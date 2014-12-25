#ifndef UPGRADEPAGE_H
#define UPGRADEPAGE_H

#include <QWidget>

namespace Ui {
class UpgradePage;
}

class UpgradePage : public QWidget
{
    Q_OBJECT

public:
    explicit UpgradePage(QWidget *parent = 0);
    ~UpgradePage();

private:
    Ui::UpgradePage *ui;
};

#endif // UPGRADEPAGE_H
