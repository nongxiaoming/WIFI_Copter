#include "xtitlewidget.h"
#include "xframe/xtoolbutton.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

XTitleWidget::XTitleWidget(QWidget *parent)
	:QWidget(parent)
{
    version_title = new QLabel();
    skin_button = new XPushButton();
    main_menu_button = new XPushButton();
    min_button = new XPushButton();
    max_button = new XPushButton();
    close_button = new XPushButton();

	version_title->setStyleSheet("color:white;");

	//ÉèÖÃÍ¼Æ¬
	skin_button->loadPixmap(":/sysButton/skin_button");
	main_menu_button->loadPixmap(":/sysButton/main_menu");
	min_button->loadPixmap(":/sysButton/min_button");
	max_button->loadPixmap(":/sysButton/max_button");
	close_button->loadPixmap(":/sysButton/close_button");

	connect(skin_button, SIGNAL(clicked()), this, SIGNAL(showSkin()));
	connect(main_menu_button, SIGNAL(clicked()), this, SIGNAL(showMainMenu()));
	connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
	connect(max_button, SIGNAL(clicked()), this, SIGNAL(showMax()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(skin_button, 0, Qt::AlignTop);
    title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(max_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
	title_layout->setSpacing(0);
	title_layout->setContentsMargins(0, 0, 5, 0);
	version_title->setContentsMargins(15, 0, 0, 0);
	skin_button->setContentsMargins(0, 0, 10, 0);

	QStringList string_list;
    string_list<<":/toolWidget/search"<<":/toolWidget/status"<<":/toolWidget/control"<<":/toolWidget/settings"
       <<":/toolWidget/plot"<<":/toolWidget/fw_update";

	QHBoxLayout *button_layout = new QHBoxLayout();

	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for(int i=0; i<string_list.size(); i++)
	{
        XToolButton *tool_button = new XToolButton(string_list.at(i));
		button_list.append(tool_button);
		connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, i);

		button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
	}
    connect(signal_mapper, SIGNAL(mapped(int)), this, SLOT(turnPage(int)));
	
    //QPushButton *conn_button = new QPushButton();
    //QPixmap pixmap(":/toolWidget/search");
    //QIcon icon(":/toolWidget/search");
    //conn_button->setPixmap(pixmap);
    //conn_button->setIcon(icon);
    //logo_label->setFixedSize(pixmap.size());
    //conn_button->setContentsMargins(0, 0, 40, 0);
   // conn_button->setCursor(Qt::PointingHandCursor);

	button_layout->addStretch();
    //button_layout->addWidget(conn_button);
	button_layout->setSpacing(8);
	button_layout->setContentsMargins(15, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(title_layout);
	main_layout->addLayout(button_layout);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	this->translateLanguage();

    setLayout(main_layout);
    setFixedHeight(100);
    is_move = false;
}

void XTitleWidget::translateLanguage()
{
    version_title->setText(tr("xframe"));
	skin_button->setToolTip(tr("change skin"));
	main_menu_button->setToolTip(tr("main menu"));
	min_button->setToolTip(tr("minimize"));
	max_button->setToolTip(tr("maximize"));
	close_button->setToolTip(tr("close"));

    button_list.at(0)->setText(tr("Search"));
    button_list.at(1)->setText(tr("Status"));
    button_list.at(2)->setText(tr("Control"));
    button_list.at(3)->setText(tr("Settings"));
//	button_list.at(4)->setText(tr("clear"));
//	button_list.at(5)->setText(tr("optimize"));
    button_list.at(4)->setText(tr("Plot"));
    button_list.at(5)->setText(tr("FW Update"));
}

void XTitleWidget::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void XTitleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        static QWidget* parent_widget = this->parentWidget();
        QPoint parent_point = parent_widget->pos();
        parent_point.setX(parent_point.x() + e->x() - press_point.x());
        parent_point.setY(parent_point.y() + e->y() - press_point.y());
        parent_widget->move(parent_point);
    }
}

void XTitleWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
	{
		is_move = false;
	}
}

void XTitleWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    emit showMax();
}

void XTitleWidget::turnPage(int current_index)
{

	for(int i=0; i<button_list.count(); i++)
	{
        XToolButton *tool_button = button_list.at(i);
		if(current_index == i)
		{
			tool_button->setMousePress(true);
            emit PageIndexChanged(i);
		}
		else
		{
			tool_button->setMousePress(false);
		}
	}
}
