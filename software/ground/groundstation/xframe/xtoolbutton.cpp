#include "xtoolbutton.h"

XToolButton::XToolButton(QString pic_name, QWidget *parent)
	:QToolButton(parent)
{
	//�����ı���ɫ
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
	setPalette(text_palette);

	//�����ı�����
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setWeight(QFont::Bold);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//����ͼ��
	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(pixmap.size());

	//���ô�С
	setFixedSize(pixmap.width()+25, pixmap.height()+27);
	setAutoRaise(true);

	setStyleSheet("background:transparent;");

	mouse_over = false;
	mouse_press = false;
}

XToolButton::~XToolButton()
{

}

void XToolButton::enterEvent(QEvent *)
{
	mouse_over = true;
}

void XToolButton::leaveEvent(QEvent *)
{
	mouse_over = false;
}

void XToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

void XToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void XToolButton::paintEvent(QPaintEvent *event)
{
	if(mouse_over)
	{
		//��������Ƶ���ť�ϵİ�ťЧ��
		painterInfo(0, 100, 150);
	}
	else
	{
		if(mouse_press)
		{
			painterInfo(0, 100, 150);
		}
	}

	QToolButton::paintEvent(event);
}

void XToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(230, 230, 230, top_color));
	linear.setColorAt(0.5, QColor(230, 230, 230, middle_color));
	linear.setColorAt(1, QColor(230, 230, 230, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
