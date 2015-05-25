#ifndef __SKIN_WIDGET_H
#define __SKIN_WIDGET_H

#include "xpushbutton.h"
#include "xskinitem.h"

class QHBoxLayout;
class QLabel;
class QGridLayout;

class XSkinWidget : public QWidget
{
	Q_OBJECT

public:

    explicit XSkinWidget(QWidget *parent = 0);
	void translateLanguage();

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

signals:

	void changeSkin(QString skin_name);

private slots:

	void showSkin(QString page_count);
	void varyfySkin(QString skin_name);

private:

	void initTitle();
	void initCenter();
	void initBottom();

private:

	QHBoxLayout *title_layout;
	QGridLayout *center_layout;
	QHBoxLayout *bottom_layout;

	QPoint move_point; //�ƶ��ľ���
	bool mouse_press; //����������
	QLabel *title_label; //����
	QLabel *title_icon_label; //����ͼ��
    XPushButton *close_button; //�رհ�ť
};

#endif // SKIN_WIDGET_H
