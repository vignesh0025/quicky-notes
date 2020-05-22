#include <cstdint>
#include <QString>
#include <QDateTime>

#ifndef DATA_H
#define DATA_H

class Data
{
private:


public:
    static const QString format;

public:
    Data(int32_t _id = 0, QString _title = "", QString _notes = "", QString _datetime = "");
    Data(Data const& data);
    void set(int32_t _id, QString _title, QString _notes, QString _datetime = "");
    std::int32_t id() const;
    QString title() const;
    QString notes() const;

    QString datetime(QString format = "") const;
    QDateTime orgdatetime() const;
    void setDateTime(QString str);
    void updateDateTime();

    virtual ~Data();

    int32_t _id;
    QString _title;
    QString _notes;
    QDateTime _datetime;

};

#endif /* DATA_H */
