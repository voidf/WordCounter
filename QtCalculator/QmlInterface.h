
#ifndef QmlInterface_H
#define QmlInterface_H
#include <unordered_map>
#include "BigInteger.cpp"
#include <QJsonDocument>
#include <QDebug>
#include <QString>
#include <QObject>

#include <string>
#include <QObject>
#include <QUrl>
#include <QVariant>
extern QObject *rootobj;
class QmlInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _query_expression READ rfurl WRITE wfurl)
    //    Q_PROPERTY(QString _default_codec READ rdc WRITE wdc)

public:
    explicit QmlInterface(QObject *parent = nullptr) : QObject(parent) {}

    QString rfurl() const { return _query_expression; }
    void wfurl(QString s) { _query_expression = s; }

    //    QString rdc() const { return _default_codec; }
    //    void wdc(QString tdc) { _default_codec = tdc; }

public:
    Q_INVOKABLE void handle_exp(QVariant q)
    {
        QString s = q.toString();
        std::string handler;
        for (auto i : s)
        {
//            qDebug() << i;

        }
    }
    //Q_INVOKABLE void add_rule(QVariant ad); //传列表用QVariantList，键值对用QVariantMap

private:
    QStringList _rules;
    QString _query_expression;
    QObject *_obj;
    QString _default_codec;
};

#endif // QDATAMGR_H
