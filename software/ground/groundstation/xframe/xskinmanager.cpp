#include "xskinmanager.h"
#include "util.h"
#include <QVBoxLayout>
#include <QLabel>

XSkinManager::XSkinManager(QWidget *parent)
	:QWidget(parent)
{
	this->resize(620, 445);

	//初始化为未按下鼠标左键
	mouse_press = false;
	skin_name = QString("");
	is_change = false;
	current_page = 1;

	//设置标题栏隐藏
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	this->initTitle();
	this->initCenter();
	this->initBottom();

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(title_layout);
	main_layout->addLayout(center_layout);
	main_layout->addLayout(bottom_layout);
	main_layout->addStretch();
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	setLayout(main_layout);

	this->translateLanguage();

	this->showSkin(QString::number(current_page, 10));
}

void XSkinManager::initTitle()
{
	title_label = new QLabel();
	title_icon_label = new QLabel();
    close_button = new XPushButton();

	QPixmap title_pixmap(":/img/safe");
	title_icon_label->setPixmap(title_pixmap);
	title_icon_label->setFixedSize(16, 16);
	title_icon_label->setScaledContents(true);

	close_button->loadPixmap(":/sysButton/close");
	title_label->setFixedHeight(30);

	title_layout = new QHBoxLayout();
	title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
	title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
	title_layout->addStretch();
	title_layout->addWidget(close_button, 0, Qt::AlignTop);
	title_layout->setSpacing(5);
	title_layout->setContentsMargins(10, 0, 5, 0);

	title_label->setStyleSheet("color:white;");
	connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
}

void XSkinManager::initCenter()
{
    skin_list<<":/skins/0"<<":/skins/1"<<":/skins/2"<<":/skins/3"<<":/skins/4"<<
        ":/skins/5"<<":/skins/6"<<":/skins/7"<<":/skins/8"<<":/skins/9"<<
        ":/skins/10"<<":/skins/11"<<":/skins/12"<<":/skins/13"<<":/skins/14"<<
        ":/skins/15"<<":/skins/16"<<":/skins/17"<<":/skins/18"<<":/skins/19"<<
        ":/skins/20"<<":/skins/21"<<":/skins/22"<<":/skins/23";

	center_layout = new QGridLayout();
	center_layout->setSpacing(5);
	center_layout->setContentsMargins(5, 35, 5, 0);

    skin_item_0 = new XSkinItem();
    skin_item_1 = new XSkinItem();
    skin_item_2 = new XSkinItem();
    skin_item_3 = new XSkinItem();
    skin_item_4 = new XSkinItem();
    skin_item_5 = new XSkinItem();
    skin_item_6 = new XSkinItem();
    skin_item_7 = new XSkinItem();

    connect(skin_item_0, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_1, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_2, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_3, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_4, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_5, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_6, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(skin_item_7, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));

    center_layout->addWidget(skin_item_0, 0, 0);
    center_layout->addWidget(skin_item_1, 0, 1);
    center_layout->addWidget(skin_item_2, 0, 2);
    center_layout->addWidget(skin_item_3, 0, 3);
    center_layout->addWidget(skin_item_4, 1, 0);
    center_layout->addWidget(skin_item_5, 1, 1);
    center_layout->addWidget(skin_item_6, 1, 2);
    center_layout->addWidget(skin_item_7, 1, 3);

	int skin_list_count = skin_list.size();
	page_count = skin_list_count / 8;
	page_count_point = skin_list_count % 8;
	if(page_count_point > 0)
	{
		page_count = page_count + 1;
	}
}

