#ifndef COPTERCTRLPAGE_H
#define COPTERCTRLPAGE_H

#include <QWidget>

namespace Ui {
class CopterCtrlPage;
}

class CopterCtrlPage : public QWidget
{
    Q_OBJECT

public:
    explicit CopterCtrlPage(QWidget *parent = 0);
    ~CopterCtrlPage();

private:
    Ui::CopterCtrlPage *ui;
};

#endif // COPTERCTRLPAGE_H
