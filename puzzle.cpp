#include "puzzle.h"

VBEK::Puzzle::Puzzle(QWidget *parent, int selectedLevel)
    : QDialog(parent), selectedLevel(selectedLevel)
{
    setupInterface();
}

void VBEK::Puzzle::setupInterface()
{
    setWindowTitle("15 Puzzle Game");
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    const int gridSize = 4;
    cells.clear();
    emptyRow = gridSize - 1;
    emptyColumn = gridSize - 1;

    for (int row = 0; row < gridSize; ++row) {
        for (int column = 0; column < gridSize; ++column) {
            QPushButton *cell = new QPushButton(this);
            cell->setFlat(true);
            cell->setFixedSize(100, 100);
            cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            cell->setIconSize(QSize(100, 100));

            if (row == gridSize - 1 && column == gridSize - 1) {
                cell->setIcon(QIcon()); // Пустая клетка
            } else {
                QString imagePath = QString(":%1/game_images/%2.jpg").arg(selectedLevel).arg(row * gridSize + column + 1);
                cell->setIcon(QIcon(imagePath));
            }

            gridLayout->addWidget(cell, row, column);
            cells.append(cell);

            connect(cell, &QPushButton::clicked, [this, row, column]() { onCellClicked(row, column); });
        }
    }

    QPushButton *shuffleButton = new QPushButton("Shuffle", this);
    shuffleButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(shuffleButton, gridSize + 1, 0, 1, gridSize);

    connect(shuffleButton, &QPushButton::clicked, this, &Puzzle::onShuffleButtonClicked);

    if (selectedLevel != 1) {
        setFixedSize(400, 480);
        QPushButton *viewOriginalButton = new QPushButton("View Original", this);
        viewOriginalButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        gridLayout->addWidget(viewOriginalButton, gridSize, 0, 1, gridSize);

        connect(viewOriginalButton, &QPushButton::clicked, this, &Puzzle::onViewOriginalClicked);
    } else {
        setFixedSize(400, 440);
    }

    shufflePuzzle(cells, emptyRow, emptyColumn, gridSize);
    setLayout(gridLayout);
}

void VBEK::Puzzle::onCellClicked(int row, int column)
{
    if ((row == emptyRow && abs(column - emptyColumn) == 1) || (column == emptyColumn && abs(row - emptyRow) == 1)) {
        QPushButton *clickedButton = cells[row * gridSize + column];
        QPushButton *emptyButton = cells[emptyRow * gridSize + emptyColumn];

        emptyButton->setIcon(clickedButton->icon());
        clickedButton->setIcon(QIcon());

        emptyRow = row;
        emptyColumn = column;

        checkWin();
    }
}

void VBEK::Puzzle::onShuffleButtonClicked()
{
    shufflePuzzle(cells, emptyRow, emptyColumn, gridSize);
}

void VBEK::Puzzle::onViewOriginalClicked()
{
    QDialog *originalDialog = new QDialog(this);
    originalDialog->setWindowTitle("Original Image");
    originalDialog->resize(400, 400);

    QLabel *originalLabel = new QLabel(originalDialog);
    QString originalPixmap = QString(":%1/game_images_origin/game_images_origin.jpg").arg(selectedLevel);
    originalLabel->setPixmap(originalPixmap);
    originalLabel->setScaledContents(true);
    originalLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *originalLayout = new QVBoxLayout;
    originalLayout->addWidget(originalLabel);
    originalDialog->setLayout(originalLayout);

    originalDialog->exec();
}

void VBEK::Puzzle::checkWin()
{
    QList<QImage> correctImages;

    for (int i = 0; i < gridSize * gridSize - 1; ++i) {
        QPixmap pixmap(QString(":%1/game_images/%2.jpg").arg(selectedLevel).arg(i + 1));
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
        QPixmap winPixmap(QString(":%1/win_image/win_image.jpg").arg(selectedLevel));
        winLabel->setPixmap(winPixmap);
        winLabel->setScaledContents(true);
    }

    QVBoxLayout *winLayout = new QVBoxLayout;
    winLayout->addWidget(winLabel);
    winDialog->setLayout(winLayout);

    winDialog->exec();
}

void VBEK::Puzzle::shufflePuzzle(QList<QPushButton*>& cells, int &emptyRow, int &emptyCol, const int gridSize)
{
    QRandomGenerator *generator = QRandomGenerator::global();

    for (int i = 0; i < 1000; ++i) {
        int random = generator->bounded(4);
        int newEmptyRow = emptyRow, newEmptyColumn = emptyColumn;

        if (random == 0 && emptyRow > 0) newEmptyRow--;
        if (random == 1 && emptyRow < gridSize - 1) newEmptyRow++;
        if (random == 2 && emptyColumn > 0) newEmptyColumn--;
        if (random == 3 && emptyColumn < gridSize - 1) newEmptyColumn++;

        if (newEmptyRow != emptyRow || newEmptyColumn != emptyColumn) {
            QPushButton *cell = cells[newEmptyRow * gridSize + newEmptyColumn];
            QPushButton *emptyCell = cells[emptyRow * gridSize + emptyColumn];

            QIcon tempIcon = cell->icon();
            cell->setIcon(emptyCell->icon());
            emptyCell->setIcon(tempIcon);

            emptyRow = newEmptyRow;
            emptyColumn = newEmptyColumn;
        }
    }
}
