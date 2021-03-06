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

	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
};

#endif //XTOOlBUTTON_H
