#ifndef LEVELSELECT_HPP
#define LEVELSELECT_HPP

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>

namespace bva {

class LevelSelect : public QDialog {
    Q_OBJECT

private:
	int levelOffset;

public:
    explicit LevelSelect(QWidget *parent = nullptr, int levelOffset = 1);

signals:
    void levelSelected(int level);

private:
	void setupInterface();
};

}

#endif
