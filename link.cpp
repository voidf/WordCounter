#include "link.h"
#include <QDebug>
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <QApplication>
#include <unordered_map>
#include <iostream>
#include <QJsonDocument>
static std::unordered_map<std::string,long long>count_map;
extern QObject *rootobj;
QDataMgr::QDataMgr(QObject *parent) : QObject(parent)
{
    _rules << "\n";
    _rules << " ";
    _rules << "\t";
    _rules << "\v";
    _rules << "\r";
    _rules << "\f";
    //_rules << "\0";
    _rules << QString::fromLocal8Bit("以上为部分不可见字符，勿删");
    _rules << ",";
    _rules << ".";
    _rules << "(";
    _rules << ")";
    _rules << "?";
    _rules << "!";
    _rules << "/";
    _rules << "\"";
    _rules << "'";
    _rules << "\\";
    _rules << ":";
    _rules << ";";
}

void QDataMgr::exp_file(QVariant pa,QVariant ma)
{
    QString file_path=pa.toString();
    if(file_path.left(8) == "file:///")
        file_path = file_path.right(file_path.length() - 8);
    file_path+="/count_result.json";


    QFile new_file(file_path);
    new_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray buf= ma.toByteArray();
    new_file.write(buf);
    new_file.close();
}

void QDataMgr::count_files()
{
    QObject *o;

    if (_file_path.length() && _rules.size())
    {
        qDebug() << "counting";
        if (_file_path.left(8) == "file:///")
            _file_path = _file_path.right(_file_path.length() - 8);

        QFile new_file(_file_path);
        new_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray content = new_file.readAll();
        new_file.close();

        QString content_str=QString::fromStdString(content.toStdString());

        QStringList content_split_list=content_str.split(_rules.at(0),QString::SkipEmptyParts);

        for(int i=1;i<_rules.size();i++)
        {
            QStringList tmp_strli;
            for(int j=0;j<content_split_list.size();j++)
            {
                QStringList tmp_strli2=content_split_list.at(j).split(_rules.at(i),QString::KeepEmptyParts);
                if(tmp_strli2.size()>1)
                {
                    tmp_strli << content_split_list.at(j).split(_rules.at(i),QString::SkipEmptyParts);
                    content_split_list.removeAt(j);
                    j--;
                }
            }
            content_split_list << tmp_strli;
        }

        count_map.clear();

       for(int i=0;i<content_split_list.size();i++)
       {
           std::string tmpstr=content_split_list.at(i).toStdString();
           if(count_map.find(tmpstr)==count_map.end())
           {
               count_map[tmpstr]=1;
           }
           else
           {
               count_map[tmpstr]+=1;
           }
       }

       o=rootobj->findChild<QObject*>("res_view");
       QMetaObject::invokeMethod(o,"clear_r");

       for (std::unordered_map<std::string, long long>::iterator itr=count_map.begin();itr!=count_map.end();itr++)
       {
            QVariant fst(QString::fromStdString(itr->first));
            QVariant sec(itr->second);
            QMetaObject::invokeMethod(o,"append_list",Q_ARG(QVariant,fst),Q_ARG(QVariant,sec));
       }

    }
    else if(!_file_path.length())
    {
        QMetaObject::invokeMethod(rootobj,"non_file");
    }
   else
    {
        QMetaObject::invokeMethod(rootobj,"non_rule");
    }
}

void QDataMgr::init_rules()
{
    QObject *o;
    o=rootobj->findChild<QObject*>("add_rules_view");


    QMetaObject::invokeMethod(o,"clear_r");

    for (int i = 0; i < _rules.size(); i++)
    {
        QVariant input_arg(_rules.at(i));
        qDebug()<<input_arg;
        QMetaObject::invokeMethod(o,"init_r",Q_ARG(QVariant,input_arg));
    }
    qDebug() << _rules;
}

void QDataMgr::add_rule(QVariant ad)
{
    _rules << ad.toString();
    qDebug() << _rules;
}

void QDataMgr::del_rule(QVariant rm)
{
    _rules.removeAt(rm.toInt());
    qDebug() << _rules;
}
