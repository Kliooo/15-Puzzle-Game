#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), selectedLevel(0), levelOffset(0)
{
    setup_interface();
    setup_connections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup_interface()
{
    resize(300, 150);
    setMinimumSize(220, 100);
    this->setWindowTitle("Login Window");

    setWindowIcon(QIcon("C:/Slava/Qt/15_Puzzle_Game_Images/assets/avatar.jpg"));

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

void MainWindow::setup_connections()
{
    connect(loginButton, &QPushButton::clicked, [this]() {
        QDialog *loginDialog = new QDialog(this);
        loginDialog->setWindowTitle("Login Form");
        loginDialog->resize(300, 120);
        loginDialog->setMinimumSize(150, 100);

        submitButton = new QPushButton("Submit", loginDialog);
        submitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        submitButton->setStyleSheet("background-color: green; color: white; border-radius: 8px;");

        IDInput = new QLineEdit(loginDialog);
        IDInput->setPlaceholderText("Enter your ID");
        IDInput->setMaxLength(20);

        passwordInput = new QLineEdit(loginDialog);
        passwordInput->setEchoMode(QLineEdit::Password);
        passwordInput->setPlaceholderText("Enter your password");
        passwordInput->setMaxLength(20);

        QVBoxLayout *formLayout = new QVBoxLayout;
        formLayout->addWidget(IDInput);
        formLayout->addWidget(passwordInput);
        formLayout->addWidget(submitButton);

        loginDialog->setLayout(formLayout);


        connect(submitButton, &QPushButton::clicked, [this, loginDialog]() {
            QString enteredID = IDInput->text();
            QString enteredPassword = passwordInput->text();

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
                connect(exitButton, &QPushButton::clicked, [this]() {
                    loginButton->setText("Login");
                    loginButton->setStyleSheet("background-color: green; color: white; border-radius: 15px;");
                    loginButton->setEnabled(true);

                    exitButton->setText("Exit");
                    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

                    playButton->hide();
                });

                playButton->show();
                loginDialog->accept();
            }
        });

        loginDialog->exec();
    });

    connect(playButton, &QPushButton::clicked, [this]() {
        QDialog *levelDialog = new QDialog(this);
        levelDialog->setWindowTitle("Select Level");
        levelDialog->resize(300, 350);

        level1Button = new QPushButton("Classic", levelDialog);
        level2Button = new QPushButton("Cats", levelDialog);
        level3Button = new QPushButton("Ryan Gosling", levelDialog);
        level4Button = new QPushButton("Sea and Beach", levelDialog);
        level5Button = new QPushButton("Satoru Gojo", levelDialog);

        if (levelOffset == 11) {
            level1Button->setText("Neko Girl 1");
            level2Button->setText("Random Woman");
            level3Button->setText("Black Square");
            level4Button->setText("Neko Girl 2");
            level5Button->setText("Dinosaurs");
        }

        level1Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        level2Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        level3Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        level4Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        level5Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        level1Button->setStyleSheet("background-color: white; color: black; border-radius: 10px;");
        level2Button->setStyleSheet("background-color: grey; color: black; border-radius: 10px;");
        level3Button->setStyleSheet("background-color: yellow; color: black; border-radius: 10px;");
        level4Button->setStyleSheet("background-color: turquoise; color: black; border-radius: 10px;");
        level5Button->setStyleSheet("background-color: blue; color: black; border-radius: 10px;");

        QVBoxLayout *levelLayout = new QVBoxLayout;
        levelLayout->addWidget(level1Button);
        levelLayout->addWidget(level2Button);
        levelLayout->addWidget(level3Button);
        levelLayout->addWidget(level4Button);
        levelLayout->addWidget(level5Button);

        levelDialog->setLayout(levelLayout);

        connect(level1Button, &QPushButton::clicked, [this]() {
            if (levelOffset == 11) selectedLevel = 11;
            else selectedLevel = 1;
            startGame();
        });

        connect(level2Button, &QPushButton::clicked, [this]() {
            if (levelOffset == 11) selectedLevel = 22;
            else selectedLevel = 2;
            startGame();
        });

        connect(level3Button, &QPushButton::clicked, [this]() {
            if (levelOffset == 11) selectedLevel = 33;
            else selectedLevel = 3;
            startGame();
        });


        connect(level4Button, &QPushButton::clicked, [this]() {
            if (levelOffset == 11) selectedLevel = 44;
            else selectedLevel = 4;
            startGame();
        });

        connect(level5Button, &QPushButton::clicked, [this]() {
            if (levelOffset == 11) selectedLevel = 55;
            else selectedLevel = 5;
            startGame();
        });

        levelDialog->exec();
    });

    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}

void MainWindow::startGame()
{
    QDialog *puzzleWindow = new QDialog(this);
    puzzleWindow->setWindowTitle("15 Puzzle Game");

    QGridLayout *gridLayout = new QGridLayout(puzzleWindow);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    const int gridSize = 4;
    QList<QPushButton*> cells;
    int emptyLine = gridSize - 1;
    int emptyColumn = gridSize - 1;

    for (int line = 0; line < gridSize; ++line) {
        for (int column = 0; column < gridSize; ++column) {
            QPushButton *cell = new QPushButton(puzzleWindow);
            cell->setFlat(true);
            cell->setFixedSize(100, 100);
            cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            cell->setIconSize(QSize(100, 100));

            if (line == gridSize - 1 && column == gridSize - 1) {
                cell->setIcon(QIcon()); // Empty cell
            } else {
                QString imagePath = QString("C:/Slava/Qt/15-Puzzle-Game/assets/%1/game_images/%2.jpg").arg(selectedLevel).arg(line * gridSize + column + 1);
                cell->setIcon(QIcon(imagePath));
            }

            gridLayout->addWidget(cell, line, column);
            cells.append(cell);

            connect(cell, &QPushButton::clicked, [cell, &emptyLine, &emptyColumn, line, column, &cells, this]() {
                if ((line == emptyLine && abs(column - emptyColumn) == 1) || (column == emptyColumn && abs(line - emptyLine) == 1)) {
                    QPushButton *emptyCell = cells[emptyLine * gridSize + emptyColumn];
                    emptyCell->setIcon(cell->icon());
                    cell->setIcon(QIcon());

                    emptyLine = line;
                    emptyColumn = column;

                    checkWin(cells, gridSize);
                }
            });
        }
    }

    QPushButton *shuffleButton = new QPushButton("Shuffle", puzzleWindow);
    shuffleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(shuffleButton, gridSize + 1, 0, 1, gridSize);

    connect(shuffleButton, &QPushButton::clicked, [this, &cells, &emptyLine, &emptyColumn]() {
        shufflePuzzle(cells, emptyLine, emptyColumn, gridSize);
    });

    if (selectedLevel != 1) {
        puzzleWindow->setFixedSize(400, 480);

        QPushButton *viewOriginalButton = new QPushButton("View Original", puzzleWindow);
        viewOriginalButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        gridLayout->addWidget(viewOriginalButton, gridSize, 0, 1, gridSize);

        connect(viewOriginalButton, &QPushButton::clicked, [this]() {
            QDialog *originalDialog = new QDialog(this);
            originalDialog->setWindowTitle("Original Image");
            originalDialog->resize(400, 400);

            QLabel *originalLabel = new QLabel(originalDialog);

            QString originalPixmap = QString("C:/Slava/Qt/15-Puzzle-Game/assets/%1/game_images_origin/game_images_origin.jpg").arg(selectedLevel);
            originalLabel->setPixmap(originalPixmap);
            originalLabel->setScaledContents(true);

            originalLabel->setAlignment(Qt::AlignCenter);

            QVBoxLayout *originalLayout = new QVBoxLayout;
            originalLayout->addWidget(originalLabel);
            originalDialog->setLayout(originalLayout);

            originalDialog->exec();
        });
    }

    else {
        puzzleWindow->setFixedSize(400, 440);
    }

    shufflePuzzle(cells, emptyLine, emptyColumn, gridSize);

    puzzleWindow->setLayout(gridLayout);
    puzzleWindow->exec();
}

void MainWindow::shufflePuzzle(QList<QPushButton*>& cells, int &emptyLine, int &emptyColumn, int gridSize)
{
    QRandomGenerator *generator = QRandomGenerator::global();

    for (int i = 0; i < 10; ++i) {
        int random = generator->bounded(4);
        int newEmptyLine = emptyLine, newEmptyColumn = emptyColumn;

        if (random == 0 && emptyLine > 0) newEmptyLine--;
        if (random == 1 && emptyLine < gridSize - 1) newEmptyLine++;
        if (random == 2 && emptyColumn > 0) newEmptyColumn--;
        if (random == 3 && emptyColumn < gridSize - 1) newEmptyColumn++;

        if (newEmptyLine != emptyLine || newEmptyColumn != emptyColumn) {
            QPushButton *cell = cells[newEmptyLine * gridSize + newEmptyColumn];
            QPushButton *emptyCell = cells[emptyLine * gridSize + emptyColumn];

            QIcon tempIcon = cell->icon();
            cell->setIcon(emptyCell->icon());
            emptyCell->setIcon(tempIcon);

            emptyLine = newEmptyLine;
            emptyColumn = newEmptyColumn;
        }
    }
}

void MainWindow::checkWin(QList<QPushButton*>& cells, int gridSize)
{
    QList<QImage> correctImages;

    for (int i = 0; i < gridSize * gridSize - 1; ++i) {
        QPixmap pixmap(QString("C:/Slava/Qt/15-Puzzle-Game/assets/%1/game_images/%2.jpg").arg(selectedLevel).arg(i + 1));
        correctImages.append(pixmap.toImage());
    }
    correctImages.append(QImage());

    for (int i = 0; i < gridSize * gridSize; ++i) {
        QPushButton *cell = cells[i];
        QPixmap currentPixmap = cell->icon().pixmap(cell->size());


        if (currentPixmap.isNull()) {
            if (!correctImages[i].isNull()) {
                return;
            }
        } else {
            QImage currentImage = currentPixmap.toImage();
            QImage expectedImage = correctImages[i];

            if (currentImage != expectedImage) {
                return;
            }
        }
    }

    QDialog *winDialog = new QDialog(this);
    winDialog->setWindowTitle("Victory!");

    QLabel *winLabel = new QLabel(winDialog);

    if (selectedLevel == 1) {
        winDialog->resize(200, 100);
        winDialog->setMinimumSize(200, 100);
        winLabel->setText("You win!");
        winLabel->setAlignment(Qt::AlignCenter);
        winLabel->setStyleSheet("font-size: 32px; font-weight: bold;");
    } else {
        winDialog->resize(400, 400);
        winDialog->setMinimumSize(200, 200);
        QPixmap winPixmap(QString("C:/Slava/Qt/15-Puzzle-Game/assets/%1/win_image/win.jpg").arg(selectedLevel));
        winLabel->setPixmap(winPixmap);
        winLabel->setScaledContents(true);
    }

    QVBoxLayout *winLayout = new QVBoxLayout;
    winLayout->addWidget(winLabel);
    winDialog->setLayout(winLayout);

    winDialog->exec();
}

