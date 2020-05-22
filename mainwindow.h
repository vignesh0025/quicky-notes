#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTextEdit>
#include <cstdint>
#include <QDebug>

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
    Data d;

public slots:
    void noteChanged();

signals:
    int32_t noteUpdated(Data &d);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
