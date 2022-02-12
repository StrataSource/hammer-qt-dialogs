#include "dialogs/Options.h"

#include <QLabel>
#include <QPushButton>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFormLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <QPainter>

#include <QDebug>

using namespace ui;

// todo: fix console spam due to overlays
COptions::COptions( QWidget *pParent ) :
	QDialog(pParent)
{
	this->setWindowTitle( tr( "Options" ) );

	auto pDialogLayout = new QVBoxLayout();
	
	auto pOptionsTabWidget = new QTabWidget( this );
	m_pGeneralTab = new COptionsGeneralTab( this );
	m_p2DViewsTab = new COptions2DViewsTab( this );
	m_p3DViewsTab = new COptions3DViewsTab( this );
	m_pGameConfigsTab = new COptionsGameConfigsTab( this );
	m_pBuildProgramsTab = new COptionsBuildProgramsTab( this );
	m_pMaterialsTab = new COptionsMaterialsTab( this );
	m_pColorsTab = new COptionsColorsTab( this );
	pOptionsTabWidget->addTab( m_pGeneralTab, tr( "General" ) );
	pOptionsTabWidget->addTab( m_p2DViewsTab, tr( "2D Views" ) );
	pOptionsTabWidget->addTab( m_p3DViewsTab, tr( "3D Views" ) );
	pOptionsTabWidget->addTab( m_pGameConfigsTab, tr( "Game Config" ) );
	pOptionsTabWidget->addTab( m_pBuildProgramsTab, tr( "Build Programs" ) );
	pOptionsTabWidget->addTab( m_pMaterialsTab, tr( "Materials" ) );
	pOptionsTabWidget->addTab( m_pColorsTab, tr( "Colors" ) );
	
	loadSettings();

	// Buttons
	auto pButtonBox = new QDialogButtonBox( this );
	auto pOkButton = pButtonBox->addButton( QDialogButtonBox::Ok );
	auto pCancelButton = pButtonBox->addButton( QDialogButtonBox::Cancel );
	auto pApplyButton = pButtonBox->addButton( QDialogButtonBox::Apply );
	auto pHelpButton = pButtonBox->addButton( QDialogButtonBox::Help );

	pDialogLayout->addWidget( pOptionsTabWidget );
	pDialogLayout->addWidget( pButtonBox, 0, Qt::AlignRight );

	this->setLayout( pDialogLayout );

	this->setFixedSize( this->sizeHint() );
}

void ui::COptions::loadSettings()
{
}

void ui::COptions::saveSettings()
{
}

void ui::COptions::onOkPressed()
{
}

void ui::COptions::onCancelPressed()
{
	this->close();
}

void ui::COptions::onApplyPressed()
{
	saveSettings();
}

void ui::COptions::onHelpPressed()
{
}

	//-----------------------------------------------------------------------------------------//

COptionsGeneralTab::COptionsGeneralTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	auto pUndoLevelMaxCamLayout = new QHBoxLayout();
	auto pUndoLevelsLabel = new QLabel( tr( "Undo Levels:" ), this );
	auto pMaxCamLabel = new QLabel( tr( "Max Cameras:" ), this );
	m_pUndoLevels = new QSpinBox( this );
	m_pUndoLevels->setMaximum( INT_MAX );
	m_pUndoLevels->setFixedWidth( 55 );
	m_pMaxCameras = new QSpinBox( this );
	m_pMaxCameras->setFixedWidth( 55 );

	m_pAllowGroupingWhileIgnoreGroups = new QCheckBox( tr( "Allow grouping/ungrouping while Ignore Groups is checked" ), this );
	m_pStretchToFitOrigBounding = new QCheckBox( tr( "Stretch arches and toruses to fit original bounding rectangle" ), this );
	m_pEnableMatProxies = new QCheckBox( tr( "Enable material proxies (restart to apply)" ), this );
	m_pEnablePerforce = new QCheckBox( tr( "Enable Perforce Integration" ), this );

	// I can only do DirsOnly here
	m_pFavoriteMaterial = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pFavoriteMaterial->getLabel().setText( "Favorite Material:" );

	m_pUseNodrawForClippedFaces = new QCheckBox( tr( "Use nodraw for clipped faces" ), this );
	m_pAutoDeleteEmptyVisgroups = new QCheckBox( tr( "Automatically delete empty VisGroups" ), this );
	m_pShowCarveWarning = new QCheckBox( tr( "Show carve warning" ), this );

	pUndoLevelMaxCamLayout->addWidget( pUndoLevelsLabel );
	pUndoLevelMaxCamLayout->addWidget( m_pUndoLevels );
	pUndoLevelMaxCamLayout->addSpacing( 5 );
	pUndoLevelMaxCamLayout->addWidget( pMaxCamLabel );
	pUndoLevelMaxCamLayout->addWidget( m_pMaxCameras );
	pUndoLevelMaxCamLayout->insertStretch( -1, 1 );

	// Add components to layout
	pWidgetLayout->addWidget( addWindowSetupGroup() );
	pWidgetLayout->addWidget( addAutosaveGroup() );
	pWidgetLayout->addWidget( addDiscordGroup() );
	pWidgetLayout->addLayout( pUndoLevelMaxCamLayout );
	pWidgetLayout->addWidget( m_pAllowGroupingWhileIgnoreGroups );
	pWidgetLayout->addWidget( m_pStretchToFitOrigBounding );
	pWidgetLayout->addWidget( m_pEnableMatProxies );
	pWidgetLayout->addWidget( m_pEnablePerforce );
	pWidgetLayout->addWidget( m_pFavoriteMaterial );
	pWidgetLayout->addWidget( m_pUseNodrawForClippedFaces );
	pWidgetLayout->addWidget( m_pAutoDeleteEmptyVisgroups );
	pWidgetLayout->addWidget( m_pShowCarveWarning );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGroupBox *COptionsGeneralTab::addWindowSetupGroup()
{
	auto pWindowSetupGroup = new QGroupBox( tr( "Window Setup" ), this );
	auto pWindowSetupLayout = new QVBoxLayout( pWindowSetupGroup );
	m_pUseIndependentWindowConfigs = new QCheckBox( tr( "Use independent window configurations" ), this );
	m_pLoadDefaultWindowPosWithMaps = new QCheckBox( tr( "Load default window positions with maps" ), this );
	pWindowSetupLayout->addWidget( m_pUseIndependentWindowConfigs );
	pWindowSetupLayout->addWidget( m_pLoadDefaultWindowPosWithMaps );

	return pWindowSetupGroup;
}

