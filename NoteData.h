#include <QObject>
#include <QAction>
#include <QWidget>

#include "Data.h"
#include "mainwindow.h"

#ifndef NOTEDATA_H
#define NOTEDATA_H

class NoteData : public QObject
{
    Q_OBJECT

public:
    MainWindow *window;
    QAction *action;

public:
    NoteData(Data data = Data(), QWidget *parent = nullptr, QString menutitle ="");
    virtual ~NoteData();
};

#endif /* NOTEDATA_H */
