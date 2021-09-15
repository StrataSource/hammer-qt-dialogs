#include "Zoo.h"

#include "FileSelector.h"
#include "GoToDialog.h"
#include "Preferences.h"

using namespace ui;

CZoo::CZoo(QWidget* pParent) :
        QDialog(pParent)
{
    this->setWindowTitle(tr("You're a Qt :)"));
    this->setMinimumWidth(300);

    m_pFileSelector = new QPushButton(this);
    m_pFileSelector->setText(tr("File Selector"));
    m_pGoToBrush = new QPushButton(this);
    m_pGoToBrush->setText(tr("Go To Brush"));
    m_pGoToCoord = new QPushButton(this);
    m_pGoToCoord->setText(tr("Go To Coord"));
    m_pPreferences = new QPushButton(this);
    m_pPreferences->setText(tr("Preferences"));

    auto* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_pFileSelector);
    pLayout->addWidget(m_pGoToBrush);
    pLayout->addWidget(m_pGoToCoord);
    pLayout->addWidget(m_pPreferences);
    this->setLayout(pLayout);

    connect(m_pFileSelector, &QPushButton::released, this, &CZoo::onFileSelectorPressed);
    connect(m_pGoToBrush, &QPushButton::released, this, &CZoo::onGoToBrushPressed);
    connect(m_pGoToCoord, &QPushButton::released, this, &CZoo::onGoToCoordPressed);
    connect(m_pPreferences, &QPushButton::released, this, &CZoo::onPreferencesPressed);
}

void CZoo::onFileSelectorPressed()
{
    auto pFileSelector = new ui::CFileSelector(nullptr, CFileSelector::DirsOnly);
    pFileSelector->show();
}

void CZoo::onGoToBrushPressed()
{
    auto pGoToBrush = new ui::CGoToBrushDialog(nullptr);
    pGoToBrush->show();
}

void CZoo::onGoToCoordPressed()
{
    auto pGoToCoord = new ui::CGoToCoordDialog(nullptr);
    pGoToCoord->show();
}

void CZoo::onPreferencesPressed()
{
    auto pPreferences = new ui::CPrefManager(nullptr);
    pPreferences->show();
}