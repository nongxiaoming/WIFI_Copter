#include "discoverpage.h"
#include "ui_discoverpage.h"

DiscoverPage::DiscoverPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiscoverPage)
{
    ui->setupUi(this);
}

DiscoverPage::~DiscoverPage()
{
    delete ui;
}
