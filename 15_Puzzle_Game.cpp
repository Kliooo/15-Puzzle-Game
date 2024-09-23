#include "15_Puzzle_Game.hpp"
#include "loginform.hpp"
#include "levelselect.hpp"
#include "puzzle.hpp"

bva::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), selectedLevel(0), levelOffset(0)
{
    setupInterface();
    setupConnections();
}

bva::MainWindow::~MainWindow()
{
}

void bva::MainWindow::setupInterface()
{
    resize(300, 150);
    setMinimumSize(220, 100);
    setWindowTitle("Login Window");

    setWindowIcon(QIcon(":avatar.jpg"));

    loginButton = new QPushButton("Login");
    playButton = new QPushButton("Play");
    exitButton = new QPushButton("Exit");

    playButton->hide();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(loginButton);
    layout->addWidget(playButton);
    layout->addWidget(exitButton);

    QWidget *loginWindow = new QWidget(this);
    loginWindow->setLayout(layout);
    setCentralWidget(loginWindow);

    loginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    playButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    loginButton->setStyleSheet("background-color: green; color: white; border-radius: 15px;");
    playButton->setStyleSheet("background-color: green; color: white; border-radius: 10px;");
    exitButton->setStyleSheet("background-color: red; color: white; border-radius: 15px;");
}

void bva::MainWindow::setupConnections()
{
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
}

void bva::MainWindow::onLoginButtonClicked()
{
    LoginForm loginForm(this);
    if (loginForm.exec() == QDialog::Accepted) {
        QString enteredID = loginForm.getID();
        QString enteredPassword = loginForm.getPassword();

        if (enteredID == "VIP" && enteredPassword == "666") {
            levelOffset = 11;
        } else if (!enteredID.isEmpty() && !enteredPassword.isEmpty()) {
            levelOffset = 1;
        }

        if (!enteredID.isEmpty() && !enteredPassword.isEmpty()) {
            loginButton->setText(enteredID);
            loginButton->setStyleSheet("background-color: grey; color: white; border-radius: 10px;");
            loginButton->setEnabled(false);

            exitButton->setText("Log out");

            disconnect(exitButton, nullptr, nullptr, nullptr);
            connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);

            playButton->show();

            QDialog *dialog = qobject_cast<QDialog *>(sender()->parent());
            if (dialog) {
                dialog->accept();
            }
        }
    }
}

void bva::MainWindow::onExitButtonClicked()
{
    if (loginButton->text() == "Login") {
        qApp->quit();
    } else {
        loginButton->setText("Login");
        loginButton->setStyleSheet("background-color: green; color: white; border-radius: 15px;");
        loginButton->setEnabled(true);

        exitButton->setText("Exit");
        playButton->hide();

        selectedLevel = 0;
        levelOffset = 0;
    }
}

void bva::MainWindow::onPlayButtonClicked()
{
    LevelSelect levelSelectDialog(this, levelOffset);
    connect(&levelSelectDialog, &LevelSelect::levelSelected, this, &MainWindow::onLevelButtonClicked);
    levelSelectDialog.exec();
}

void bva::MainWindow::onLevelButtonClicked(int level)
{
    if (levelOffset == 11) {
        selectedLevel = level * 11;
    } else {
        selectedLevel = level;
    }

    Puzzle *puzzleGame = new Puzzle(this, selectedLevel);
    puzzleGame->exec();
}
