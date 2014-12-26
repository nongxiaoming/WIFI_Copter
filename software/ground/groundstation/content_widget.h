#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>

class QSplitter;
class QPushButton;
class QLabel;
class QToolButton;
class QProgressBar;


class ContentWidget : public QWidget
{
    Q_OBJECT

public:

    explicit ContentWidget(QWidget *parent = 0);
	void translateLanguage();

private:

	void initLeft();
    void initStatusBar();

private:

	QSplitter *main_splitter;

	QWidget *left_widget;
	QLabel *label;
	QLabel *suggest_label;
	QLabel *system_safe_label;
	QPushButton *power_button; //立即体检按钮




    QWidget *statusBar_widget;
	QLabel *icon_label; //云图标
	QLabel *connect_label; //成功连接云安全
	QLabel *version_label; //版本号
    QPushButton *version_button; //版本升级

};

#endif // CONTENTWIDGET_H