QGroupBox *COptionsGeneralTab::addAutosaveGroup()
{
	auto pAutosaveGroup = new QGroupBox( tr( "Autosave" ), this );
	auto pAutosaveLayout = new QVBoxLayout( pAutosaveGroup );

	m_pEnableAutosave = new QCheckBox( tr( "Enable Autosave" ), this );

	auto pAutosaveTimeLayout = new QHBoxLayout();
	auto pAutosaveTimeLabel = new QLabel( tr( "Time Between Saves (in minutes)" ), this );
	m_pAutosaveTime = new QLineEdit( this );
	m_pAutosaveTime->setValidator( new QDoubleValidator( m_pAutosaveTime ) );
	m_pAutosaveTime->setFixedWidth( 55 );
	pAutosaveTimeLayout->addWidget( pAutosaveTimeLabel );
	pAutosaveTimeLayout->addWidget( m_pAutosaveTime, 0, Qt::AlignLeft );
	pAutosaveTimeLayout->insertStretch( -1, 1 );

	auto pAutosaveSizeLayout = new QHBoxLayout();
	auto pAutosaveSizeLabel = new QLabel( tr( "Amount of hard drive space used for autosaves (in megabytes)" ), this );
	m_pAutosaveSize = new QLineEdit( this );
	m_pAutosaveSize->setValidator( new QDoubleValidator( m_pAutosaveSize ) );
	m_pAutosaveSize->setFixedWidth( 55 );
	pAutosaveSizeLayout->addWidget( pAutosaveSizeLabel, 0, Qt::AlignLeft );
	pAutosaveSizeLayout->addWidget( m_pAutosaveSize );
	pAutosaveSizeLayout->insertStretch( -1, 1 );

	auto pAutosaveIterationsLayout = new QHBoxLayout();
	auto pAutosaveIterationsLabel = new QLabel( tr( "Number of map iterations to save" ), this );
	m_pAutosaveIterations = new QLineEdit( this );
	m_pAutosaveIterations->setValidator( new QDoubleValidator( m_pAutosaveIterations ) );
	m_pAutosaveIterations->setFixedWidth( 55 );
	pAutosaveIterationsLayout->addWidget( pAutosaveIterationsLabel, 0, Qt::AlignLeft );
	pAutosaveIterationsLayout->addWidget( m_pAutosaveIterations );
	pAutosaveIterationsLayout->insertStretch( -1, 1 );

	m_pAutosaveDirectory = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pAutosaveDirectory->getLabel().setText( "Autosave Directory:" );

	pAutosaveLayout->addWidget( m_pEnableAutosave );
	pAutosaveLayout->addLayout( pAutosaveTimeLayout );
	pAutosaveLayout->addLayout( pAutosaveSizeLayout );
	pAutosaveLayout->addLayout( pAutosaveIterationsLayout );
	pAutosaveLayout->addWidget( m_pAutosaveDirectory );

	return pAutosaveGroup;
}

