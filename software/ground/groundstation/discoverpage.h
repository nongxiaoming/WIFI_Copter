#ifndef DISCOVERPAGE_H
#define DISCOVERPAGE_H

#include <QWidget>

namespace Ui {
class DiscoverPage;
}

class DiscoverPage : public QWidget
{
    Q_OBJECT

public:
    explicit DiscoverPage(QWidget *parent = 0);
    ~DiscoverPage();

private:
    Ui::DiscoverPage *ui;
};

#endif // DISCOVERPAGE_H
