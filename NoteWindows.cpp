#include "NoteWindows.h"
#include "qmenu.h"
#include "qnamespace.h"
#include <cstdlib>

NoteWindows::NoteWindows()
{
    qDebug() << QSystemTrayIcon::isSystemTrayAvailable();
    trayIcon = new QSystemTrayIcon(QIcon(":/icons/tray_icon.png"), this);

    newNoteAction = new QAction(tr("&New Note"), this);
    showAction = new QAction(tr("&Show All"), this);
    quitAction = new QAction(tr("&Quit"), this);
    minimiseAction = new QAction(tr("&Minimise all"), this);

    trayNotesMenu = new QMenu(QString("Total %1").arg(d.notes_count()));

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(newNoteAction);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(minimiseAction);
    trayIconMenu->addAction(quitAction);
    trayIconMenu->addMenu(trayNotesMenu);


    trayIconMenu->addSeparator();
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setToolTip(QString("Total %1").arg(d.notes_count()));

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
    delete trayNotesMenu;
    delete trayNotesMenu;
    delete trayIcon;
    delete newNoteAction;
    delete showAction;
    delete quitAction;
    delete minimiseAction;

    for(auto window: windows)
        delete window;
}

void NoteWindows::exec()
{
    d.Connect();

    trayNotesMenu->setTitle(QString("Total %1").arg(d.notes_count()));

    if(d.notes_count() != 0)
    {
        for (Data dat : d.getData()) {
            win = new NoteData(dat);
            windows.insert(win);
        }
    }
    else {
        win = new NoteData();
        windows.insert(win);
    }

    for(NoteData *win: windows)
    {
        trayNotesMenu->addAction(win->action);
        connect(win->action, &QAction::triggered, [this,win] () { this->getIntoFocus(win->window); });
        connect(win->window, &MainWindow::noteUpdated, this, &NoteWindows::updateNote);
        connect(win->window->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
        getIntoFocus(win->window);
    }

    trayIcon->show();
}

void NoteWindows::menuAction(bool status, QWidget *parent, MenuItem item)
{
    MainWindow *window = (MainWindow *)parent;
    switch(item)
    {
        case MenuItem::NewNote:
            NewNote();
            break;

        case MenuItem::DeleteNote:
            if(deleteNote(window->d.id()))
            {
                for(auto win1: windows)
                {
                    if(win1->window == window)
                    {
                        this->win = win1;
                        trayNotesMenu->removeAction(this->win->action);
                        this->win->window->close();
                        windows.erase(this->win);
                        delete this->win;
                        this->win = nullptr;
                        break;
                    }
                    else
                    {
                        qDebug() << "Window not found" << window->d.id();
                    }
                }
            }
            break;

        case MenuItem::BgColorNote:
            window->updateBgColor();
            break;

        case MenuItem::BoldNote:
            window->boldText(status);
            break;

        case MenuItem::ItalicNote:
            window->italicText(status);
            break;

        case MenuItem::UnderlineNote:
            window->underlineText(status);
            break;

        case MenuItem::TextColorNote:
            window->colorText();
            break;

        case MenuItem::StrikeOutNote:
            window->strikeoutNote(status);
            qDebug() <<"strike icon";
            break;
    }
}

void NoteWindows::iconActivated(std::int32_t id)
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
        win->window->close();
}

void NoteWindows::NewNote()
{
    this->win = new NoteData();
    getIntoFocus(this->win->window);

    trayNotesMenu->addAction(win->action);
    connect(this->win->action, &QAction::triggered, [this] () { getIntoFocus(this->win->window); });
    connect(this->win->window, &MainWindow::noteUpdated, this, &NoteWindows::updateNote);
    connect(this->win->window->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
    windows.insert(this->win);
}

bool NoteWindows::deleteNote(std::int32_t id){
    return d.deleteNote(id);
}

void NoteWindows::ShowFocus()
{
    for(auto win: windows)
        getIntoFocus(win->window);
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
