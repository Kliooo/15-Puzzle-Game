#include "levelselect.h"

VBEK::LevelSelect::LevelSelect(QWidget *parent, int levelOffset)
    : QDialog(parent), levelOffset(levelOffset)
{
    setupInterface();
}

void VBEK::LevelSelect::setupInterface()
{
    setWindowTitle("Select Level");
    resize(300, 350);

    QPushButton *levelButtons[5];

    QStringList defaultNames = {"Classic", "Cats", "Ryan Gosling", "Sea and Beach", "Satoru Gojo"};
    QStringList vipNames = {"Neko Girl 1", "Random Woman", "Black Square", "Neko Girl 2", "Dinosaurs"};
    QStringList buttonColors = {"white", "grey", "yellow", "turquoise", "blue"};

    QVBoxLayout *levelLayout = new QVBoxLayout;

    for (int i = 0; i < 5; ++i) {
        levelButtons[i] = new QPushButton(this);

        if (levelOffset == 11) {
            levelButtons[i]->setText(vipNames[i]);
        } else {
            levelButtons[i]->setText(defaultNames[i]);
        }

        QString buttonStyle = QString("background-color: %1; color: black; border-radius: 10px;").arg(buttonColors[i]);
        levelButtons[i]->setStyleSheet(buttonStyle);
        levelButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        levelLayout->addWidget(levelButtons[i]);

        connect(levelButtons[i], &QPushButton::clicked, this, [this, i]() { emit levelSelected(i + 1); });
    }

    setLayout(levelLayout);
}
