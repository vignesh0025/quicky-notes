#include "DataClient.h"
#include "qdebug.h"
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
                    Data d;
                    //d.set(query->value(0).toInt(), query->value(1).toString(), query->value(2).toString(), query->value(3).toString());
                    /*data.push_back(d);*/
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
                     id INTEGER NOT NULL,\
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


std::vector<Data> DataClient::getData() const
{
    return data;
}

uint32_t DataClient::notes_count() const
{
    return data.size();
}


void DataClient::updateData(Data d)
{
    qDebug() << "NOte change received";
}

void DataClient::connectWindow(MainWindow *win)
{
    connect(win, &MainWindow::noteUpdated, this, &DataClient::updateData );
}
