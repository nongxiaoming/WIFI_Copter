#include "upgradepage.h"
#include "ui_upgradepage.h"

UpgradePage::UpgradePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpgradePage)
{
    ui->setupUi(this);
}

UpgradePage::~UpgradePage()
{
    delete ui;
}
