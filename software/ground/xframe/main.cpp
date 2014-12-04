#include "xframe/xmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    XMainWindow mainwindow;
    mainwindow.showWidget();

    return app.exec();
}
