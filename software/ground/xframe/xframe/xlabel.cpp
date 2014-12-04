#include "xlabel.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QHBoxLayout>


XLabel::XLabel(QWidget *parent) :
    QWidget(parent)
{
    initVariable();
    initSetupUi();
}

XLabel::~XLabel()
{
    delete m_pLabelIcon;
    delete m_pLabelText;
    delete m_pHLayout;
}

void XLabel::setPixmap(const QPixmap &pixmap)
{
    m_pLabelIcon->setPixmap(pixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void XLabel::setText(const QString &text)
{
    m_pLabelText->setText(text);
}

void XLabel::setMouseEnterFlag(bool flag)
{
    m_mouseEnterFlag = flag;
    this->update();
}

void XLabel::setMousePressFlag(bool flag)
{
    m_mousePressFlag = flag;
    this->update();
}

void XLabel::enterEvent(QEvent *)
{
    if(!getMousePressFlag())
    {
        setMouseEnterFlag(true);
    }
    this->setCursor(Qt::PointingHandCursor);
}

void XLabel::leaveEvent(QEvent *)
{
    setMouseEnterFlag(false);
}

void XLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        setMousePressFlag(true);
        emit signalLabelPress(this);
    }
}

void XLabel::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    if(getMouseEnterFlag())
    {
        paintWidget(50, &painter);
    }
    else if(getMousePressFlag())
    {
        paintWidget(80, &painter);
    }

    QWidget::paintEvent(e);
}

void XLabel::initVariable()
{
    setMouseEnterFlag(false);
    setMousePressFlag(false);
}

void XLabel::initSetupUi()
{
    createFrame();
    createWidget();
    createLayout();
}

void XLabel::createFrame()
{
    this->setStyleSheet("QWidget {background:transparent;border:0px;color:white;font-weight:bold;font-size:16px;}");
}

void XLabel::createWidget()
{
    m_pLabelIcon = new QLabel(this);
    m_pLabelText = new QLabel(this);
}

void XLabel::createLayout()
{
    m_pHLayout = new QHBoxLayout;
    m_pHLayout->setSpacing(10);
    m_pHLayout->setContentsMargins(QMargins(5, 0, 5, 0));
    m_pHLayout->addWidget(m_pLabelIcon);
    m_pHLayout->addWidget(m_pLabelText);
	m_pHLayout->addStretch();

    this->setLayout(m_pHLayout);
}

void XLabel::paintWidget(int transparency, QPainter *device)
{
    QPen pen(Qt::NoBrush, 1);
    device->setPen(pen);
    QLinearGradient linear(this->rect().topLeft(), this->rect().bottomLeft());
    linear.setColorAt(0, QColor(255, 255, 255, transparency));

    QBrush brush(linear);
    device->setBrush(brush);
    device->drawRoundedRect(this->rect(), 2, 2);
}

inline bool XLabel::getMouseEnterFlag()
{
    return m_mouseEnterFlag;
}

inline bool XLabel::getMousePressFlag()
{
    return m_mousePressFlag;
}
