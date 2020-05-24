#include "NoteData.h"
#include "NoteWindows.h"

NoteData::NoteData(Data data, QWidget *parent, QString menutitle)
{
    window = new MainWindow(data, parent);
    action = new QAction(data.title());
    connect(window, &MainWindow::windowTitleChanged, [this](QString title) {  this->action->setText(title); });
}

NoteData::~NoteData()
{
    delete window;
    delete action;
}