QGroupBox *COptionsGeneralTab::addDiscordGroup()
{
	auto pDiscordGroup = new QGroupBox( tr( "Discord" ), this );
	auto pDiscordLayout = new QGridLayout( pDiscordGroup );

	m_pEnableDiscord = new QCheckBox( tr( "Enable Discord" ), this );
	auto pLine1Label = new QLabel( tr( "Line 1" ), this );
	auto pLine2Label = new QLabel( tr( "Line 2" ), this );
	m_pDiscordLine1 = new QLineEdit( this );
	m_pDiscordLine2 = new QLineEdit( this );
	
	auto pLine1Layout = new QHBoxLayout();
	pLine1Layout->addWidget( pLine1Label );
	pLine1Layout->addWidget( m_pDiscordLine1 );
	auto pLine2Layout = new QHBoxLayout();
	pLine2Layout->addWidget( pLine2Label );
	pLine2Layout->addWidget( m_pDiscordLine2 );

	auto pDiscordHelp = new QStringList();
	pDiscordHelp->append( tr( "Template to use for rich presence." ) );
	pDiscordHelp->append( tr( "If field is left empty, it will not be used." ) );
	pDiscordHelp->append( tr( "These special keywords will be replaced:" ) );
	pDiscordHelp->append( tr( "- %(filename) - map file name without extension" ) );
	pDiscordHelp->append( tr( "- %(file) - file with extension" ) );
	pDiscordHelp->append( tr( "- %(moddir) - current mod's directory" ) );
	pDiscordHelp->append( tr( "- %(mod) - name of current mod (from GameConfig.txt)" ) );

	auto pDiscordInfoLabel = new QLabel( pDiscordHelp->join( "\n" ), this );

	pDiscordLayout->addWidget( m_pEnableDiscord, 0, 0 );
	pDiscordLayout->addLayout( pLine1Layout, 1, 0 );
	pDiscordLayout->addWidget( pDiscordInfoLabel, 0, 3, 3, 1 );
	pDiscordLayout->addLayout( pLine2Layout, 2, 0 );

	return pDiscordGroup;
}

	//-----------------------------------------------------------------------------------------//

COptions2DViewsTab::COptions2DViewsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	pWidgetLayout->addWidget( addOptionsGroup(), 0, Qt::AlignTop );
	pWidgetLayout->addWidget( addGridGroup(), 0, Qt::AlignTop );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGroupBox *COptions2DViewsTab::addOptionsGroup()
{
	auto pOptionsGroup = new QGroupBox( tr( "Options" ), this );
	auto pOptionsLayout = new QGridLayout( pOptionsGroup );

	m_pDefaultTo15DegRots = new QCheckBox( tr( "Default to 15 degree rotations" ), this );
	m_pDisplayScrollbars = new QCheckBox( tr( "Display scrollbars" ), this );
	m_pDrawVertices = new QCheckBox( tr( "Draw vertices" ), this );
	m_pDrawModels = new QCheckBox( tr( "Draw models" ), this );
	m_pWhiteOnBlackColorScheme = new QCheckBox( tr( "White-on-Black color scheme" ), this );
	m_pUseVisgroupColorsForObjectLines = new QCheckBox( tr( "Use visgroup colors for object lines" ), this );
	m_pKeepVisgroupWhenCloneDragging = new QCheckBox( tr( "Keep visgroup when clone-dragging" ), this );

	m_pArrowkeyNudgeSelected = new QCheckBox( tr( "Arrow keys nudge selected object/vertex" ), this );
	m_pReorientPrimiitvesOnCreation = new QCheckBox( tr( "Reorient primitives on creation in the active 2D view" ), this );
	m_pAutoInfiniteSelection = new QCheckBox( tr( "Automatic infinite selection in 2D windows (no ENTER)" ), this );
	m_pSelectObjectsByCenter = new QCheckBox( tr( "Select objects by center handles only" ), this );
	m_pCenterOnCameraAfterMovement = new QCheckBox( tr( "Center on camera after movement in 3D" ), this );

	pOptionsLayout->addWidget( m_pDefaultTo15DegRots, 0, 0 );
	pOptionsLayout->addWidget( m_pDisplayScrollbars, 1, 0 );
	pOptionsLayout->addWidget( m_pDrawVertices, 2, 0 );
	pOptionsLayout->addWidget( m_pDrawModels, 3, 0 );
	pOptionsLayout->addWidget( m_pWhiteOnBlackColorScheme, 4, 0 );
	pOptionsLayout->addWidget( m_pUseVisgroupColorsForObjectLines, 5, 0 );
	pOptionsLayout->addWidget( m_pKeepVisgroupWhenCloneDragging, 6, 0 );

	pOptionsLayout->addWidget( m_pArrowkeyNudgeSelected, 0, 1 );
	pOptionsLayout->addWidget( m_pReorientPrimiitvesOnCreation, 1, 1 );
	pOptionsLayout->addWidget( m_pAutoInfiniteSelection, 2, 1 );
	pOptionsLayout->addWidget( m_pSelectObjectsByCenter, 3, 1 );
	pOptionsLayout->addWidget( m_pCenterOnCameraAfterMovement, 4, 1 );

	return pOptionsGroup;
}

