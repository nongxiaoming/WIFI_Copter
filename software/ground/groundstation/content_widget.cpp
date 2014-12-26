#include "content_widget.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QEvent>
#include <QPainter>

ContentWidget::ContentWidget(QWidget *parent)
	:QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
	
    main_splitter = new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Vertical);
    main_splitter->setHandleWidth(1);
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    this->initMainStackedWidget();
    this->initStatusBar();

    main_splitter->addWidget(this->mainStackedWidget);
    main_splitter->addWidget(this->statusBar_widget);
    main_splitter->setStretchFactor(0,1);
    for(int i = 0; i<main_splitter->count();i++)
    {
        QSplitterHandle *handle = main_splitter->handle(i);
        handle->setEnabled(false);
    }

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    this->translateLanguage();
}

void ContentWidget::initMainStackedWidget()
{
    this->mainStackedWidget = new QStackedWidget(this);
    this->discover_page = new DiscoverPage();
    this->status_page = new StatusPage();
    this->ctrl_page = new CopterCtrlPage;
    this->setting_page = new CopterSettingPage();
    this->plot_page = new PlotingPage();
    this->upgrade_page = new UpgradePage();
    this->mainStackedWidget->addWidget(this->discover_page);
    this->mainStackedWidget->addWidget(this->status_page);
    this->mainStackedWidget->addWidget(this->ctrl_page);
    this->mainStackedWidget->addWidget(this->setting_page);
    this->mainStackedWidget->addWidget(this->plot_page);
    this->mainStackedWidget->addWidget(this->upgrade_page);
    this->mainStackedWidget->setCurrentIndex(0);
    this->mainStackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ContentWidget::initStatusBar()
{
    this->statusBar_widget = new QWidget();
	icon_label = new QLabel();
	connect_label = new QLabel();
	version_label = new QLabel();
	version_button = new QPushButton();

	QPixmap label_pixmap(":/contentWidget/cloud");
	icon_label->setPixmap(label_pixmap);
	icon_label->setFixedSize(label_pixmap.size());

	QPixmap pixmap(":/contentWidget/version");
	version_button->setIcon(pixmap);
	version_button->setIconSize(pixmap.size());
	version_button->setFixedSize(20, 20);
	version_button->setStyleSheet("background:transparent;");

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(icon_label);
    hlayout->addWidget(connect_label);
    hlayout->addStretch();
    hlayout->addWidget(version_label);
    hlayout->addWidget(version_button);
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(10, 0, 10, 0);
    this->statusBar_widget->setLayout(hlayout);
    this->statusBar_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->statusBar_widget->setMinimumSize(0,24);
}
void ContentWidget::turn_page(int index)
{
 if(index != this->mainStackedWidget->currentIndex())
 {
    this->mainStackedWidget->setCurrentIndex(index);
 }
}
void ContentWidget::translateLanguage()
{

    connect_label->setText(tr("connect success"));
    version_label->setText(tr("version"));
}

