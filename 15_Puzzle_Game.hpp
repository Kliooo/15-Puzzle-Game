#ifndef PUZZLE_GAME_15_HPP
#define PUZZLE_GAME_15_HPP

#include <QApplication>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

namespace bva {

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QPushButton *playButton;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QPushButton *exitButton;

    QString userId;

    int selectedLevel;
    int levelOffset;
    bool levelSelectOpen = false;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayButtonClicked();
    void onLoginButtonClicked();
    void onExitButtonClicked();
    void onLevelButtonClicked(int level);

private:
    void setupInterface();
    void setupConnections();
};

}

#endif
