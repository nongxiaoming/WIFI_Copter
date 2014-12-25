#ifndef PLOTINGPAGE_H
#define PLOTINGPAGE_H

#include <QWidget>

namespace Ui {
class PlotingPage;
}

class PlotingPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlotingPage(QWidget *parent = 0);
    ~PlotingPage();

private:
    Ui::PlotingPage *ui;
};

#endif // PLOTINGPAGE_H
