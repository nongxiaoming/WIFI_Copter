#ifndef PLOTINGPAGE_H
#define PLOTINGPAGE_H

#include <QWidget>
#include <QTimer>

class  QCustomPlot;


namespace Ui {
class PlotingPage;
}

class PlotingPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlotingPage(QWidget *parent = 0);
    ~PlotingPage();
private slots:
    void realtimeDataSlot();
private:
   void setupRealtimeDataDemo(QCustomPlot *customPlot);
    Ui::PlotingPage *ui;
   QTimer dataTimer;
};

#endif // PLOTINGPAGE_H
