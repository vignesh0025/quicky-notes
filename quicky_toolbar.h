#ifndef QUICKY_TOOLBAR_H
#define QUICKY_TOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QDebug>

#include "MenuItem.h"

namespace Ui {
class quicky_toolbar;
}

class QuickyToolbar : public QToolBar
{
    Q_OBJECT

public:
    explicit QuickyToolbar(QWidget *parent = nullptr);
    ~QuickyToolbar();
    QWidget *parent;

private slots:
    void newMenuAction(bool status);
    void deleteMenuAction(bool status);

signals:
    void menuActionTriggered(bool status, QWidget *parent, MenuItem item);

private:
    Ui::quicky_toolbar *ui;
};

#endif // QUICKY_TOOLBAR_H
