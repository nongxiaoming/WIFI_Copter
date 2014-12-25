#include "copterctrlpage.h"
#include "ui_copterctrlpage.h"

CopterCtrlPage::CopterCtrlPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopterCtrlPage)
{
    ui->setupUi(this);
}

CopterCtrlPage::~CopterCtrlPage()
{
    delete ui;
}
