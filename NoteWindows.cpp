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


    // If there are no notes, create a blank note and show
    if(d.notes_count() == 0)
    {
        win = new NoteData();
        PrepareWindow(win);

    }
    else for (Data dat : d.getData()) {
        win = new NoteData(dat);
        PrepareWindow(win);
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
            deleteNote(window, window->d.id());
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

    trayNotesMenu->setTitle(QString("Total %1").arg(d.notes_count()));
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
    // If a blank window is already open, show it rather than creating new window
    for(auto win: windows)
        if(win->window->d.id() == INVALID_NOTE)
        {
            qDebug() << "Showing already existing new window";
            getIntoFocus(win->window);
        }
        else
        {
            this->win = new NoteData();
            PrepareWindow(this->win);
        }

}

void NoteWindows::deleteNote(MainWindow *window, std::int32_t id)
{
    bool check = (id == INVALID_NOTE)? true :  d.deleteNote(id);

    if(check)
    {
        // Duplicated loop #LOOPCLOSEWINDOW
        for(auto win1: windows)
        {
            if(win1->window == window)
            {
                windows.erase(win1);
                trayNotesMenu->removeAction(win1->action);
                win1->window->close();
                delete win1;
                break;
            }
        }
    }
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
        win->setFocus();
        win->activateWindow();
    }
    else if(!win->hasFocus())
    {
        win->raise();
        win->setFocus();
        win->activateWindow();
    }
    else {

    }
}

void NoteWindows::PrepareWindow(NoteData *win1)
{
    // Connect the window close event to the event handler in this class
    connect(win1->window, &MainWindow::windowClosed, this, &NoteWindows::MainWindowClosed);

    // Connect Note List in Tray Menu to the corresponding window to show the window
    connect(win1->action, &QAction::triggered, [this, win1] () { this->getIntoFocus(win1->window); });

    // Connect the note update event from window to the Note updation function in this class
    connect(win1->window, &MainWindow::noteUpdated, this, &NoteWindows::updateNote);

    // Connect the toolbar in every window to same handler in this Class and then route to the corresponding window
    connect(win1->window->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);

    // Add the corresponding menu to tray
    trayNotesMenu->addAction(win1->action);

    // Show the window
    getIntoFocus(win->window);

    // Insert the window into the set we have
    windows.insert(win);
}


void NoteWindows::MainWindowClosed(MainWindow *window)
{

    // When a Unused note is closed, delete the node rather than closing it
    if(window->d.id() == INVALID_NOTE)
    {
        qDebug() << "Delete unused window";

        // Duplicated loop #LOOPCLOSEWINDOW
        for(auto win1: windows)
        {
            if(win1->window == window)
            {
                windows.erase(win1);
                trayNotesMenu->removeAction(win1->action);
                window->setAttribute( Qt::WA_DeleteOnClose );
                break;
            }
            else qDebug() << "Window not found" << window->d.id();
        }
    }

    trayNotesMenu->setTitle(QString("Total %1").arg(d.notes_count()));
}
