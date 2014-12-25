#include "coptersettingpage.h"
#include "ui_coptersettingpage.h"

CopterSettingPage::CopterSettingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopterSettingPage)
{
    ui->setupUi(this);
}

CopterSettingPage::~CopterSettingPage()
{
    delete ui;
}
