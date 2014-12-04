#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include "xtitlewidget.h"
#include "content_widget.h"
#include "system_tray.h"
#include "about_us.h"
#include "xmainmenu.h"
#include "character_widget.h"
//#include "setting_dialog.h"
#include "xskinmanager.h"

#include <QSystemTrayIcon>

class XMainWindow : public QDialog
{
    Q_OBJECT

public:

    XMainWindow(QWidget *parent = 0);
    ~XMainWindow();

protected:

    void paintEvent(QPaintEvent *);

public slots:

	void showWidget();

private slots:

	void showMax();
	void showSkinWidget();
	void showMainMenu();
	void showSettingDialog();
	void showAboutUs();
	void showNewCharacter();
	void changeSkin(QString skin_name);
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);

private:

	QRect location;
    XTitleWidget *title_widget; //标题栏
	ContentWidget *content_widget; //主界面内容
    //XSystemTray *system_tray; //托盘项
    //SettingDialog *setting_dialog; //设置界面
	CharacterWidget *character_widget; //新版特性界面
	AboutUsDialog *about_us_dialog; //关于我们界面
    QString skin_name;//主窗口背景图片的名称
    XMainMenu *main_menu; //主菜单
    XSkinManager *skin_manager; //皮肤管理界面

};

#endif // MAINWIDGET_H
