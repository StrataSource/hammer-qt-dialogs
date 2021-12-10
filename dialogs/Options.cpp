
#include "Options.h"

#include "widgets/FileSelector.h"
#include "widgets/PrefSlider.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace ui;

float miles;
bool boolSetting;

QString SelectFileName( const char *pCategory, const char *pKey, QWidget *pParent, const QString &caption, const QString &defaultDir,
						const QString &filter, QFileDialog::Options opts )
{
	// char szDir[MAX_PATH];
	// GetProfileString(pCategory, pKey, defaultDir.toUtf8().data(), szDir, sizeof(szDir));

	// if(!UseNativeFileDialog())
	//	opts |= QFileDialog::DontUseNativeDialog;

	QFileDialog *dlg = new QFileDialog();
	dlg->setDirectory( "/" );
	dlg->setNameFilter( filter );
	dlg->setFilter( QDir::Files );
	dlg->setWindowTitle( caption );
	dlg->setOptions( opts );

	dlg->exec();

	QString selected = dlg->selectedFiles().first();

	// auto file = QFileDialog::getOpenFileName(pParent, caption, szDir, filter, nullptr, opts);

	QString dirPath = selected;
	// ui::StripFileName(dirPath);
	// WriteProfileString(pCategory, pKey, dirPath.toUtf8().data());
	delete dlg;
	return selected;
}

CPrefManager::CPrefManager( QWidget *pParent ) :
	QDialog( pParent )
{
	auto pVLayout = new QVBoxLayout( this );

	auto pGameExeSelect = new CFileSelector( this, CFileSelector::DirsOnly );
	pGameExeSelect->getLabel().setText( "Game Executable Directory:" );

	auto pGameDirSelect = new CFileSelector( this, CFileSelector::DirsOnly );
	pGameDirSelect->getLabel().setText( "Game Directory (where GameInfo.txt is):" );

	auto pHammerVMFDirSelect = new CFileSelector( this, CFileSelector::DirsOnly );
	pHammerVMFDirSelect->getLabel().setText( "Hammer VMF Directory:" );

	auto pPrefabDirSelect = new CFileSelector( this, CFileSelector::DirsOnly );
	pPrefabDirSelect->getLabel().setText( "Prefab Directory:" );
	SelectFileName( "", "", this, "Hello", "/", "", 0 );

	auto pPrefSlider = new CPrefSlider( this, "Test Slider", "miles", -10, 100, miles, 0.5f );
	auto pCheckBox = new CPrefCheckbox( this, "Test", boolSetting, false );

	pVLayout->addWidget( pGameExeSelect );
	pVLayout->addWidget( pGameDirSelect );
	pVLayout->addWidget( pHammerVMFDirSelect );
	pVLayout->addWidget( pPrefabDirSelect );
	pVLayout->addWidget( pPrefSlider );
	pVLayout->addWidget( pCheckBox );

	this->setLayout( pVLayout );
}