#include "xskinwidget.h"
#include "util.h"
#include <QVBoxLayout>
#include <QLabel>

XSkinWidget::XSkinWidget(QWidget *parent)
        :QDialog(parent)
{
	this->resize(620, 445);

	//��ʼ��Ϊδ����������
	mouse_press = false;

	//���ñ���������
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	this->initTitle();

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(title_layout);
	main_layout->addStretch();
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	setLayout(main_layout);
}
void XSkinWidget::changeSkin(QString skin_name)
{
    this->skin_name = skin_name;
}
int XSkinWidget::show()
{
 return 0;
}
void XSkinWidget::initTitle()
{
	title_label = new QLabel();
	title_icon_label = new QLabel();
        close_button = new XPushButton();

	QPixmap title_pixmap(":/img/safe");
	title_icon_label->setPixmap(title_pixmap);
	title_icon_label->setFixedSize(16, 16);
	title_icon_label->setScaledContents(true);

	close_button->loadPixmap(":/sysButton/close");
	title_label->setFixedHeight(30);

	title_layout = new QHBoxLayout();
	title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
	title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
	title_layout->addStretch();
	title_layout->addWidget(close_button, 0, Qt::AlignTop);
	title_layout->setSpacing(5);
	title_layout->setContentsMargins(10, 0, 5, 0);

	title_label->setStyleSheet("color:white;");
	connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
}

void XSkinWidget::paintEvent(QPaintEvent *)
{

	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(skin_name));

	QPainter painter2(this);
	QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
	linear2.setColorAt(0, Qt::white);
	linear2.setColorAt(0.5, Qt::white);
	linear2.setColorAt(1, Qt::white);
	painter2.setPen(Qt::white); //�趨������ɫ����ʱ����Ǳ߿���ɫ
	painter2.setBrush(linear2);
	painter2.drawRect(QRect(0, 30, this->width(), this->height()-30));

	QPainter painter3(this);
	painter3.setPen(Qt::gray);
	static const QPointF points[4] = {QPointF(0, 30), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 30)};
	painter3.drawPolyline(points, 4);
}

void XSkinWidget::mousePressEvent( QMouseEvent * event )
{
	//ֻ�����������ƶ��͸ı��С
	if(event->button() == Qt::LeftButton) 
	{
		mouse_press = true;
	}

	//�����ƶ�����
	move_point = event->globalPos() - pos(); 
}

void XSkinWidget::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void XSkinWidget::mouseMoveEvent(QMouseEvent *event)
{
	//�ƶ�����
	if(mouse_press)   
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}
