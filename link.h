
#ifndef QDATAMGR_H
#define QDATAMGR_H
#include <unordered_map>
#include <QObject>
#include <QUrl>
#include <QVariant>
//extern std::unordered_map<std::string,long long>count_map;



class QDataMgr : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _file_path READ rfurl WRITE wfurl)

public:
    explicit QDataMgr(QObject *parent = nullptr);

    QString rfurl() const{return _file_path;}
    void wfurl(QString s){_file_path = s;}
 
public:
    Q_INVOKABLE void exp_file(QVariant pa,QVariant ma);
    Q_INVOKABLE void count_files();
    Q_INVOKABLE void init_rules();
    Q_INVOKABLE void add_rule(QVariant ad);//传列表用QVariantList，键值对用QVariantMap
    Q_INVOKABLE void del_rule(QVariant rm);

private:
    QStringList _rules;
    QString _file_path;
    QObject *_obj;


};
 
#endif // QDATAMGR_H
