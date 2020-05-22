#include "mainwindow.h"
#include <QDateTime>
#include "qnamespace.h"
#include "qwindowdefs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Data data, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    self_gui_update_ongoing = true;

    d = data;
    qDebug() << "Date time " << data.datetime();

    timer.setInterval(1000);
    timer.setSingleShot(true);

    // Perform UI additions before adding data
    toolbar = new QuickyToolbar();
    this->addToolBar(Qt::BottomToolBarArea, toolbar);

    updateUI();

    // Connect Events only after updating the UI so no signals are sent
    connect(ui->notes, &QTextEdit::textChanged, this, &MainWindow::noteChanged);
    connect(ui->title, &QLineEdit::textChanged, this, &MainWindow::noteChanged);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeOut);

    //connect(ui->deleteBtn, &QToolButton::clicked
}

void MainWindow::updateUI()
{
    this->ui->id->display(d._id);
    this->ui->title->setText(d.title());
    this->ui->notes->setText(d.notes());
    this->ui->statusbar->showMessage(d.datetime());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete toolbar;
}

void MainWindow::setData(Data data)
{
    d = data;
    updateUI();
}

void MainWindow::noteChanged()
{
    timer.start();
}

void MainWindow::timeOut()
{
    ui->statusbar->showMessage(QDateTime::currentDateTime().toString(Data::format));

    d.set(d._id, ui->title->text(), ui->notes->toPlainText());
    d._id = emit noteUpdated(d);
    this->ui->id->display(d._id);
    qDebug() << "Returned id " << d._id;
}

void MainWindow::deleteBtnClicked()
{

}
