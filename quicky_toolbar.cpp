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
    connect(ui->actionBoldBtn, &QAction::triggered, this, &QuickyToolbar::boldMenuAction);
    connect(ui->actionItalicBtn, &QAction::triggered, this, &QuickyToolbar::italicMenuAction);
    connect(ui->actionUnderlineBtn, &QAction::triggered, this, &QuickyToolbar::underlineMenuAction);
    connect(ui->textColorBtn, &QAction::triggered, this, &QuickyToolbar::textColorMenuAction);
    connect(ui->strikeoutNoteBtn, &QAction::triggered, this, &QuickyToolbar::strikeoutMenuAction);
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

void QuickyToolbar::boldMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::BoldNote);
}

void QuickyToolbar::italicMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::ItalicNote);
}

void QuickyToolbar::underlineMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::UnderlineNote);
}

void QuickyToolbar::textColorMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::TextColorNote);
}

void QuickyToolbar::strikeoutMenuAction(bool status)
{
    emit menuActionTriggered(status,parent, MenuItem::StrikeOutNote);
}
