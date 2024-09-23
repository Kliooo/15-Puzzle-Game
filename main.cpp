#include <QApplication>
#include "15_Puzzle_Game.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    bva::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
