#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VBEK::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
