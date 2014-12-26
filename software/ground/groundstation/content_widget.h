#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <discoverpage.h>
#include <statuspage.h>
#include <copterctrlpage.h>
#include <coptersettingpage.h>
#include <upgradepage.h>
#include <plotingpage.h>

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

public slots:
    void turn_page(int index);

private:

	QSplitter *main_splitter;

    QStackedWidget *mainStackedWidget;

    DiscoverPage *discover_page;
    StatusPage *status_page;
    CopterCtrlPage *ctrl_page;
    CopterSettingPage *setting_page;
    PlotingPage *plot_page;
    UpgradePage *upgrade_page;

    QWidget *statusBar_widget;
	QLabel *icon_label; //云图标
	QLabel *connect_label; //成功连接云安全
	QLabel *version_label; //版本号
    QPushButton *version_button; //版本升级

    void initMainStackedWidget();
    void initStatusBar();
};

#endif // CONTENTWIDGET_H
