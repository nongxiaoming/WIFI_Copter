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
	void showNewCharacter();
	void showAboutUs();

private:
	
	void createActions();

private:

	QAction *action_setting; //����
	QAction *action_new_character; //�°�����
	QAction *action_check_update; //������
	QAction *action_change_company; //�л�Ϊ��ҵ��
	QAction *action_help_online; //���߰���
	QAction *action_platform_help; //��̳����
	QAction *action_login_home; //360��վ
	QAction *action_protect; //��˽����
	QAction *action_about_us; //��������

};

#endif //MAINMENU_H