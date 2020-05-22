#include "mainwindow.h"

#include <QApplication>
#include <memory>
#include <vector>
#include <memory.h>
#include "DataClient.h"
#include "Data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataClient d;
    d.Connect();

    std::vector<MainWindow *> windows;

    MainWindow *w;

    if(d.notes_count() != 0)
    {
        for(Data d: d.getData())
        {
            MainWindow *win = new MainWindow();
            win->setData(d);
            windows.push_back(win);
        }
    }
    else {
        w = new MainWindow();
        w->show();
        windows.push_back(w);
    }

    auto ret =  a.exec();
    for(MainWindow *window: windows)
        delete window;

    return ret;
}


