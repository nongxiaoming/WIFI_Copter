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
	QPushButton *power_button; //������찴ť




    QWidget *statusBar_widget;
	QLabel *icon_label; //��ͼ��
	QLabel *connect_label; //�ɹ������ư�ȫ
	QLabel *version_label; //�汾��
    QPushButton *version_button; //�汾����

};

#endif // CONTENTWIDGET_H
