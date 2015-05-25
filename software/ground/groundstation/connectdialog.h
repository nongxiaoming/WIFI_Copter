#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "xframe/xskinwidget.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public XSkinWidget
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
