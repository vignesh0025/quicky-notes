#include <QApplication>
#include <QDebug>

#include "NoteWindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    NoteWindows n;
    n.exec();

    return a.exec();
}


