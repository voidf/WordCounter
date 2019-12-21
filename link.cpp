#include "link.h"

#include <QJsonDocument>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <QApplication>
#include <QTextCodec>

#include <unordered_map>
#include <iostream>

#include <string>
extern QObject *rootobj;
static std::unordered_map<std::string, long long> count_map;
static bool is_ignore=0;
static const char *codecli[] = {
    "UTF-8",
    "Big5",
    "Big5-HKSCS",
    "CP949",
    "EUC-JP",
    "EUC-KR",
    "HP-ROMAN8",
    "IBM 850",
    "IBM 866",
    "IBM 874",
    "ISO 2022-JP",
    "ISO 8859-1",
    "ISO 8859-13",
    "KOI8-R",
    "KOI8-U",
    "Macintosh",
    "Shift-JIS",
    "TIS-620",
    "TSCII",
    "UTF-16",
    "UTF-16BE",
    "UTF-16LE",
    "UTF-32",
    "UTF-32BE",
    "UTF-32LE",
    "Windows-1250",
    "GB18030"
};

QDataMgr::QDataMgr(QObject *parent) : QObject(parent)
{
    _rules << "\n";
    _rules << " ";
    _rules << "\t";
    _rules << "\v";
    _rules << "\r";
    _rules << "\f";
    //_rules << "\0";
    //_rules << QString::fromLocal8Bit("以上为部分不可见字符，勿删");//MSVC
    _rules << ("以上为部分不可见字符，勿删"); //MinGW
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

    _default_codec="GB18030";
}
void QDataMgr::ignore_upper()
{
    is_ignore^=1;
}


void QDataMgr::exp_file(QVariant pa, QVariant ma)
{
    QString file_path = pa.toString();
    if (file_path.left(8) == "file:///")
        file_path = file_path.right(file_path.length() - 8);
    file_path += "/count_result.json";

    QFile new_file(file_path);
    new_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray buf = ma.toByteArray();
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

        QTextCodec::ConverterState state;
        QString content_str;
        bool is_conv = 0;
        //int min_invalid=0x7fffffff;
        int si=sizeof (codecli);
        qDebug()<<"size:"<<si;
        if(_default_codec=="GB18030"){
            for (int i = 0; si; i++)
            {
                si-=sizeof (codecli[i]);
                QTextCodec *codec = QTextCodec::codecForName(codecli[i]);
                QString text = codec->toUnicode(content.constData(), content.size(), &state);
                //text.replace("\u0000","");
                if (state.invalidChars > 0)
                {

                    //                if(state.remainingChars==0)
                    //                {
                    //                    content_str=text;
                    //                    qDebug() << content_str;

                    //                }
                    qDebug() << codecli[i] << "\tinvalidChars:" << state.invalidChars;

                    qDebug()<<state.remainingChars;

                }
                else
                {
                    content_str = text;
                    is_conv = 1;
                    _default_codec = codecli[i];
                    break;
                }
                //codec=~QTextCodec();

            }

            if (!is_conv)
            {
                qDebug() << "Invalid codec!";
                QByteArray tarr=_default_codec.toLatin1();
                QTextCodec *codec = QTextCodec::codecForName(tarr.data());
                content_str = codec->toUnicode(content.constData(), content.size(), &state);
            }
        }
        else
        {
            qDebug()<<"codec set!";
            QByteArray tarr=_default_codec.toLatin1();
            QTextCodec *codec = QTextCodec::codecForName(tarr.data());
            content_str = codec->toUnicode(content.constData(), content.size(), &state);
        }



        if(is_ignore)
            content_str=content_str.toLower();

        QStringList content_split_list = content_str.split(_rules.at(0), QString::SkipEmptyParts);

        for (int i = 1; i < _rules.size(); i++)
        {
            QStringList tmp_strli;
            for (int j = 0; j < content_split_list.size(); j++)
            {
                QStringList tmp_strli2 = content_split_list.at(j).split(_rules.at(i), QString::KeepEmptyParts);
                if (tmp_strli2.size() > 1)
                {
                    tmp_strli << content_split_list.at(j).split(_rules.at(i), QString::SkipEmptyParts);
                    content_split_list.removeAt(j);
                    j--;
                }
            }
            content_split_list << tmp_strli;
        }



        count_map.clear();

        for (int i = 0; i < content_split_list.size(); i++)
        {
            std::string tmpstr = content_split_list.at(i).toStdString();
            if (count_map.find(tmpstr) == count_map.end())
            {
                count_map[tmpstr] = 1;
            }
            else
            {
                count_map[tmpstr] += 1;
            }
        }

        o = rootobj->findChild<QObject *>("res_view");
        QMetaObject::invokeMethod(o, "clear_r");

        for (std::unordered_map<std::string, long long>::iterator itr = count_map.begin(); itr != count_map.end(); itr++)
        {
            QVariant fst(QString::fromStdString(itr->first));
            QVariant sec(itr->second);
            QMetaObject::invokeMethod(o, "append_list", Q_ARG(QVariant, fst), Q_ARG(QVariant, sec));
        }
    }
    else if (!_file_path.length())
    {
        QMetaObject::invokeMethod(rootobj, "non_file");
    }
    else
    {
        QMetaObject::invokeMethod(rootobj, "non_rule");
    }
}

void QDataMgr::init_rules()
{
    QObject *o;
    o = rootobj->findChild<QObject *>("add_rules_view");

    QMetaObject::invokeMethod(o, "clear_r");

    for (int i = 0; i < _rules.size(); i++)
    {
        QVariant input_arg(_rules.at(i));
        qDebug() << input_arg;
        QMetaObject::invokeMethod(o, "init_r", Q_ARG(QVariant, input_arg));
    }
    qDebug() << _rules;
}

void QDataMgr::show_codec_list()
{

    QObject *o;
    o = rootobj->findChild<QObject *>("co_view");
    QMetaObject::invokeMethod(o, "clear_r");

    int codeset_size=sizeof (codecli);
    for (int i = 0; codeset_size; i++)
    {
        codeset_size -= sizeof (codecli[i]);

        QVariant input_arg(codecli[i]);
        qDebug() << input_arg;
        QMetaObject::invokeMethod(o, "append_list", Q_ARG(QVariant, input_arg));
    }
}

void QDataMgr::set_codec(QVariant cod)
{
    _default_codec = cod.toString();
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