QGroupBox *COptions2DViewsTab::addGridGroup()
{
	auto pGridGroup = new QGroupBox( tr( "Grid" ), this );
	auto pGridLayout = new QGridLayout( pGridGroup );

	// Grid Size
	auto pSizeLayout = new QHBoxLayout();
	auto pSizeLabel = new QLabel( tr( "Size:" ) );
	m_pGridSizeBox = new QComboBox( this );
	m_pGridSizeBox->addItem( "4" );
	m_pGridSizeBox->addItem( "8" );
	m_pGridSizeBox->addItem( "16" );
	m_pGridSizeBox->addItem( "32" );
	m_pGridSizeBox->addItem( "64" );
	m_pGridSizeBox->addItem( "128" );
	m_pGridSizeBox->addItem( "256" );

	pSizeLayout->addWidget( pSizeLabel );
	pSizeLayout->addWidget( m_pGridSizeBox );
	// HACK: No other method I tried works, this sets the gap to be minimal
	// This comment covers all instances of this, this was just the first added.
	pSizeLayout->insertStretch( -1, 1 );

	// Intensity Slider
	m_pIntensitySlider = new CPrefSlider( this, tr( "Intensity:" ), "", 0, 100, m_fIntensityValue );

	m_pHighlightEvery64UnitsBox = new QCheckBox( tr( "Highlight every 64 units" ) );
	m_pDottedGridBox = new QCheckBox( tr( "Dotted Grid" ) );
	m_pHideGridSmallerThan4PixelsBox = new QCheckBox( tr( "Hide grid smaller than 4 pixels" ), this );

	auto pGridLinesLayout = new QHBoxLayout();
	pGridLinesLayout->setSpacing( 0 );
	m_pHighlightEveryXGridLinesBox = new QCheckBox( tr( "Highlight every" ) );
	m_pHighlightEveryXGridLinesLine = new QLineEdit( this );
	m_pHighlightEveryXGridLinesLine->setFixedWidth( 25 );
	m_pHighlightEveryXGridLinesLine->setValidator( new QIntValidator( m_pHighlightEveryXGridLinesLine ) );
	auto pRestOfGridLinesLabel = new QLabel( tr( "grid lines" ) );
	pGridLinesLayout->addWidget( m_pHighlightEveryXGridLinesBox );
	pGridLinesLayout->addWidget( m_pHighlightEveryXGridLinesLine );
	pGridLinesLayout->addSpacing( 5 );
	pGridLinesLayout->addWidget( pRestOfGridLinesLabel );

	// Add components to grid layout
	pGridLayout->addLayout( pSizeLayout, 0, 0 );
	pGridLayout->addWidget( m_pIntensitySlider, 0, 1, 1, 4 );

	//1
	pGridLayout->addWidget( m_pHighlightEvery64UnitsBox, 1, 0 );
	pGridLayout->addWidget( m_pDottedGridBox, 1, 1 );

	//2
	pGridLayout->addLayout( pGridLinesLayout, 2, 0, Qt::AlignLeft );
	pGridLayout->addWidget( m_pHideGridSmallerThan4PixelsBox, 2, 1 );

	return pGridGroup;
}

	//-----------------------------------------------------------------------------------------//

COptions3DViewsTab::COptions3DViewsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	pWidgetLayout->addWidget( addPerformanceBox(), 0, Qt::AlignTop );
	pWidgetLayout->addWidget( addNavigationBox(), 0, Qt::AlignTop );
	pWidgetLayout->addWidget( addGeneralBox(), 0, Qt::AlignTop );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGroupBox *COptions3DViewsTab::addPerformanceBox()
{
	auto pPerfGroup = new QGroupBox( tr( "Performance" ), this );
	auto pPerfLayout = new QGridLayout( pPerfGroup );

	m_pBackClippingPlaneSlider = new CPrefSlider( this, tr( "Back clipping plane:" ), "", 500, 30000, m_fBackClippingPlaneValue );
	m_pFilterTextures = new QCheckBox( tr( "Filter textures" ), this );
	m_pAnimateModels = new QCheckBox( tr( "Animate model" ), this );
	m_pModelRenderDistanceSlider = new CPrefSlider( this, tr( "Model render distance:" ), "", 0, 30000, m_fModelRenderDistanceValue );
	m_pDetailRenderDistanceSlider = new CPrefSlider( this, tr( "Detail render distance:" ), "", 0, 30000, m_fDetailRenderDistanceValue );

	pPerfLayout->addWidget( m_pBackClippingPlaneSlider, 0, 0, 1, 2, Qt::AlignLeft );
	pPerfLayout->addWidget( m_pFilterTextures, 1, 0 );
	pPerfLayout->addWidget( m_pAnimateModels, 1, 1 );
	pPerfLayout->addWidget( m_pModelRenderDistanceSlider, 2, 0, 1, 2, Qt::AlignLeft );
	pPerfLayout->addWidget( m_pDetailRenderDistanceSlider, 3, 0, 1, 2, Qt::AlignLeft );

	return pPerfGroup;
}

QGroupBox *COptions3DViewsTab::addNavigationBox()
{
	auto pNavGroup = new QGroupBox( tr( "Navigation" ), this );
	auto pNavLayout = new QGridLayout( pNavGroup );

	m_pUseMouseLookNavigation = new QCheckBox( tr( "Use mouselook navigation" ), this );
	m_pReverseMouseYAxis = new QCheckBox( tr( "Reverse mouse Y axis" ), this );
	m_pMouseSensitivitySlider = new CPrefSlider( this, tr( "Mouse Sensitivity:" ), "", 0.0001, 1, m_fMouseSensitivityValue, 0.0001 );
	m_pForwardSpeedSlider = new CPrefSlider( this, tr( "Forward speed:" ), "", 1000, 30000, m_fForwardSpeedValue );
	m_pTimeToTopSpeedSlider = new CPrefSlider( this, tr( "Time to top speed:" ), "sec", 0.00, 30.00, m_fTimeToTopSpeedValue, 0.01 );


	pNavLayout->addWidget( m_pUseMouseLookNavigation, 0, 0 );
	pNavLayout->addWidget( m_pReverseMouseYAxis, 0, 1 );
	pNavLayout->addWidget( m_pMouseSensitivitySlider, 1, 0, 1, 2 );
	pNavLayout->addWidget( m_pForwardSpeedSlider, 2, 0, 1, 2 );
	pNavLayout->addWidget( m_pTimeToTopSpeedSlider, 3, 0, 1, 2 );

	return pNavGroup;
}

