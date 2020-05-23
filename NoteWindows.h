#include <QApplication>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <memory>
#include <set>
#include <memory.h>
#include <QThread>
#include <QPixmap>

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

    void getIntoFocus(MainWindow *win);

public:
    NoteWindows();
    virtual ~NoteWindows();

    void exec();
    void NewNote();
    void ShowFocus();


public:
    DataClient d;
    std::set<MainWindow *> windows;
    MainWindow *win;

    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    QAction *newNoteAction;
    QAction *showAction;
    QAction *quitAction;
    QAction *minimiseAction;
    QThread thread;


public slots:
    void menuAction(bool status, QWidget *parent, MenuItem item);
    void iconActivated();
    void quitTrayAction(bool status);
    void showTrayAction(bool status);
    void minimiseTrayAction(bool status);

    std::int32_t updateNote(Data &d);
    bool deleteNote(std::int32_t id);

    void finished();
};

#endif /* NOTEWINDOWS_H */
