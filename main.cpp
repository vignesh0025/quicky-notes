#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QtGlobal>
#include <QByteArray>
#include <QDebug>

#include "NoteWindows.h"
#include "RunGuard.h"

int main(int argc, char *argv[])
{
    qputenv("QT_LOGGING_TO_CONSOLE", QByteArray("0"));

    RunGuard guard( "some_random_key" );
    if ( !guard.tryToRun() )
    {
        // Needed to enable logging to syslog or journald.
        qDebug() << "An Instance is already running";
        return 0;
    }

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    NoteWindows n;
    n.exec();

    return a.exec();
}