QGroupBox *COptions3DViewsTab::addGeneralBox()
{
	auto pGeneralGroup = new QGroupBox( tr( "General" ), this );
	auto pGeneralLayout = new QGridLayout( pGeneralGroup );

	m_pReverseSelectionOrder = new QCheckBox( tr( "Reverse selection order" ), this );
	m_pDrawSkyboxPreview = new QCheckBox( tr( "Draw skybox preview" ), this );

	auto pCamFovLayout = new QHBoxLayout();
	auto pCamFovLabel = new QLabel( tr( "Camera FOV (30-100)" ), this );
	m_pCameraFov = new QSpinBox( this );
	m_pCameraFov->setFixedWidth( 40 );
	m_pCameraFov->setMinimum( 30 );
	m_pCameraFov->setMaximum( 100 );
	m_pCameraFov->setButtonSymbols( QAbstractSpinBox::NoButtons );

	pCamFovLayout->addWidget( pCamFovLabel );
	pCamFovLayout->addWidget( m_pCameraFov, 0, Qt::AlignRight );

	auto pLightSpotLayout = new QHBoxLayout();
	auto pLightSpotLabel = new QLabel( tr( "Light_spot cone multiplier" ), this );
	m_pLightSpotConeModifier = new QSpinBox( this );
	m_pLightSpotConeModifier->setFixedWidth( 40 );
	m_pLightSpotConeModifier->setMinimum( 1 );
	m_pLightSpotConeModifier->setMaximum( INT_MAX );
	m_pLightSpotConeModifier->setButtonSymbols( QAbstractSpinBox::NoButtons );

	pLightSpotLayout->addWidget( pLightSpotLabel );
	pLightSpotLayout->addWidget( m_pLightSpotConeModifier, 0, Qt::AlignRight );

	pGeneralLayout->addWidget( m_pReverseSelectionOrder, 0, 0 );
	pGeneralLayout->addLayout( pCamFovLayout, 0, 1 );

	pGeneralLayout->addWidget( m_pDrawSkyboxPreview, 1, 0 );
	pGeneralLayout->addLayout( pLightSpotLayout, 1, 1 );

	return pGeneralGroup;
}

	//-----------------------------------------------------------------------------------------//

COptionsGameConfigsTab::COptionsGameConfigsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	// todo: Some of these really need to just be files, but CFileSelector doesn't allow that.
	m_pCordonTexture = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pCordonTexture->getLineEdit().setText( "tools/toolskybox" );
	m_pCordonTexture->getLabel().setText( tr( "Cordon Texture:" ) );

	m_pGameExec = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pGameExec->getLineEdit().setText( "path/to/chaos.exe" );
	m_pGameExec->getLabel().setText( tr( "Game Exectuable Directory (ex: c:\\Half-Life):" ) );

	m_pGameDir = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pGameDir->getLineEdit().setText( "path/to/gameinfo.txt" );
	m_pGameDir->getLabel().setText( tr( "Game Directory (where GameInfo.txt is, ex: c:\\Half-Life\\cstrike):" ) );

	m_pHammerVmfDir = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pHammerVmfDir->getLineEdit().setText( "path/to/mapsrc" );
	m_pHammerVmfDir->getLabel().setText( tr( "Hammer VMF Directory (ex: c:\\Half-Life\\maps):" ) );

	m_pPrefabDir = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pPrefabDir->getLineEdit().setText( "path/to/prefabs" );
	m_pPrefabDir->getLabel().setText( tr( "Prefabs Directory (ex: c:\\Half-Life\\maps\\prefabs):" ) );

	pWidgetLayout->addLayout( addConfigAndGameDataLayout() );
	pWidgetLayout->addLayout( addEntityAndScaleLayout() );
	pWidgetLayout->addWidget( m_pCordonTexture );
	pWidgetLayout->addWidget( m_pGameExec );
	pWidgetLayout->addWidget( m_pGameDir );
	pWidgetLayout->addWidget( m_pHammerVmfDir );
	pWidgetLayout->addWidget( m_pPrefabDir );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGridLayout *COptionsGameConfigsTab::addConfigAndGameDataLayout()	
{
	auto pConfigLayout = new QGridLayout();

	auto pConfigLabel = new QLabel( tr( "Configuration:" ) );
	m_pConfigCombo = new QComboBox( this );
	m_pConfigCombo->addItem( "Momentum" );
	auto pConfigEditButton = new QPushButton( tr( "Edit" ), this );

	auto pGameDataLabel = new QLabel( tr( "Game Data files:" ), this );
	m_pGameDataList = new QListWidget( this );
	m_pGameDataList->setFixedHeight( 50 );
	m_pGameDataList->addItem( "path/to/momentum.fgd" );

	auto pButtonLayout = new QVBoxLayout();
	auto pAddEditLayout = new QHBoxLayout();
	auto pGameDataAddButton = new QPushButton( tr( "Add" ), this );
	auto pGameDataEditButton = new QPushButton( tr( "Edit" ), this );
	auto pRemoveButton = new QPushButton( tr( "Remove" ), this );

	pAddEditLayout->addWidget( pGameDataAddButton );
	pAddEditLayout->addWidget( pGameDataEditButton );

	pGameDataAddButton->setFixedWidth( pRemoveButton->width() / 2 );
	pGameDataEditButton->setFixedWidth( pRemoveButton->width() / 2 );

	pButtonLayout->addLayout( pAddEditLayout );
	pButtonLayout->addWidget( pRemoveButton );
	
	// Config
	pConfigLayout->addWidget( pConfigLabel, 0, 0 );
	pConfigLayout->addWidget( m_pConfigCombo, 1, 0, 1, 3 );
	pConfigLayout->addWidget( pConfigEditButton, 1, 4 );

	// Game Data
	pConfigLayout->addWidget( pGameDataLabel, 2, 0 );
	pConfigLayout->addWidget( m_pGameDataList, 3, 0, 1, 3 );
	pConfigLayout->addLayout( pButtonLayout, 3, 4, 1, 1, Qt::AlignTop );

	connect( pConfigEditButton, &QPushButton::released, this, &COptionsGameConfigsTab::onConfigEditPressed );
	connect( pGameDataAddButton, &QPushButton::released, this, &COptionsGameConfigsTab::onGameDataAddPressed );
	connect( pGameDataEditButton, &QPushButton::released, this, &COptionsGameConfigsTab::onGameDataEditPressed );
	connect( pRemoveButton, &QPushButton::released, this, &COptionsGameConfigsTab::onGameDataRemovePressed );

	return pConfigLayout;
}

