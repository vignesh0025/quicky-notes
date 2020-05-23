#include "mainwindow.h"
#include <QDateTime>
#include <QBuffer>
#include <QColorDialog>
#include "qnamespace.h"
#include "qtextcursor.h"
#include "qtextformat.h"
#include "qwindowdefs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Data data, QWidget *parent)
    : QMainWindow(parent, Qt::Tool)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    self_gui_update_ongoing = true;

    d = data;

    timer.setInterval(1000);
    timer.setSingleShot(true);

    // Perform UI additions before adding data
    toolbar = new QuickyToolbar(this);
    this->addToolBar(Qt::BottomToolBarArea, toolbar);

    updateUI();

    // Connect Events only after updating the UI so no signals are sent
    connect(ui->notes, &QTextEdit::textChanged, this, &MainWindow::noteChanged);
    connect(ui->title, &QLineEdit::textChanged, this, &MainWindow::noteChanged);

    connect(&timer, &QTimer::timeout, this, &MainWindow::timeOut);
}

void MainWindow::updateUI()
{
    this->ui->id->display(d.id());
    this->ui->title->setText(d.title());
    this->ui->notes->setHtml(d.notes());
    this->ui->statusbar->showMessage(d.datetime());
    this->ui->notes->setStyleSheet(d.stylesheet());
    this->ui->title->setStyleSheet(d.stylesheet());
    qDebug() << d.pos() << d.size();
    this->move(d.pos());
    this->resize(d.size());
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

    d.setTitle(ui->title->text());
    d.setNote(ui->notes->toHtml());
    d.setGeomentry(this->pos(), this->size());
    d.setStyleSheet(ui->title->styleSheet());
    d.setId(emit noteUpdated(d));

    this->ui->id->display(d.id());
    qDebug() << "Returned id " << d.id();
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    if(d.id() != INVALID_NOTE)
    {
        timer.start();
        qDebug() << "Resized";
    }
    else {
        qDebug() << "Invalid Note";
    }
}

void MainWindow::moveEvent(QMoveEvent *ev)
{
    if(d.id() != INVALID_NOTE)
    {
        timer.start();
        qDebug() << "Moved";
    }
    else {
        qDebug() << "Invalid Note";
    }

}

void MainWindow::updateBgColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    this->ui->notes->setStyleSheet("background-color: " + color.name());
    this->ui->title->setStyleSheet("background-color: " + color.name());

    if(d.id() != INVALID_NOTE)
    {
        timer.start();
        qDebug() << "Moved";
    }
    else {
        qDebug() << "Invalid Note";
    }
}


void MainWindow::boldText(bool status)
{
    QTextCursor cursor = this->ui->notes->textCursor();
    QTextCharFormat fmt = cursor.blockCharFormat();
    fmt.setFontWeight(status? QFont::Bold: QFont::Normal);
    cursor.mergeCharFormat(fmt);

    if(status) this->ui->notes->setFontWeight(QFont::Bold);
        else this->ui->notes->setFontWeight(QFont::Normal);
}

void MainWindow::italicText(bool status)
{
    QTextCursor cursor = this->ui->notes->textCursor();
    QTextCharFormat fmt = cursor.blockCharFormat();
    fmt.setFontItalic(status);
    cursor.mergeCharFormat(fmt);

    this->ui->notes->setFontItalic(status);
}

void MainWindow::underlineText(bool status)
{

    QTextCursor cursor = this->ui->notes->textCursor();
    QTextCharFormat fmt = cursor.blockCharFormat();
    fmt.setFontUnderline(status);
    cursor.mergeCharFormat(fmt);

    this->ui->notes->setFontUnderline(status);

}
