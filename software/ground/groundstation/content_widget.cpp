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

    this->initLeft();
    this->initStatusBar();

    main_splitter->addWidget(left_widget);
    main_splitter->addWidget(this->statusBar_widget);



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

void ContentWidget::initLeft()
{
    left_widget = new QWidget();
    label = new QLabel();
    suggest_label = new QLabel();
    system_safe_label = new QLabel();
    power_button = new QPushButton();

    left_widget->resize(650, 500);

    QPixmap label_pixmap(":/contentWidget/computer");
    label->setPixmap(label_pixmap);
    label->setFixedSize(label_pixmap.size());

    QFont suggest_font = suggest_label->font();
    suggest_font.setPointSize(12);
    suggest_font.setBold(true);
    suggest_label->setFont(suggest_font);
    suggest_label->setStyleSheet("color:gray;");

    QFont system_safe_font = system_safe_label->font();
    system_safe_font.setBold(true);
    system_safe_label->setFont(system_safe_font);
    system_safe_label->setStyleSheet("color:gray;");

    QPixmap pixmap(":/contentWidget/power");
    power_button->setIcon(pixmap);
    power_button->setIconSize(pixmap.size());
    power_button->setFixedSize(180, 70);
    power_button->setStyleSheet("QPushButton{border-radius:5px; background:rgb(110, 190, 10); color:white;}"
        "QPushButton:hover{background:rgb(140, 220, 35);}");
    QFont power_font = power_button->font();
    power_font.setPointSize(16);
    power_button->setFont(power_font);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(suggest_label);
    v_layout->addWidget(system_safe_label);
    v_layout->addStretch();
    v_layout->setSpacing(15);
    v_layout->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(label, 0, Qt::AlignTop);
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->setSpacing(20);
    h_layout->setContentsMargins(30, 20, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(h_layout);
    main_layout->addWidget(power_button, 0, Qt::AlignCenter);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);
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
}

void ContentWidget::translateLanguage()
{
	suggest_label->setText(tr("suggest"));
	system_safe_label->setText(tr("system safe"));
	power_button->setText(tr("power"));

    connect_label->setText(tr("connect success"));
    version_label->setText(tr("version"));
}

