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

    QPoint press_point;//鼠标按下去的点
    bool is_move;

	QLabel *version_title; //标题
    XPushButton *skin_button; //换肤
    XPushButton *main_menu_button; //主菜单
    XPushButton *min_button; //最小化
    XPushButton *max_button; //最大化
    XPushButton *close_button; //关闭

    QList<XToolButton *> button_list;
};

#endif // TITLEWIDGET_H
