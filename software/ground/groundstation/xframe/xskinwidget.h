#ifndef __SKIN_WIDGET_H
#define __SKIN_WIDGET_H

#include <QDialog>
#include "xpushbutton.h"

class QHBoxLayout;
class QLabel;
class QGridLayout;

class XSkinWidget : public QDialog
{
	Q_OBJECT

public:

    explicit XSkinWidget(QWidget *parent = 0);
    int show();

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);


private slots:

    void changeSkin(QString skin_name);

private:

	void initTitle();

private:

	QHBoxLayout *title_layout;

	QPoint move_point; //移动的距离
	bool mouse_press; //按下鼠标左键
	QLabel *title_label; //标题
	QLabel *title_icon_label; //标题图标
    XPushButton *close_button; //关闭按钮
    QString skin_name;

};

#endif // SKIN_WIDGET_H
