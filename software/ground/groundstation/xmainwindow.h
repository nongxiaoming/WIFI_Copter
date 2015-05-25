#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H
#include <QDialog>
#include "xtitlewidget.h"
#include "content_widget.h"
#include "xframe/system_tray.h"
#include "xframe/xmainmenu.h"
#include "xframe/character_widget.h"
#include "xframe/xskinmanager.h"
#include "connectdialog.h"
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
    void ShowConnectDialog();
	void changeSkin(QString skin_name);
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);

private:

	QRect location;
    XTitleWidget *title_widget; //������
	ContentWidget *content_widget; //����������
    //XSystemTray *system_tray; //������
    //SettingDialog *setting_dialog; //���ý���
    ConnectDialog *connect_dialog;
	CharacterWidget *character_widget; //�°����Խ���
    QString skin_name;//�����ڱ���ͼƬ������
    XMainMenu *main_menu; //���˵�
    XSkinManager *skin_manager; //Ƥ���������

};

#endif // MAINWIDGET_H
