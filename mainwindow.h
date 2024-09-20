#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

namespace VBEK {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayButtonClicked();
    void onLoginButtonClicked();
    void onExitButtonClicked();
    void onLevelButtonClicked(int level);

private:
    bool levelSelectOpen = false;

    int selectedLevel;
    int levelOffset;

    void setupInterface();
    void setupConnections();

    QPushButton *playButton;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QPushButton *exitButton;

    QString userId;
};

}

#endif // MAINWINDOW_H
