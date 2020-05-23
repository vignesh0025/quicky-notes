#include "NoteWindows.h"

NoteWindows::NoteWindows()
{

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
        connect(win, &MainWindow::noteUpdated, &d, &DataClient::updateData);
        connect(win->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
        win->show();
    }
}

void NoteWindows::menuAction(bool status, QWidget *parent, MenuItem item)
{
    switch(item)
    {
        case MenuItem::NewNote:
            win = new MainWindow();
            win->show();
            connect(win, &MainWindow::noteUpdated, &d, &DataClient::updateData);
            connect(win->toolbar, &QuickyToolbar::menuActionTriggered, this, &NoteWindows::menuAction);
            windows.insert(win);
            break;

        case MenuItem::DeleteNote:
            win = (MainWindow *)parent;
            if(d.deleteNote(win->d.id()))
            {
                win->close();
                windows.erase(win);
            }
            break;
    }
}
