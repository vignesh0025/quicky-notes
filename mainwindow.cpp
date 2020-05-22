#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(QDateTime::currentDateTime().toString(Data::format));
    ui->title->setText("New Note");
    id = -1;

    connect(ui->notes, &QTextEdit::textChanged, this, &MainWindow::noteChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(Data d)
{
    this->id = d.id();
    this->ui->title->setText(d.title());
    this->ui->notes->setText(d.notes());
    this->ui->statusbar->showMessage(d.datetime());
}

void MainWindow::noteChanged()
{
    ui->statusbar->showMessage(QDateTime::currentDateTime().toString(Data::format));

    Data d(id, ui->title->text(), ui->notes->toPlainText(), ui->statusbar->currentMessage());
    emit noteUpdated(d);
}