QGridLayout *COptionsGameConfigsTab::addEntityAndScaleLayout()
{
	auto pGridLayout = new QGridLayout();

	auto pDefPointEntLabel = new QLabel( tr( "Default PointEntity class:" ), this );
	m_pDefaultPointEntity = new QComboBox( this );
	m_pDefaultPointEntity->addItem( "info_teleport_destination" );
	m_pDefaultPointEntity->setEditable( true );

	auto pDefSolidEntLabel = new QLabel( tr( "Default SolidEntity class:" ), this );
	m_pDefaultSolidEntity = new QComboBox( this );
	m_pDefaultSolidEntity->addItem( "func_detail" );
	m_pDefaultSolidEntity->setEditable( true );

	auto pScaleLayout = new QHBoxLayout();
	auto pDefTexScaleLabel = new QLabel( tr( "Default texture scale:" ), this );
	m_pDefTextureScale = new QLineEdit( "0.25", this );
	m_pDefTextureScale->setFixedWidth( 30 );
	m_pDefTextureScale->setValidator( new QDoubleValidator( m_pDefTextureScale ) );

	auto pDefLMScaleLabel = new QLabel( tr( "Default lightmap scale:" ), this );
	m_pDefLightMapScale = new QLineEdit( "128", this );
	m_pDefLightMapScale->setFixedWidth( 30 );
	m_pDefLightMapScale->setValidator( new QIntValidator( m_pDefLightMapScale ) );

	pScaleLayout->addWidget( pDefTexScaleLabel, 0, Qt::AlignLeft );
	pScaleLayout->addWidget( m_pDefTextureScale, 0, Qt::AlignLeft );
	pScaleLayout->addWidget( pDefLMScaleLabel, 0, Qt::AlignLeft );
	pScaleLayout->addWidget( m_pDefLightMapScale, 0, Qt::AlignLeft );

	// Point Entity
	pGridLayout->addWidget( pDefPointEntLabel, 0, 0 );
	pGridLayout->addWidget( m_pDefaultPointEntity, 1, 0 );

	// Solid Entity
	pGridLayout->addWidget( pDefSolidEntLabel, 0, 1 );
	pGridLayout->addWidget( m_pDefaultSolidEntity, 1, 1 );

	// Sales
	pGridLayout->addLayout( pScaleLayout, 2, 0, 1, 2 );

	return pGridLayout;
}

void COptionsGameConfigsTab::onConfigEditPressed()
{
}

void COptionsGameConfigsTab::onGameDataAddPressed()
{
}

void COptionsGameConfigsTab::onGameDataEditPressed()
{
}

void COptionsGameConfigsTab::onGameDataRemovePressed()
{
}

	//-----------------------------------------------------------------------------------------//

