#include <QApplication>

#include "NoteWindows.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NoteWindows n;
    n.exec();

    return a.exec();
}


