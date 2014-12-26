#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include "xmainwindow.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

        XMainWindow w;
        w.showWidget();

        return a.exec();


}
