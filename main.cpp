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
      for (Data dat : d.getData()) {

        MainWindow *win = new MainWindow(dat);
        //win->setData(dat);
        win->show();
        d.connectWindow(win);
        windows.push_back(win);
      }
    }
    else {
        w = new MainWindow();
        w->show();
        d.connectWindow(w);
        windows.push_back(w);
    }

    auto ret =  a.exec();
    for(MainWindow *window: windows)
        delete window;

    return ret;
}


