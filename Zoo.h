#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

namespace ui {

//-------------------------------------------//
// Launches every dialog window in this repo //
//-------------------------------------------//
class CZoo : public QDialog
{
Q_OBJECT;
public:
    QPushButton *m_pFileSelector;
    QPushButton *m_pGoToBrush;
    QPushButton *m_pGoToCoord;
    QPushButton *m_pPreferences;

    CZoo(QWidget *pParent);

private slots:
    void onFileSelectorPressed();
    void onGoToBrushPressed();
    void onGoToCoordPressed();
    void onPreferencesPressed();
};

}