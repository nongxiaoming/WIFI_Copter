#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include "xtitlewidget.h"
#include "content_widget.h"
#include "system_tray.h"
#include "about_us.h"
#include "main_menu.h"
#include "character_widget.h"
#include "setting_dialog.h"
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
    XTitleWidget *title_widget; //������
	ContentWidget *content_widget; //����������
	SystemTray *system_tray; //������
	SettingDialog *setting_dialog; //���ý���
	CharacterWidget *character_widget; //�°����Խ���
	AboutUsDialog *about_us_dialog; //�������ǽ���
    QString skin_name;//�����ڱ���ͼƬ������
	MainMenu *main_menu; //���˵�
    XSkinManager *skin_manager; //Ƥ���������

};

#endif // MAINWIDGET_H
