#include "quicky_toolbar.h"
#include "ui_quicky_toolbar.h"

QuickyToolbar::QuickyToolbar(QWidget *parent) :
    QToolBar(parent),
    parent(parent),
    ui(new Ui::quicky_toolbar)
{
    ui->setupUi(this);

    connect(ui->newNoteBtn, &QAction::triggered, this, &QuickyToolbar::newMenuAction);
    connect(ui->deleteNoteBtn, &QAction::triggered, this, &QuickyToolbar::deleteMenuAction);
    connect(ui->bgColorBtn, &QAction::triggered, this, &QuickyToolbar::bgColorMenuAction);
}

QuickyToolbar::~QuickyToolbar()
{
    delete ui;
}

void QuickyToolbar::newMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::NewNote);
}

void QuickyToolbar::deleteMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::DeleteNote);
}

void QuickyToolbar::bgColorMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::BgColorNote);
}
