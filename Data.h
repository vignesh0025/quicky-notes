#include <cstdint>
#include <QString>
#include <QDateTime>
#include <QDebug>

#ifndef DATA_H
#define DATA_H

class Data
{
private:


public:
    static const QString format;

public:
    Data(int32_t _id = -1, QString _title = "New Note", QString _notes = "", QString _datetime = "");

    std::int32_t id() const;
    QString title() const;
    QString notes() const;
    QString datetime(QString format = Data::format) const;

    QString databaseDateTime() const;
    QDateTime orgdatetime() const;
    void updateDateTime(QString str = "");

    void setId(std::int32_t id);
    void setTitle(QString str = "");
    void setNote(QString str = "");

    virtual ~Data();

private:
    int32_t _id;
    QString _title;
    QString _notes;
    QDateTime _datetime;

};

#endif /* DATA_H */
