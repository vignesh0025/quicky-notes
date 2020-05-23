#include <cstdint>
#include <QString>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QByteArray>
#include <QBuffer>
#include <QPoint>
#include <QSize>

#ifndef DATA_H
#define DATA_H

#define INVALID_NOTE -1

class Data
{
private:


public:
    static const QString format;

public:
    Data(int32_t _id = -1, QString _title = "New Note", QString _notes = "",\
            QString _datetime = "", QPoint pos = QPoint(0,0), QSize size = QSize(353, 307));

    std::int32_t id() const;
    QString title() const;
    QString notes() const;
    QPoint pos() const;
    QSize size() const;
    QString stylesheet() const;
    QString datetime(QString format = Data::format) const;
    QByteArray byteaarray() const;

    QString databaseDateTime() const;
    QDateTime orgdatetime() const;
    void updateDateTime(QString str = "");

    void setId(std::int32_t id);
    void setTitle(QString str = "");
    void setNote(QString str = "");
    void setGeomentry(QPoint pos, QSize size);
    void dataUpdateFromByteArray(QByteArray byte);
    void setStyleSheet(QString stylesheet);

    virtual ~Data();

private:
    int32_t _id;
    QString _title;
    QString _notes;
    QDateTime _datetime;
    QByteArray _bytearray;
    QPoint _pos;
    QSize _size;
    QString _stylesheet;
};

#endif /* DATA_H */
