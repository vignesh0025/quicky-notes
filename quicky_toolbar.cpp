#include "quicky_toolbar.h"
#include "ui_quicky_toolbar.h"

QuickyToolbar::QuickyToolbar(QWidget *parent) :
    QToolBar(parent),
    ui(new Ui::quicky_toolbar)
{
    ui->setupUi(this);
}

QuickyToolbar::~QuickyToolbar()
{
    delete ui;
}
