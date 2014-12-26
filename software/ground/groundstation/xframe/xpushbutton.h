#ifndef XPUSHBUTTON_H
#define XPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>


class XPushButton : public QPushButton
{
	Q_OBJECT

public:

    explicit XPushButton(QWidget *parent = 0);

    ~XPushButton();

	void loadPixmap(QString pic_name);

protected:

	void enterEvent(QEvent *);

	void leaveEvent(QEvent *);

	void mousePressEvent(QMouseEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);

	void paintEvent(QPaintEvent *);

private:

	//ö�ٰ�ť�ļ���״̬
	enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
	ButtonStatus status;
	QPixmap pixmap; 

	int btn_width; //��ť���
	int btn_height; //��ť�߶�
	bool mouse_press; //��ť����Ƿ���
};

#endif //XPUSHBUTTON_H