COptionsBuildProgramsTab::COptionsBuildProgramsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QGridLayout();

	auto pConfigLabel = new QLabel( tr( "Configuration:" ) );
	m_pConfigCombo = new QComboBox( this );
	m_pConfigCombo->addItem( "Momentum" );

	auto pInfoLabel = new QLabel( tr( "Select the build and game exectuables for this game\nconfiguration:" ), this );

	m_pGameExe = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pGameExe->getLineEdit().setText( "path/to/chaos.exe" );
	m_pGameExe->getLabel().setText( tr( "Game Executable:" ) );

	m_pBSPExe = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pBSPExe->getLineEdit().setText( "path/to/vbsp.exe" );
	m_pBSPExe->getLabel().setText( tr( "BSP Executable:" ) );

	m_pPostCompExe = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pPostCompExe->getLineEdit().setText( "path/to/postcomp.exe" );
	m_pPostCompExe->getLabel().setText( tr( "Postcompiler Executable:" ) );

	m_pVISExe = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pVISExe->getLineEdit().setText( "path/to/vvis.exe" );
	m_pVISExe->getLabel().setText( tr( "VIS Executable:" ) );

	m_pRADExe = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pRADExe->getLineEdit().setText( "path/to/vrad.exe" );
	m_pRADExe->getLabel().setText( tr( "RAD Executable:" ) );

	m_pOutputDir = new CFileSelector( this, CFileSelector::DirsOnly );
	m_pOutputDir->getLineEdit().setText( "path/to/maps" );
	m_pOutputDir->getLabel().setText( tr( "Place compiled maps in this directory before running the game:" ) );

	pWidgetLayout->addWidget( pConfigLabel, 0, 0 );
	pWidgetLayout->addWidget( m_pConfigCombo, 1, 0, 1, 2 );
	pWidgetLayout->addWidget( pInfoLabel, 2, 0, 1, 2 );

	pWidgetLayout->addWidget( m_pGameExe, 3, 0, 1, 3 );
	pWidgetLayout->addWidget( m_pBSPExe, 4, 0, 1, 3 );
	pWidgetLayout->addWidget( m_pPostCompExe, 5, 0, 1, 3 );
	pWidgetLayout->addWidget( m_pVISExe, 6, 0, 1, 3 );
	pWidgetLayout->addWidget( m_pRADExe, 7, 0, 1, 3 );
	pWidgetLayout->addWidget( m_pOutputDir, 8, 0, 1, 3 );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

	//-----------------------------------------------------------------------------------------//

COptionsMaterialsTab::COptionsMaterialsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	m_pEnableColor = new QCheckBox( tr( "Enable color sort in material browser (requires restart)" ), this );

	pWidgetLayout->addWidget( addMaterialGroup() );
	pWidgetLayout->addWidget( m_pEnableColor );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGroupBox *COptionsMaterialsTab::addMaterialGroup()
{
	auto pMatGroup = new QGroupBox( tr( "Material" ), this );
	auto pMatLayout = new QGridLayout( pMatGroup );

	auto pMatLabel = new QLabel( tr( "Material directory exclusion list" ), this );
	m_pMaterialExclusionList = new QListWidget( this );
	m_pMaterialExclusionList->setMinimumHeight( 300 );
	auto pAddButton = new QPushButton( tr( "Add..." ), this );
	auto pRemoveButton = new QPushButton( tr( "Remove" ), this );

	pMatLayout->addWidget( pMatLabel, 0, 0 );
	pMatLayout->addWidget( m_pMaterialExclusionList, 1, 0, 3, 2 );
	pMatLayout->addWidget( pAddButton, 1, 3 );
	pMatLayout->addWidget( pRemoveButton, 2, 3 );

	connect( pAddButton, &QPushButton::released, this, &COptionsMaterialsTab::onAddPressed );
	connect( pRemoveButton, &QPushButton::released, this, &COptionsMaterialsTab::onRemovePressed );


	return pMatGroup;
}

void COptionsMaterialsTab::onAddPressed()
{
}

void COptionsMaterialsTab::onRemovePressed()
{
}

	//-----------------------------------------------------------------------------------------//

COptionsColorsTab::COptionsColorsTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	m_pCustomColors = new QCheckBox( tr( "Custom Colors" ), this );

	auto p2DColGroup = add2DColorGroup();
	auto pColGroup = addColorsGroup();

	p2DColGroup->setEnabled( false );
	pColGroup->setEnabled( false );

	pWidgetLayout->addWidget( m_pCustomColors );
	pWidgetLayout->addWidget( p2DColGroup );
	pWidgetLayout->addWidget( pColGroup );

	connect( m_pCustomColors, SIGNAL( toggled( bool ) ), p2DColGroup, SLOT( setEnabled( bool ) ) );
	connect( m_pCustomColors, SIGNAL( toggled( bool ) ), pColGroup, SLOT( setEnabled( bool ) ) );

	this->setLayout( pWidgetLayout );

	this->setFixedSize( this->sizeHint() );
}

QGroupBox *COptionsColorsTab::add2DColorGroup()
{
	auto pColGroup = new QGroupBox( tr( "2D Color Scaling" ), this );
	auto pColLayout = new QHBoxLayout( pColGroup );

	m_pAxis = new QCheckBox( tr( "Axis" ), this );
	m_pGrid = new QCheckBox( tr( "Grid" ), this );
	m_pDotGrid = new QCheckBox( tr( "Dot-Grid" ), this );
	m_p10Grid = new QCheckBox( tr( "10 Grid" ), this );
	m_p1024Grid = new QCheckBox( tr( "1024 Grid" ), this );

	pColLayout->addWidget( m_pAxis );
	pColLayout->addWidget( m_pGrid );
	pColLayout->addWidget( m_pDotGrid );
	pColLayout->addWidget( m_p10Grid );
	pColLayout->addWidget( m_p1024Grid );
	return pColGroup;
}

