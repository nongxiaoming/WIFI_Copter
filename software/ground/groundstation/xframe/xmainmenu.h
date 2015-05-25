#ifndef XMAINMENU_H
#define XMAINMENU_H

#include <QMenu>

class XMainMenu : public QMenu
{
	Q_OBJECT

public:

    explicit XMainMenu(QWidget *parent = 0);

	void translateActions();

signals:

	void showSettingDialog();
    void ShowConnectDialog();
	void showAboutUs();

private:
	
	void createActions();

private:

	QAction *action_setting; //设置
    QAction *action_connect; //connect action
	QAction *action_check_update; //检查更新
	QAction *action_about_us; //关于我们

};

#endif //MAINMENU_H
