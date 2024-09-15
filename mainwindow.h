#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QRandomGenerator>
#include <QLabel>
#include <QIcon>
#include <QBuffer>
#include <QPixmap>
#include <QImage>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setup_interface();
    void setup_connections();
    void shufflePuzzle(QList<QPushButton*>& cells, int &emptyRow, int &emptyCol, int gridSize);
    void checkWin(QList<QPushButton*>& cells, int gridSize);
    void startGame();

    int selectedLevel;

    int levelOffset;

    QPushButton *loginButton;
    QPushButton *playButton;
    QPushButton *exitButton;
    QPushButton *submitButton;

    QPushButton *level1Button;
    QPushButton *level2Button;
    QPushButton *level3Button;
    QPushButton *level4Button;
    QPushButton *level5Button;

    QPixmap winPixmap;

    QLabel *winLabel;

    QLineEdit *IDInput;
    QLineEdit *passwordInput;


};

#endif // MAINWINDOW_H
