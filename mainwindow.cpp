#include "mainwindow.h"
#include <QDateTime>
#include "ui_mainwindow.h"

MainWindow::MainWindow(Data data, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    d = data;

    //d._id = -1;
    //d._notes = ui->notes->toPlainText();
    //d._title = ui->title->text();
    //d.setDateTime(QDateTime::currentDateTime().toString(Data::format));

    updateUI();
    connect(ui->notes, &QTextEdit::textChanged, this, &MainWindow::noteChanged);
}

void MainWindow::updateUI()
{
    ui->notes->setText(d._notes);
    ui->title->setText(d._title);
    ui->statusbar->showMessage(d.datetime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(Data d)
{
    this->ui->title->setText(d.title());
    this->ui->notes->setText(d.notes());
    this->ui->statusbar->showMessage(d.datetime());
}

void MainWindow::noteChanged()
{
    ui->statusbar->showMessage(QDateTime::currentDateTime().toString(Data::format));

    d.set(d._id, ui->title->text(), ui->notes->toPlainText());
    d._id = emit noteUpdated(d);
    qDebug() << "Returned id " << d._id;
}

