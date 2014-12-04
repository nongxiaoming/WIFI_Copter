#ifndef XTITLEWIDGET_H
#define XTITLEWIDGET_H

#include "xpushbutton.h"
#include "xtoolbutton.h"

class QLabel;

class XTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit XTitleWidget(QWidget *parent = 0);
	void translateLanguage();

signals:
	void showSkin();
    void showMin();
    void showMax();
	void showMainMenu();
	void closeWidget(); 

public slots:

	void turnPage(QString current_page);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:

    QPoint press_point;//��갴��ȥ�ĵ�
    bool is_move;

	QLabel *version_title; //����
    XPushButton *skin_button; //����
    XPushButton *main_menu_button; //���˵�
    XPushButton *min_button; //��С��
    XPushButton *max_button; //���
    XPushButton *close_button; //�ر�

    QList<XToolButton *> button_list;
};

#endif // TITLEWIDGET_H
