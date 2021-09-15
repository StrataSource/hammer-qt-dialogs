
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Preferences.h"
#include "PrefSlider.h"

using namespace ui; 

float miles;
bool boolSetting;

CPrefManager::CPrefManager(QWidget* pParent) :
	QDialog(pParent)
{
	auto pVLayout = new QVBoxLayout(this);
	
	auto pGameExeSelect = new CFileSelector(this, CFileSelector::DirsOnly);
	pGameExeSelect->getLabel().setText("Game Executable Directory:");
	
	auto pGameDirSelect = new CFileSelector(this, CFileSelector::DirsOnly);
	pGameDirSelect->getLabel().setText("Game Directory (where GameInfo.txt is):");
	
	auto pHammerVMFDirSelect = new CFileSelector(this, CFileSelector::DirsOnly);
	pHammerVMFDirSelect->getLabel().setText("Hammer VMF Directory:");
	
	auto pPrefabDirSelect = new CFileSelector(this, CFileSelector::DirsOnly);
	pPrefabDirSelect->getLabel().setText("Prefab Directory:");
	
	auto pPrefSlider = new CPrefSlider(this, "Test Slider", "miles", -10, 100, miles, 0.5f);
	auto pCheckBox = new CPrefCheckbox(this, "Test", boolSetting, false);
	
	pVLayout->addWidget(pGameExeSelect);
	pVLayout->addWidget(pGameDirSelect);
	pVLayout->addWidget(pHammerVMFDirSelect);
	pVLayout->addWidget(pPrefabDirSelect);
	pVLayout->addWidget(pPrefSlider);
	pVLayout->addWidget(pCheckBox);
	
	this->setLayout(pVLayout);
}