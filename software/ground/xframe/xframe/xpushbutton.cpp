#include "xpushbutton.h"

XPushButton::XPushButton(QWidget *parent)
	:QPushButton(parent)
{	
	status = NORMAL;
	mouse_press = false;
}

XPushButton::~XPushButton()
{

}

void XPushButton::loadPixmap(QString pic_name)
{
	pixmap.load(pic_name);
	btn_width = pixmap.width()/4;
	btn_height = pixmap.height();
	setFixedSize(btn_width, btn_height);
}

void XPushButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void XPushButton::mousePressEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
}

void XPushButton::mouseReleaseEvent(QMouseEvent *)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if(mouse_press)
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void XPushButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void XPushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
}
