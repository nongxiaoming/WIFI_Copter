#ifndef STATUSPAGE_H
#define STATUSPAGE_H

#include <QWidget>

namespace Ui {
class StatusPage;
}

class StatusPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPage(QWidget *parent = 0);
    ~StatusPage();

private:
    Ui::StatusPage *ui;
};

#endif // STATUSPAGE_H
