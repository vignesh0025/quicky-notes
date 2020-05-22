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
        _datetime = QDateTime::fromString(datetime);
}


//Data::Data(Data const& data)
//{
    //_id = data._id;
    //_notes = data._notes;
    //_datetime = data._datetime;
    //_title = data._title;
//}

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
        return _datetime.toString();
    else return _datetime.toString(format);
}

QDateTime Data::orgdatetime() const
{
    return _datetime;
}

void Data::updateDateTime(QString datetime)
{
    if(datetime.isEmpty())
        _datetime = QDateTime::currentDateTime();
    else
    {
        _datetime = QDateTime::fromString(datetime);
        qDebug() << "Data::set" << _datetime << datetime;
    }
}

QString Data::databaseDateTime() const
{
    return _datetime.toString();
}

void Data::setId(std::int32_t id)
{
    _id = id;
}

void Data::setTitle(QString title)
{
    _title = title;
}

void Data::setNote(QString notes)
{
    _notes = notes;
}
