#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QSqlError>
#include <QSqlDriver>
#include <vector>

#include "Data.h"
#include "mainwindow.h"
#include "qobjectdefs.h"

#ifndef DATACLIENT_H
#define DATACLIENT_H

class DataClient : public QObject
{
    //Q_OBJECT

public:
    DataClient(QString file = "./mydb.db");
    ~DataClient();
    bool Connect();
    QString GetError() const;
    std::vector<Data> getData() const;
    uint32_t notes_count() const;
    void connectWindow(MainWindow *win);

public slots:
    void updateData(Data d);

public:
    QSqlDatabase db;
    QSqlQuery *query;
    QString databaseFile;
    bool result;
    std::vector<Data> data;

};

#endif /* DATACLIENT_H */