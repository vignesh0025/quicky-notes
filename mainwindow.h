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
    MainWindow(QWidget *parent = nullptr);
    void setData(Data d);
    ~MainWindow();

public:
    std::int32_t id;

public slots:
    void noteChanged();

signals:
    void noteUpdated(Data d);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
