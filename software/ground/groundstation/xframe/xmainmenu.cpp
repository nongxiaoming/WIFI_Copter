#include "xmainmenu.h"

XMainMenu::XMainMenu(QWidget *widget)
	: QMenu(widget)
{
	this->createActions();
	this->translateActions();
}

void XMainMenu::createActions()
{
	//创建菜单项
	action_setting = new QAction(this);
    action_connect = new QAction(this);
	action_check_update = new QAction(this);
	action_about_us = new QAction(this);

	action_about_us->setIcon(QIcon(":/mainMenu/about"));
	action_check_update->setIcon(QIcon(":/mainMenu/update"));
	action_setting->setIcon(QIcon(":/mainMenu/setting"));

	//添加菜单项
	this->addAction(action_setting);
    this->addAction(action_connect);
	this->addSeparator();
    this->addAction(action_check_update);
	this->addAction(action_about_us);

	//设置信号连接
	QObject::connect(action_setting, SIGNAL(triggered()), this, SIGNAL(showSettingDialog()));
    QObject::connect(action_connect, SIGNAL(triggered()), this, SIGNAL(ShowConnectDialog()));
	QObject::connect(action_about_us, SIGNAL(triggered()), this, SIGNAL(showAboutUs()));
}

void XMainMenu::translateActions()
{
	action_setting->setText(tr("setting"));
    action_connect->setText(tr("connect"));
	action_check_update->setText(tr("check update"));
	action_about_us->setText(tr("about us"));
}
