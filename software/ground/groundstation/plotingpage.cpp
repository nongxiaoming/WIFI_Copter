#include "plotingpage.h"
#include "ui_plotingpage.h"

PlotingPage::PlotingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotingPage)
{
    ui->setupUi(this);
}

PlotingPage::~PlotingPage()
{
    delete ui;
}
