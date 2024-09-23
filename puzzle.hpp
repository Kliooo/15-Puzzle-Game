#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>

namespace bva {

class Puzzle : public QDialog {
    Q_OBJECT

public:
    explicit Puzzle(QWidget *parent = nullptr, int selectedLevel = 1);

private slots:
    void onCellClicked(int row, int column);
    void onShuffleButtonClicked();
    void onViewOriginalClicked();

private:
    const int gridSize = 4;

    QList<QPushButton*> cells;
    int selectedLevel;
    int emptyRow;
    int emptyColumn;

    void setupInterface();
    void checkWin();
    void shufflePuzzle(QList<QPushButton*>& cells, int &emptyRow, int &emptyCol, const int gridSize);
};

}

#endif
