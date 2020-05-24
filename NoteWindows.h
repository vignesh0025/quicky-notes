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
#include "NoteData.h"

#ifndef NOTEWINDOWS_H
#define NOTEWINDOWS_H



class NoteWindows : public QObject
{

    void getIntoFocus(MainWindow *win);
    void PrepareWindow(NoteData *win);

public:
    NoteWindows();
    virtual ~NoteWindows();

    void exec();
    void NewNote();
    void ShowFocus();

public:
    DataClient d;
    std::set<NoteData *> windows;
    std::set<QAction *> actions;

    NoteData *win;
    QAction *act;

    QMenu *trayIconMenu;
    QMenu *trayNotesMenu;
    QSystemTrayIcon *trayIcon;

    QAction *newNoteAction;
    QAction *showAction;
    QAction *quitAction;
    QAction *minimiseAction;
    QThread thread;


public slots:
    void menuAction(bool status, QWidget *parent, MenuItem item);
    void iconActivated(std::int32_t id);
    void quitTrayAction(bool status);
    void showTrayAction(bool status);
    void minimiseTrayAction(bool status);
    void trayNoteTriggered();
    std::int32_t updateNote(Data &d);
    void deleteNote(MainWindow *win1, std::int32_t id = INVALID_NOTE);
    void MainWindowClosed(MainWindow *window);

    void finished();
};

#endif /* NOTEWINDOWS_H */
