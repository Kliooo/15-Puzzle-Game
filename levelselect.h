#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>

namespace VBEK {

class LevelSelect : public QDialog {
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr, int levelOffset = 1);

signals:
    void levelSelected(int level);

private:
    void setupInterface();
    int levelOffset;
};

}

#endif // LEVELSELECT_H
