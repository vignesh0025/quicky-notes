#include <QObject>
#include <memory>
#include <set>
#include <memory.h>

#include "mainwindow.h"
#include "DataClient.h"
#include "DataClient.h"
#include "Data.h"
#include "quicky_toolbar.h"
#include "MenuItem.h"

#ifndef NOTEWINDOWS_H
#define NOTEWINDOWS_H

class NoteWindows : public QObject
{

public:
    NoteWindows();
    virtual ~NoteWindows();

    void exec();

public:
    DataClient d;
    std::set<MainWindow *> windows;
    MainWindow *win;

public slots:
    void menuAction(bool status, QWidget *parent, MenuItem item);

};

#endif /* NOTEWINDOWS_H */
