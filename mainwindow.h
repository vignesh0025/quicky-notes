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

#include "Data.h"

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

public:
    bool self_gui_update_ongoing;
    Data d;
    QTimer timer;
    QToolBar *toolbar;

public slots:
    void noteChanged();
    void deleteBtnClicked();
    void timeOut();

signals:
    int32_t noteUpdated(Data &d);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
