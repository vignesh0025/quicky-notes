#include "Data.h"

const QString Data::format = "dddd, d MMMM yy hh:mm:ss";

Data::Data(std::int32_t id, QString title, QString notes, QString datetime)
{
    _id = id;
    _title = title;
    _notes = notes;
    if(datetime.isEmpty())
        _datetime = QDateTime::currentDateTime();
    else
        _datetime = QDateTime::fromString(datetime, Data::format);
}


Data::Data(Data const& data)
{
    _id = data._id;
    _notes = data._notes;
    _datetime = data._datetime;
    _title = data._title;
}

void Data::set(int32_t id, QString title, QString notes, QString datetime)
{
    _id = id;
    _title = title;
    _notes = notes;
    if(datetime.isEmpty())
        _datetime = QDateTime::currentDateTime();
    else
        _datetime = QDateTime::fromString(datetime, Data::format);
}

Data::~Data()
{

}

std::int32_t Data::id() const
{
    return _id;
}

QString Data::title() const
{
    return _title;
}

QString Data::notes() const
{
    return _notes;
}

QString Data::datetime(QString format) const
{
    if(format.isEmpty())
        return _datetime.toString(Data::format);
    else return _datetime.toString(format);
}

QDateTime Data::orgdatetime() const
{
    return _datetime;
}

void Data::setDateTime(QString str)
{
    _datetime = QDateTime::fromString(str, Data::format);
}

void Data::updateDateTime()
{
    _datetime = QDateTime::currentDateTime();
}
