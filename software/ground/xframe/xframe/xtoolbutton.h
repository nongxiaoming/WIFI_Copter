#ifndef XTOOlBUTTON_H
#define XTOOlBUTTON_H

#include <QtGui>
#include <QToolButton>
class XToolButton : public QToolButton
{

public:

    explicit XToolButton(QString pic_name, QWidget *parent = 0);
    ~XToolButton();
	void setMousePress(bool mouse_press);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);

public:

	bool mouse_over; //����Ƿ��ƹ�
	bool mouse_press; //����Ƿ���
};

#endif //XTOOlBUTTON_H
