#include "stdafx.h"
#include "QtMiniGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtMiniGame window;
    window.show();
    return app.exec();
}
