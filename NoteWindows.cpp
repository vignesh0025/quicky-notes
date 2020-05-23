#include "NoteWindows.h"
#include "qnamespace.h"
#include <cstdlib>

NoteWindows::NoteWindows()
{
    qDebug() << QSystemTrayIcon::isSystemTrayAvailable();
    trayIcon = new QSystemTrayIcon(QIcon("./tray_icon.png"), this);

    newNoteAction = new QAction(tr("&New Note"), this);
    showAction = new QAction(tr("&Show All"), this);
    quitAction = new QAction(tr("&Quit"), this);
    minimiseAction = new QAction(tr("&Minimise all"), this);

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(newNoteAction);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(minimiseAction);
    trayIconMenu->addAction(quitAction);

    trayIconMenu->addSeparator();
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
            if(reason == QSystemTrayIcon::Trigger)
            {
            this->ShowFocus();
            }
    });
    connect(quitAction, &QAction::triggered, this, &NoteWindows::quitTrayAction);
    connect(showAction, &QAction::triggered, this, &NoteWindows::showTrayAction);
    connect(minimiseAction, &QAction::triggered, this, &NoteWindows::minimiseTrayAction);
    connect(newNoteAction, &QAction::triggered, this, [this](bool status) {this->NewNote();});

    /*//connect(trayIcon, &QSystemTrayIcon::activated, this, &NoteWindows::iconActivated);*/
}

NoteWindows::~NoteWindows()
{
    for(MainWindow *window: windows)
        delete window;
}

void NoteWindows::exec()
{
    d.Connect();


    if(d.notes_count() != 0)
    {
        for (Data dat : d.getData()) {

            win = new MainWindow(dat);
            windows.insert(win);
        }
    }
    else {
        win = new MainWindow();
        windows.insert(win);
    }

    for(auto win: windows)
    {
        connect(win, &MainWindow::noteUpdated, this, &NoteWindows::updateNote);
        connect(win->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
        getIntoFocus(win);
    }

    trayIcon->show();
}

void NoteWindows::menuAction(bool status, QWidget *parent, MenuItem item)
{

    win = (MainWindow *)parent;
    switch(item)
    {
        case MenuItem::NewNote:
            NewNote();
            break;

        case MenuItem::DeleteNote:
            if(deleteNote(win->d.id()))
            {
                win->close();
                windows.erase(win);
                delete win;
            }
            break;

        case MenuItem::BgColorNote:
            win->updateBgColor();
            break;

        case MenuItem::BoldNote:
            win->boldText(status);
            break;

        case MenuItem::ItalicNote:
            win->italicText(status);
            break;

        case MenuItem::UnderlineNote:
            win->underlineText(status);
            break;
    }
}

void NoteWindows::iconActivated()
{
    qDebug() << "Tray Icon Activated";
}

void NoteWindows::quitTrayAction(bool status)
{
    exit(0);
}

void NoteWindows::showTrayAction(bool status)
{
    ShowFocus();
}

void NoteWindows::minimiseTrayAction(bool status)
{
    for(auto win: windows)
        win->close();
}

void NoteWindows::NewNote()
{
    win = new MainWindow();
    getIntoFocus(win);
    connect(win, &MainWindow::noteUpdated, this, &NoteWindows::updateNote);
    connect(win->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
    windows.insert(win);

}

bool NoteWindows::deleteNote(std::int32_t id){
    return d.deleteNote(id);
}

void NoteWindows::ShowFocus()
{
    qDebug() << "Activated: ";
    for(auto win: windows)
        getIntoFocus(win);
}

std::int32_t NoteWindows::updateNote(Data &data)
{
    return d.updateData(data);
}

void NoteWindows::finished()
{
    qDebug() << "Finished";
}

void NoteWindows::getIntoFocus(MainWindow *win)
{
    if(!win->isVisible())
    {
        win->show();
        win->raise();
        win->setFocusPolicy(Qt::TabFocus);
        win->setFocus();
        win->activateWindow();
    }
    else if(!win->hasFocus())
    {
        win->raise();
        win->setFocusPolicy(Qt::TabFocus);
        win->setFocus();
        win->activateWindow();
    }
}
