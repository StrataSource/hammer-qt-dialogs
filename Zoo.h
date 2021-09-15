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
    CZoo(QWidget *pParent);

};

}