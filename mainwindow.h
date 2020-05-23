#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTextEdit>
#include <cstdint>
#include <QDebug>
#include <QTimer>
#include <QToolButton>
#include <QToolBar>
#include <QAction>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QTextCursor>
#include <QFont>

#include "Data.h"
#include "quicky_toolbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Data data = Data(), QWidget *parent = nullptr);
    void setData(Data d);
    ~MainWindow();
    void updateUI();
    void updateBgColor();
    void boldText(bool status);
    void italicText(bool status);
    void underlineText(bool status);

    bool self_gui_update_ongoing;
    Data d;
    QTimer timer;


protected:
    void resizeEvent(QResizeEvent *ev) override;
    void moveEvent(QMoveEvent *ev) override;

public:
    QuickyToolbar *toolbar;

public slots:
    void noteChanged();
    void timeOut();

signals:
    int32_t noteUpdated(Data &d);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
