#include "Data.h"

const QString Data::format = "dddd, d MMMM yy hh:mm:ss";

Data::Data(std::int32_t id, QString title, QString notes, QString datetime,QPoint pos, QSize size)
{
    _id = id;
    _title = title;
    _notes = notes;
    if(datetime.isEmpty())
        _datetime = QDateTime::currentDateTime();
    else
        _datetime = QDateTime::fromString(datetime);
    setGeomentry(pos, size);
    setStyleSheet("background-color: white");
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

QPoint Data::pos() const
{
    return _pos;
}

QSize Data::size() const
{
    return _size;
}

QByteArray Data::byteaarray() const
{
    return _bytearray;
}

void Data::setGeomentry(QPoint pos, QSize size)
{
    qDebug() << "New Size" << pos << size;

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out_str(&buffer);
    out_str << pos << size;
    _bytearray = buffer.buffer();
    _pos = pos;
    _size = size;
    buffer.close();

    qDebug() << _bytearray;
}

void Data::dataUpdateFromByteArray(QByteArray byte)
{
    _bytearray = byte;
    QBuffer buffer(&byte);
    buffer.open(QBuffer::ReadWrite);
    QDataStream inp(&buffer);
    inp >> _pos >> _size;
    buffer.close();

    qDebug() << "Obtained from byte " << _pos << _size;
}

void Data::setStyleSheet(QString stylesheet)
{
    _stylesheet = stylesheet;
}

QString Data::stylesheet() const
{
    return _stylesheet;
}
