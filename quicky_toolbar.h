#ifndef QUICKY_TOOLBAR_H
#define QUICKY_TOOLBAR_H

#include <QWidget>
#include <QToolBar>

namespace Ui {
class quicky_toolbar;
}

class QuickyToolbar : public QToolBar
{
    Q_OBJECT

public:
    explicit QuickyToolbar(QWidget *parent = nullptr);
    ~QuickyToolbar();

private:
    Ui::quicky_toolbar *ui;
};

#endif // QUICKY_TOOLBAR_H
