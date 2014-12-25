#include "statuspage.h"
#include "ui_statuspage.h"

StatusPage::StatusPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusPage)
{
    ui->setupUi(this);
}

StatusPage::~StatusPage()
{
    delete ui;
}
