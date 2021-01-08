
#ifndef QDATAMGR_H
#define QDATAMGR_H
#include <unordered_map>
#include <QObject>
#include <QUrl>
#include <QVariant>
//extern std::unordered_map<std::string,long long>count_map;



class QmlInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _file_path READ rfurl WRITE wfurl)
    Q_PROPERTY(QString _default_codec READ rdc WRITE wdc)

public:
    explicit QmlInterface(QObject *parent = nullptr);

    QString rfurl() const{return _file_path;}
    void wfurl(QString s){_file_path = s;}

    QString rdc()const{return _default_codec;}
    void wdc(QString tdc){_default_codec=tdc;}
 
public:
    Q_INVOKABLE void exp_file(QVariant pa,QVariant ma);
    Q_INVOKABLE void count_files();
    Q_INVOKABLE void init_rules();
    Q_INVOKABLE void add_rule(QVariant ad);//传列表用QVariantList，键值对用QVariantMap
    Q_INVOKABLE void del_rule(QVariant rm);
    Q_INVOKABLE void ignore_upper();
    Q_INVOKABLE void show_codec_list();
    Q_INVOKABLE void set_codec(QVariant cod);

private:
    QStringList _rules;
    QString _file_path;
    QObject *_obj;
    QString _default_codec;

};
 
#endif // QDATAMGR_H
