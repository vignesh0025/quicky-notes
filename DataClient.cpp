#include "DataClient.h"
#include "qdebug.h"
#include <cstdint>
#include <vector>

DataClient::DataClient(QString file)
{
    databaseFile = file;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file);
    db.setHostName("vd-san");
}


DataClient::~DataClient()
{
    db.close();
}

bool DataClient::Connect()
{
    if(QFile::exists(databaseFile))
    {
        if((result = db.open()) == true)
        {
            qDebug() << "Database Opened Successfully";
            query = new QSqlQuery(this->db);
            result = query->exec("SELECT * from notes_table;");

            if(result)
            {
                if (db.driver()->hasFeature(QSqlDriver::QuerySize))
                    qDebug() << "No. of rows: "<<query->size();

                while(query->next())
                {
                    Data d(query->value(0).toInt(), query->value(1).toString(), query->value(2).toString(), query->value(3).toString());
                    qDebug() << query->value(0).toInt() << query->value(1).toString() << query->value(2).toString()<< query->value(3).toString();

                    data.push_back(d);
                }
                qDebug() << "All Data obtained from table";
            }
            else {
                qDebug() << "Error Querying Table";
            }
        }
        else {
            qDebug() << "Error Opening Existing Database";
        }
    }
    else {
        if((result = db.open()) == true)
        {
            qDebug() << "Database Opened Successfully";
            query = new QSqlQuery(this->db);
            result = query->exec("CREATE TABLE notes_table (\
                     id INTEGER PRIMARY KEY AUTOINCREMENT,\
                    title TEXT(25),\
                    notes TEXT(2000),\
                    datetime TEXT(15) NOT NULL);");

            if(result) qDebug() << "Table Created";
            else qDebug() << "Error Creating Table";
        }
        else qDebug() << "Error Creating database File ";
    }

    return result;
}

QString DataClient::GetError() const
{
    QSqlError err = query->lastError();
    return err.text();
}


std::vector<Data> DataClient::getData() const {
    return data;
}

uint32_t DataClient::notes_count() const
{
    return data.size();
}


std::int32_t DataClient::updateData(Data &d)
{
    std::int32_t id = d.id();

    if(id == -1)
    {
        QString command = QString("INSERT INTO notes_table(title, notes, datetime) \
                values ('%1', '%2', '%3')").arg(d.title(), d.notes(), d.databaseDateTime());
        qDebug() << command;

        result = query->exec(command);
        if(result)
        {
            qDebug() << "Data Inserted into database with id " << query->lastInsertId().toInt();

            id = query->lastInsertId().toInt();
        }
        else {
            qDebug() << GetError();
        }

    }
    else {
        QString command = QString("UPDATE notes_table SET title='%1', notes='%2', datetime='%3' \
                WHERE id=%4;").arg(d.title(), d.notes(),  d.databaseDateTime()).arg(id);
        qDebug() << command;

        result = query->exec(command);
        if(result)
            qDebug() << "Data updated into database with id " << id;
        else {
            qDebug() << GetError();
        }
    }
    return id;
}

void DataClient::connectWindow(MainWindow *win)
{
    connect(win, &MainWindow::noteUpdated, this, &DataClient::updateData );
}

bool DataClient::deleteNote(std::int32_t id){

    QString command = QString("DELETE FROM notes_table WHERE id='%1';").arg(id);
    qDebug() << command;

    result = query->exec(command);
    if(result)
        qDebug() << "Data deleted from database with id " << id;
    else {
        qDebug() << GetError();
    }

    return result;
}
