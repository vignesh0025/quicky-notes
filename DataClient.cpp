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
            result = query->exec("SELECT id,title,notes,datetime,stylesheet,geometry from notes_table;");

            if(result)
            {
                if (db.driver()->hasFeature(QSqlDriver::QuerySize))
                    qDebug() << "No. of rows: "<<query->size();

                while(query->next())
                {
                    Data d(query->value(0).toInt(), query->value(1).toString(), query->value(2).toString(), query->value(3).toString());
                    qDebug() << query->value(0).toInt()
                        << query->value(1).toString()
                        << query->value(2).toString()
                        << query->value(3).toString()
                        << query->value(4).toByteArray()
                        << query->value(5).toByteArray();

                    d.setStyleSheet(query->value(4).toString());
                    d.dataUpdateFromByteArray(query->value(5).toByteArray());

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
                    datetime TEXT(15),\
                    stylesheet TEXT(25),\
                    geometry BLOB);");

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
    qDebug() << "Thread id: " << QThread::currentThreadId();
    std::int32_t id = d.id();

    if(id == -1)
    {
        query->prepare("INSERT INTO notes_table(title, notes, datetime, geometry, stylesheet) \
                values (:title, :notes, :datetime, :geometry, :stylesheet);");
        query->bindValue(":title", d.title());
        query->bindValue(":notes", d.notes());
        query->bindValue(":datetime", d.databaseDateTime());
        query->bindValue(":geometry", d.byteaarray());
        query->bindValue(":stylesheet", d.stylesheet());

        result = query->exec();

        qDebug() << query->executedQuery() << d.byteaarray();

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

        query->prepare("UPDATE notes_table SET title=:title, notes=:notes, datetime=:datetime, \
                geometry=:geometry, stylesheet=:stylesheet WHERE id=:id ;");
        query->bindValue(":title", d.title());
        query->bindValue(":notes", d.notes());
        query->bindValue(":datetime", d.databaseDateTime());
        query->bindValue(":geometry", d.byteaarray());
        query->bindValue(":stylesheet", d.stylesheet());
        query->bindValue(":id", d.id());

        result = query->exec();

        qDebug() << query->executedQuery() << d.byteaarray();

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

bool DataClient::deleteNote(std::int32_t id)
{
    // Delete only the ID is valid and not for blank window
    if(INVALID_NOTE != id)
    {
        query->prepare("DELETE FROM notes_table WHERE id=:id;");
        query->bindValue(":id", id);
        result = query->exec();

        qDebug() << query->executedQuery();

        if(result)
            qDebug() << "Data deleted from database with id " << id;
        else {
            qDebug() << GetError();
        }
    }
    else
    {
        qDebug() << "Non-existant note";

        // Note may note be existant in database but blank window may be present
        result = true;
    }
    return result;
}

void DataClient::doWork()
{
    qDebug() << "Do work from a thread " <<QThread::currentThreadId();
    emit finished();
}
