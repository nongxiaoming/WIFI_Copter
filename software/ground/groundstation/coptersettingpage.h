#ifndef COPTERSETTINGPAGE_H
#define COPTERSETTINGPAGE_H

#include <QWidget>

namespace Ui {
class CopterSettingPage;
}

class CopterSettingPage : public QWidget
{
    Q_OBJECT

public:
    explicit CopterSettingPage(QWidget *parent = 0);
    ~CopterSettingPage();

private:
    Ui::CopterSettingPage *ui;
};

#endif // COPTERSETTINGPAGE_H