QGroupBox *COptionsColorsTab::addColorsGroup()
{
	// General Colors
	auto pColGroup = new QGroupBox( tr( "Colors" ), this );
	auto pColLayout = new QGridLayout( pColGroup );

	m_pGridColor = new CColorBox( this, "Grid" );
	m_pDotGridColor = new CColorBox( this, "Dot-Grid" );
	m_p10GridColor = new CColorBox( this, "10 Grid" );
	m_p1024GridColor = new CColorBox( this, "1024 Grid" );
	m_pBackgroundColor = new CColorBox( this, "Background" );

	m_pAxisColor = new CColorBox( this, "Axis" );
	m_pBrushColor = new CColorBox( this, "Brush" );
	m_pEntityColor = new CColorBox( this, "Entity" );
	m_pSelectionColor = new CColorBox( this, "Selection" );
	m_pVertexColor = new CColorBox( this, "Vertex" );

	pColLayout->addWidget( m_pGridColor, 0, 0 );
	pColLayout->addWidget( m_pDotGridColor, 1, 0 );
	pColLayout->addWidget( m_p10GridColor, 2, 0 );
	pColLayout->addWidget( m_p1024GridColor, 3, 0 );
	pColLayout->addWidget( m_pBackgroundColor, 4, 0 );

	pColLayout->addWidget( m_pAxisColor, 0, 1 );
	pColLayout->addWidget( m_pBrushColor, 1, 1 );
	pColLayout->addWidget( m_pEntityColor, 2, 1 );
	pColLayout->addWidget( m_pSelectionColor, 3, 1 );
	pColLayout->addWidget( m_pVertexColor, 4, 1 );

	// Tools
	auto pToolGroup = new QGroupBox( tr( "Tool" ), this );
	auto pToolLayout = new QVBoxLayout( pToolGroup );

	m_pHandleColor = new CColorBox( this, "Handle" );
	m_pBlockColor = new CColorBox( this, "Block" );
	m_pToolSelectionColor = new CColorBox( this, "Selection" );
	m_pMorphColor = new CColorBox( this, "Morph" );
	m_pPathColor = new CColorBox( this, "Path" );
	m_pDragColor = new CColorBox( this, "Drag" );

	pToolLayout->addWidget( m_pHandleColor );
	pToolLayout->addWidget( m_pBlockColor );
	pToolLayout->addWidget( m_pToolSelectionColor );
	pToolLayout->addWidget( m_pMorphColor );
	pToolLayout->addWidget( m_pPathColor );
	pToolLayout->addWidget( m_pDragColor );

	auto pModelColBox = new QGroupBox( tr( "Model Collision" ), this );
	auto pModelColLayout = new QVBoxLayout( pModelColBox );

	m_pWireframeColor = new CColorBox( this, "Wireframe" );
	m_pWireframeNonSolidColor = new CColorBox( this, "Wireframe (Not Solid)" );

	pModelColLayout->addWidget( m_pWireframeColor );
	pModelColLayout->addWidget( m_pWireframeNonSolidColor );

	pColLayout->addWidget( pToolGroup, 0, 3, 6, 1 );
	pColLayout->addWidget( pModelColBox, 5, 0, 1, 2, Qt::AlignLeft );

	return pColGroup;
}

//-----------------------------------------------------------------------------------------//

CColorBox::CColorBox( QWidget *pParent, const QString &label ) :
	QWidget( pParent )
{
	auto pLayout = new QHBoxLayout( this );

	m_pLabel = new QLabel( label, this );

	m_pButton = new CColorPushButton( this, Qt::white );
	m_pButton->setFixedWidth( 25 );

	// FOR DEBUG
	setColor( QColor( qrand() % 255, qrand() % 255, qrand() % 255 ) );

	pLayout->addWidget( m_pLabel, 0, Qt::AlignLeft );
	pLayout->addWidget( m_pButton, 0, Qt::AlignLeft );

	pLayout->setAlignment( Qt::AlignRight );

	connect( m_pButton, &QPushButton::released, this, &CColorBox::onButtonPressed );
}

void CColorBox::setColor( const QColor &pNewColor )
{
	m_Color = pNewColor;
	m_pButton->setColor( m_Color );
}

void CColorBox::onButtonPressed()
{
	m_Color = QColorDialog::getColor( m_Color, this );
	setColor( m_Color );
}

//-----------------------------------------------------------------------------------------//

CColorPushButton::CColorPushButton( QWidget *pParent, const QColor &color ) :
	QPushButton( pParent )
{
	m_Color = color;
}

void CColorPushButton::setColor( const QColor &pNewColor )
{
	m_Color = pNewColor;
}

void CColorPushButton::paintEvent( QPaintEvent *pe )
{
	QPushButton::paintEvent( pe );

	QPainter p( this );
	// We set it to 14 since the pen adds 1 pixels
	QRect rect( 7, 4, 14, 14 );
	QPoint center( this->rect().center().x() - 1, this->rect().center().y() - 1 );

	rect.moveCenter( center );

	// Give it a black border
	p.setPen( Qt::black );
	// If we're disabled, colour our box white instead
	// if we're not, then paint our normal colour
	if ( !isEnabled() )
		p.setBrush( Qt::white );
	else
		p.setBrush( m_Color );
	p.drawRect( rect );
}