void XSkinManager::initBottom()
{
	QSignalMapper *signal_mapper = new QSignalMapper(this);
	QList<QPushButton *> *button_list = new QList<QPushButton *>();
	for(int i=0; i<page_count; i++)
	{
		QPushButton *page_button = new QPushButton();
		page_button->setFixedWidth(20);
		page_button->setText(QString::number(i+1, 10));
		page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
		page_button->setCursor(Qt::PointingHandCursor);
		connect(page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
		signal_mapper->setMapping(page_button, page_button->text());
		button_list->push_back(page_button);
	}

	first_page_button = new QPushButton();
	previous_page_button = new QPushButton();
	next_page_button = new QPushButton();
	last_page_button = new QPushButton();
	first_page_button->setFixedWidth(50);
	previous_page_button->setFixedWidth(50);
	next_page_button->setFixedWidth(50);
	last_page_button->setFixedWidth(50);
	first_page_button->setCursor(Qt::PointingHandCursor);
	previous_page_button->setCursor(Qt::PointingHandCursor);
	next_page_button->setCursor(Qt::PointingHandCursor);
	last_page_button->setCursor(Qt::PointingHandCursor);
	first_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
	previous_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
	next_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
	last_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");

    first_page_button->setText(tr("first"));
    previous_page_button->setText(tr("previous"));
    next_page_button->setText(tr("next"));
    last_page_button->setText(tr("last"));

	connect(first_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
	connect(previous_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
	connect(next_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
	connect(last_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
	signal_mapper->setMapping(first_page_button, "first");
	signal_mapper->setMapping(previous_page_button, "previous");
	signal_mapper->setMapping(next_page_button, "next");
	signal_mapper->setMapping(last_page_button, "last");
	connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(showSkin(QString)));

	bottom_layout = new QHBoxLayout();
	bottom_layout->addStretch();
	bottom_layout->addWidget(first_page_button, 0, Qt::AlignVCenter);
	bottom_layout->addWidget(previous_page_button, 0, Qt::AlignVCenter);
	for(int i=0; i<button_list->count(); i++)
	{
		QPushButton *page_button = button_list->at(i);
		bottom_layout->addWidget(page_button, 0, Qt::AlignVCenter);
	}
	bottom_layout->addWidget(next_page_button, 0, Qt::AlignVCenter);
	bottom_layout->addWidget(last_page_button, 0, Qt::AlignVCenter);
	bottom_layout->addStretch();
	bottom_layout->setSpacing(2);
	bottom_layout->setContentsMargins(0, 10, 0, 0);
}

void XSkinManager::showSkin(QString current_skin)
{
	if(current_skin == "first")
	{
		current_page = 1;
	}
	else if(current_skin == "previous")
	{
		if(current_page > 2)
		{
			current_page = current_page - 1;
		}
	}
	else if(current_skin == "next")
	{
		if(current_page < page_count)
		{
			current_page = current_page + 1;
		}
	}
	else if(current_skin == "last")
	{
		current_page = page_count;
	}
	else
	{
		bool ok;  
		current_page = current_skin.toInt(&ok, 10);
	}

	if(current_page == 1)
	{
		next_page_button->show();
		last_page_button->show();
		first_page_button->hide();
		previous_page_button->hide();
	}
	else if(current_page == page_count)
	{
		first_page_button->show();
		previous_page_button->show();
		next_page_button->hide();
		last_page_button->hide();
	}
	else
	{
		first_page_button->hide();
		previous_page_button->show();
		next_page_button->show();
		last_page_button->hide();
	}

	//第一页为0-7 显示至previous_total_page个
	int previous_total_page = (current_page - 1)*8;
	int tip_index = previous_total_page;
	if(previous_total_page > 0)
	{
		tip_index = previous_total_page - 1;
	}
    skin_item_0->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_1->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_2->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_3->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_4->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_5->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_6->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    skin_item_7->changeSkin(":/skins/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
}

void XSkinManager::translateLanguage()
{
	title_label->setText(tr("title"));
	close_button->setToolTip(tr("close"));

	tip_list<<tr("profound life")<<tr("blue sea")<<tr("red heart")<<tr("lovely baby")<<tr("transparent water")<<
		tr("flower")<<tr("great sunshine")<<tr("shadow amazement")<<tr("360 pet")<<tr("beautiful stone")<<
		tr("yellow energy")<<tr("magic world")<<tr("intense emotion")<<tr("dream sky")<<tr("angry bird")<<
		tr("graceful jazz")<<tr("card")<<tr("summer cool")<<tr("blue world")<<tr("woodwind")<<
		tr("pink mood")<<tr("across time")<<tr("six year");
}

void XSkinManager::varyfySkin(QString skin_name)
{
	this->skin_name = skin_name;
	is_change = true;
	update();
	emit changeSkin(skin_name);
}

void XSkinManager::paintEvent(QPaintEvent *)
{
	if(!is_change)
	{
        bool is_read = Util::readInit(QString("./user.ini"), QString("skin"), skin_name);
		if(is_read)
		{
			if(skin_name.isEmpty())
			{
                skin_name = QString(":/skins/17_big");
			}
		}
		else
		{
            skin_name = QString(":/skins/17_big");
		}
	}
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(skin_name));

	QPainter painter2(this);
	QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
	linear2.setColorAt(0, Qt::white);
	linear2.setColorAt(0.5, Qt::white);
	linear2.setColorAt(1, Qt::white);
	painter2.setPen(Qt::white); //设定画笔颜色，到时侯就是边框颜色
	painter2.setBrush(linear2);
	painter2.drawRect(QRect(0, 30, this->width(), this->height()-30));

	QPainter painter3(this);
	painter3.setPen(Qt::gray);
	static const QPointF points[4] = {QPointF(0, 30), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 30)};
	painter3.drawPolyline(points, 4);
}

void XSkinManager::mousePressEvent( QMouseEvent * event )
{
	//只能是鼠标左键移动和改变大小
	if(event->button() == Qt::LeftButton) 
	{
		mouse_press = true;
	}

	//窗口移动距离
	move_point = event->globalPos() - pos(); 
}

void XSkinManager::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void XSkinManager::mouseMoveEvent(QMouseEvent *event)
{
	//移动窗口
	if(mouse_press)   
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}
