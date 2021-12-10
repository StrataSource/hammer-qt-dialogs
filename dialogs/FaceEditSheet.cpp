#include "dialogs/FaceEditSheet.h"

#include <QDoubleValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>

using namespace ui;

CFaceEditSheet::CFaceEditSheet( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Face Edit Sheet" ) );

	auto pDialogLayout = new QVBoxLayout( this );

	auto pFaceEditTabWidget = new QTabWidget( this );
	pFaceEditTabWidget->addTab( new CFaceEditMaterialTab( this ), tr( "Material" ) );
	pFaceEditTabWidget->addTab( new CFaceEditDisplacementTab( this ), tr( "Displacement" ) );

	pDialogLayout->addWidget( pFaceEditTabWidget );

	this->setLayout( pDialogLayout );

	this->setFixedSize( this->sizeHint() );
}

//-----------------------------------------------------------------------------------------//

CFaceEditMaterialTab::CFaceEditMaterialTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QGridLayout( this );

	int row = 0;

	auto pLightmapScaleLabel = new QLabel( tr( "Lightmap scale:" ) );
	auto pUnitsLabel = new QLabel( tr( "(units/luxel)" ) );

	m_pLightmapScale = new QSpinBox( this );
	m_pLightmapScale->setValue( 16 );
	m_pLightmapScale->setMinimum( 1 );
	m_pLightmapScale->setFixedWidth( 50 );

	auto pRotationLayout = new QFormLayout( this );
	auto pRotationLabel = new QLabel( tr( "Rotation:" ) );
	m_pRotation = new QDoubleSpinBox( this );
	m_pRotation->setFixedWidth( 50 );
	pRotationLayout->addRow( pRotationLabel, m_pRotation );

	// Current Texture
	auto pCurrentTextureLabel = new QLabel( tr( "Current Texture" ), this );
	m_pCurrentTextureBox = new QComboBox( this );
	m_pCurrentTextureBox->setEditable( true );
	m_pCurrentTextureBox->addItem( ":/zoo_textures/128x128.png" );

	m_pTextureLabel = new QLabel( this );
	auto pPixMap = new QPixmap( ":/zoo_textures/128x128.png" );
	m_pTextureLabel->setPixmap( pPixMap->scaled( 80, 80 ) );

	// Buttons
	auto pHideMaskButton = new QPushButton( tr( "Hide mask" ), this );
	auto pBrowseButton = new QPushButton( tr( "Browse..." ), this );
	auto pReplaceButton = new QPushButton( tr( "Replace..." ), this );
	auto pMarkButton = new QPushButton( tr( "Mark" ), this );
	auto pApplyButton = new QPushButton( tr( "Apply" ), this );
	pApplyButton->setFixedHeight( 52 );
	auto pSmoothingGroupsButton = new QPushButton( tr( "Smoothing Groups" ), this );

	auto pMaskBrowRepLayout = new QVBoxLayout( this );
	pMaskBrowRepLayout->addWidget( pHideMaskButton );
	pMaskBrowRepLayout->addWidget( pBrowseButton );
	pMaskBrowRepLayout->addWidget( pReplaceButton );

	auto pModeLabel = new QLabel( tr( "Mode:" ), this );
	m_pModeBox = new QComboBox( this );
	m_pModeBox->addItem( tr( "Lift+Select" ) );
	m_pModeBox->addItem( tr( "Lift" ) );
	m_pModeBox->addItem( tr( "Select" ) );
	m_pModeBox->addItem( tr( "Apply (textures only)" ) );
	m_pModeBox->addItem( tr( "Apply (textures + values)" ) );
	m_pModeBox->addItem( tr( "Align To View" ) );

	// Add components to widget layout
	pWidgetLayout->addLayout( addTextureShiftAndScale(), row, 0, 3, 2 );
	pWidgetLayout->addWidget( pLightmapScaleLabel, row, 3 );
	pWidgetLayout->addWidget( pUnitsLabel, row, 3, 1, 1, Qt::AlignRight );
	row++;

	// 1
	pWidgetLayout->addWidget( m_pLightmapScale, row, 3 );
	row++;

	// 2
	pWidgetLayout->addLayout( pRotationLayout, row, 3 );
	row++;

	// 3
	pWidgetLayout->addLayout( addTextureGroup(), row, 0, 1, 2, Qt::AlignTop );
	pWidgetLayout->addWidget( addJustifyBox(), row, 3 );
	pWidgetLayout->addWidget( pCurrentTextureLabel, row, 0, Qt::AlignBottom );
	row++;

	// 4
	pWidgetLayout->addWidget( m_pCurrentTextureBox, row, 0, 1, 4, Qt::AlignTop );
	row++;

	// 5
	pWidgetLayout->addWidget( m_pTextureLabel, row, 0, 3, 1 );
	pWidgetLayout->addLayout( pMaskBrowRepLayout, row, 1, 3, 1 );
	pWidgetLayout->addWidget( addAlignBox(), row, 2, 1, 2, Qt::AlignRight );
	row = 7;

	// 8
	pWidgetLayout->addWidget( pModeLabel, row, 3, Qt::AlignBottom );
	row++;

	// 9
	pWidgetLayout->addWidget( pMarkButton, row, 0 );
	pWidgetLayout->addWidget( pApplyButton, row, 1, 2, 1 );
	pWidgetLayout->addWidget( m_pModeBox, row, 3, 1, 1, Qt::AlignTop );
	row++;

	// 10
	pWidgetLayout->addWidget( pSmoothingGroupsButton, row, 3, 1, 1 );

	// setup actions
	connect( pHideMaskButton, &QPushButton::released, this, &CFaceEditMaterialTab::onHideMaskPressed );
	connect( pBrowseButton, &QPushButton::released, this, &CFaceEditMaterialTab::onBrowsePressed );
	connect( pReplaceButton, &QPushButton::released, this, &CFaceEditMaterialTab::onReplacePressed );
	connect( pApplyButton, &QPushButton::released, this, &CFaceEditMaterialTab::onApplyPressed );
	connect( pMarkButton, &QPushButton::released, this, &CFaceEditMaterialTab::onMarkPressed );
	connect( pSmoothingGroupsButton, &QPushButton::released, this, &CFaceEditMaterialTab::onSmoothingGroupsPressed );

	this->setLayout( pWidgetLayout );
}

QGridLayout *CFaceEditMaterialTab::addTextureShiftAndScale()
{
	auto pMethodLayout = new QGridLayout( this );

	auto pTexScaleLabel = new QLabel( tr( "Texture scale:" ), this );
	auto pTexShiftLabel = new QLabel( tr( "Texture shift:" ), this );

	auto pScaleXLayout = new QFormLayout( this );
	auto pScaleXLabel = new QLabel( "X:", this );
	m_pTextureScaleX = new QDoubleSpinBox( this );
	pScaleXLayout->addRow( pScaleXLabel, m_pTextureScaleX );

	auto pScaleYLayout = new QFormLayout( this );
	auto pScaleYLabel = new QLabel( "Y:", this );
	m_pTextureScaleY = new QDoubleSpinBox( this );
	pScaleYLayout->addRow( pScaleYLabel, m_pTextureScaleY );

	auto pShiftXLayout = new QFormLayout( this );
	auto pShiftXLabel = new QLabel( "X:", this );
	m_pTextureShiftX = new QSpinBox( this );
	pShiftXLayout->addRow( pShiftXLabel, m_pTextureShiftX );

	auto pShiftYLayout = new QFormLayout( this );
	auto pShiftYLabel = new QLabel( "Y:", this );
	m_pTextureShiftY = new QSpinBox( this );
	pShiftYLayout->addRow( pShiftYLabel, m_pTextureShiftY );

	auto pXButton = new QPushButton( "X", this );
	auto pYButton = new QPushButton( "Y", this );
	pXButton->setFixedWidth( 20 );
	pYButton->setFixedWidth( 20 );

	int row = 0;
	pMethodLayout->addWidget( pTexScaleLabel, row, 0 );
	pMethodLayout->addWidget( pTexShiftLabel, row, 1 );
	row++;

	// 1
	pMethodLayout->addLayout( pScaleXLayout, row, 0 );
	pMethodLayout->addLayout( pShiftXLayout, row, 1 );
	pMethodLayout->addWidget( pXButton, row, 2 );
	row++;

	// 2
	pMethodLayout->addLayout( pScaleYLayout, row, 0 );
	pMethodLayout->addLayout( pShiftYLayout, row, 1 );
	pMethodLayout->addWidget( pYButton, row, 2 );

	connect( pXButton, &QPushButton::released, this, &CFaceEditMaterialTab::onXPressed );
	connect( pYButton, &QPushButton::released, this, &CFaceEditMaterialTab::onYPressed );

	return pMethodLayout;
}

QGroupBox *CFaceEditMaterialTab::addAlignBox()
{
	auto pAlignBox = new QGroupBox( tr( "Align" ), this );
	auto pAlignLayout = new QHBoxLayout( pAlignBox );
	m_pAlignWorld = new QCheckBox( tr( "World" ), this );
	m_pAlignFace = new QCheckBox( tr( "Face" ), this );
	pAlignLayout->addWidget( m_pAlignWorld );
	pAlignLayout->addWidget( m_pAlignFace );

	return pAlignBox;
}

QGroupBox *CFaceEditMaterialTab::addJustifyBox()
{
	auto pJustifyBox = new QGroupBox( tr( "Justify" ), this );
	auto pJustifyBoxLayout = new QVBoxLayout( pJustifyBox );
	pJustifyBoxLayout->setMargin( 2 );

	auto pJustifyButtonsLayout = new QHBoxLayout( this );
	auto pLButton = new QPushButton( "L", this );
	pLButton->setFixedSize( 20, 20 );
	auto pRButton = new QPushButton( "R", this );
	pRButton->setFixedSize( 20, 20 );
	auto pFitButton = new QPushButton( "Fit", this );
	pFitButton->setFixedSize( 20, 20 );
	auto pTButton = new QPushButton( "T", this );
	pTButton->setFixedSize( 20, 20 );
	auto pBButton = new QPushButton( "B", this );
	pBButton->setFixedSize( 20, 20 );
	auto pCButton = new QPushButton( "C", this );
	pCButton->setFixedSize( 20, 20 );

	// Layout stuff
	pJustifyButtonsLayout->setSpacing( 0 );
	pJustifyButtonsLayout->addWidget( pLButton );
	pJustifyButtonsLayout->addWidget( pRButton );
	pJustifyButtonsLayout->addWidget( pFitButton );
	pJustifyButtonsLayout->addSpacing( 5 );
	pJustifyButtonsLayout->addWidget( pTButton );
	pJustifyButtonsLayout->addWidget( pBButton );
	pJustifyButtonsLayout->addWidget( pCButton );

	m_pTreatAsOne = new QCheckBox( tr( "Treat as one" ), this );

	pJustifyBoxLayout->addLayout( pJustifyButtonsLayout );
	pJustifyBoxLayout->addWidget( m_pTreatAsOne );

	connect( pLButton, &QPushButton::released, this, &CFaceEditMaterialTab::onLPressed );
	connect( pRButton, &QPushButton::released, this, &CFaceEditMaterialTab::onRPressed );
	connect( pFitButton, &QPushButton::released, this, &CFaceEditMaterialTab::onFitPressed );
	connect( pTButton, &QPushButton::released, this, &CFaceEditMaterialTab::onTPressed );
	connect( pBButton, &QPushButton::released, this, &CFaceEditMaterialTab::onBPressed );
	connect( pCButton, &QPushButton::released, this, &CFaceEditMaterialTab::onCPressed );

	return pJustifyBox;
}

QVBoxLayout *CFaceEditMaterialTab::addTextureGroup()
{
	auto pTextureGroupLayout = new QVBoxLayout( this );

	auto pTextureGroupSizeLayout = new QHBoxLayout( this );
	auto pTextureGroupLabel = new QLabel( tr( "Texture group:" ), this );
	auto pTexSizeLabel = new QLabel( tr( "128x128" ), this );
	pTextureGroupSizeLayout->addWidget( pTextureGroupLabel );
	pTextureGroupSizeLayout->addWidget( pTexSizeLabel );

	m_pTextureGroupBox = new QComboBox( this );
	m_pTextureGroupBox->addItem( "All Textures" );

	pTextureGroupLayout->addLayout( pTextureGroupSizeLayout );
	pTextureGroupLayout->addWidget( m_pTextureGroupBox );

	return pTextureGroupLayout;
}

void CFaceEditMaterialTab::onXPressed()
{
	// QT_TODO: Hammer intergration
}

void CFaceEditMaterialTab::onYPressed()
{
}

void CFaceEditMaterialTab::onLPressed()
{
}

void CFaceEditMaterialTab::onRPressed()
{
}

void CFaceEditMaterialTab::onFitPressed()
{
}

void CFaceEditMaterialTab::onTPressed()
{
}

void CFaceEditMaterialTab::onBPressed()
{
}

void CFaceEditMaterialTab::onCPressed()
{
}

void CFaceEditMaterialTab::onHideMaskPressed()
{
}

void CFaceEditMaterialTab::onBrowsePressed()
{
}

void CFaceEditMaterialTab::onReplacePressed()
{
}

void CFaceEditMaterialTab::onApplyPressed()
{
}

void CFaceEditMaterialTab::onMarkPressed()
{
}

void CFaceEditMaterialTab::onSmoothingGroupsPressed()
{
}

//-----------------------------------------------------------------------------------------//

CFaceEditDisplacementTab::CFaceEditDisplacementTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout( this );

	auto pBottomRow = new QHBoxLayout( this );

	auto pMasksBox = new QGroupBox( tr( "Masks" ), this );
	auto pMasksLayout = new QHBoxLayout( pMasksBox );
	m_pGridBox = new QCheckBox( tr( "Grid" ), this );
	m_pSelectBox = new QCheckBox( tr( "Select" ), this );
	pMasksLayout->addWidget( m_pGridBox, 0 );
	pMasksLayout->addWidget( m_pSelectBox, 0 );

	auto pAdjacentButton = new QPushButton( tr( "Select Adjacent" ), this );

	pBottomRow->addWidget( pMasksBox );
	pBottomRow->addWidget( pAdjacentButton, 0, Qt::AlignRight | Qt::AlignBottom );

	pWidgetLayout->addWidget( addToolsBox() );
	pWidgetLayout->addWidget( addAttributesBox() );
	pWidgetLayout->addLayout( pBottomRow );

	// Connect action
	connect( pAdjacentButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSelectAdjacentPressed );

	this->setLayout( pWidgetLayout );
}

QGroupBox *CFaceEditDisplacementTab::addToolsBox()
{
	int row = 0;

	auto pToolsBox = new QGroupBox( tr( "Tools" ), this );
	auto pToolsBoxLayout = new QGridLayout( pToolsBox );
	pToolsBoxLayout->setHorizontalSpacing( 0 );

	int height = 36;
	int width = 60;
	auto pSelectButton = new QPushButton( tr( "Select" ), this );
	pSelectButton->setFixedSize( width, height );
	auto pPaintGeometryButton = new QPushButton( tr( "Paint\nGeometry" ), this );
	pPaintGeometryButton->setFixedSize( width, height );
	auto pPaintAlphaButton = new QPushButton( tr( "Paint\nAlpha" ), this );
	pPaintAlphaButton->setFixedSize( width, height );
	auto pInvertAlphaButton = new QPushButton( tr( "Invert\nAlpha" ), this );
	pInvertAlphaButton->setFixedSize( width, height );
	auto pSculptButton = new QPushButton( tr( "Sculpt" ), this );
	pSculptButton->setFixedSize( width, height );

	auto pCreateButton = new QPushButton( tr( "Create" ), this );
	pCreateButton->setFixedSize( width, height );
	auto pDestroyButton = new QPushButton( tr( "Destroy" ), this );
	pDestroyButton->setFixedSize( width, height );
	auto pSubdivideButton = new QPushButton( tr( "Subdivide" ), this );
	pSubdivideButton->setFixedSize( width, height );
	auto pNoiseButton = new QPushButton( tr( "Noise" ), this );
	pNoiseButton->setFixedSize( width, height );
	auto pSewButton = new QPushButton( tr( "Sew" ), this );
	pSewButton->setFixedSize( width, height );

	pToolsBoxLayout->addWidget( pSelectButton, row, 0 );
	pToolsBoxLayout->addWidget( pPaintGeometryButton, row, 1 );
	pToolsBoxLayout->addWidget( pPaintAlphaButton, row, 2 );
	pToolsBoxLayout->addWidget( pInvertAlphaButton, row, 3 );
	pToolsBoxLayout->addWidget( pSculptButton, row, 4 );
	row++;

	pToolsBoxLayout->addWidget( pCreateButton, row, 0 );
	pToolsBoxLayout->addWidget( pDestroyButton, row, 1 );
	pToolsBoxLayout->addWidget( pSubdivideButton, row, 2 );
	pToolsBoxLayout->addWidget( pNoiseButton, row, 3 );
	pToolsBoxLayout->addWidget( pSewButton, row, 4 );

	connect( pSelectButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSelectPressed );
	connect( pPaintGeometryButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onPaintGeometryPressed );
	connect( pPaintAlphaButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onPaintAlphaPressed );
	connect( pInvertAlphaButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onInvertAlphaPressed );
	connect( pSculptButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSculptPressed );
	connect( pCreateButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onCreatePressed );
	connect( pSubdivideButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSubdividePressed );
	connect( pNoiseButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onNoisePressed );
	connect( pSewButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSewPressed );

	return pToolsBox;
}

QGroupBox *CFaceEditDisplacementTab::addAttributesBox()
{
	auto pAttribBox = new QGroupBox( tr( "Attributes" ), this );
	auto pAttribLayout = new QGridLayout( pAttribBox );

	int boxLength = 70;
	auto pPowerLabel = new QLabel( tr( "Power" ), this );
	m_pPowerSpinBox = new QSpinBox( this );
	m_pPowerSpinBox->setFixedWidth( boxLength );

	auto pElevLabel = new QLabel( tr( "Elev" ), this );
	m_pElevSpinBox = new QDoubleSpinBox( this );
	m_pElevSpinBox->setSingleStep( 0.5 );
	m_pElevSpinBox->setFixedWidth( boxLength );

	auto pScaleLabel = new QLabel( tr( "Scale" ), this );
	auto m_pScale = new QLineEdit( this );
	m_pScale->setValidator( new QDoubleValidator( m_pScale ) );
	// We do this so it doesn't span the entire grid
	m_pScale->setFixedWidth( boxLength );

	m_pNoPhysColBox = new QCheckBox( tr( "No Physics Collision" ), this );
	m_pNoHullColBox = new QCheckBox( tr( "No Hull Collision" ), this );
	m_pNoRayColBox = new QCheckBox( tr( "No Ray Collision" ), this );
	auto pColLayout = new QVBoxLayout( this );
	pColLayout->addWidget( m_pNoPhysColBox );
	pColLayout->addWidget( m_pNoHullColBox );
	pColLayout->addWidget( m_pNoRayColBox );

	auto pApplyButton = new QPushButton( tr( "Apply" ), this );
	pApplyButton->setMaximumWidth( 60 );

	// Add to attribute layout
	auto pLabelLayout = new QVBoxLayout( this );
	pLabelLayout->addWidget( pPowerLabel, 0, Qt::AlignRight );
	pLabelLayout->addWidget( pElevLabel, 0, Qt::AlignRight );
	pLabelLayout->addWidget( pScaleLabel, 0, Qt::AlignRight );

	auto pInputLayout = new QVBoxLayout( this );
	pInputLayout->setSpacing( 12 );
	pInputLayout->addWidget( m_pPowerSpinBox );
	pInputLayout->addWidget( m_pElevSpinBox );
	pInputLayout->addWidget( m_pScale );

	pAttribLayout->addLayout( pLabelLayout, 0, 0, 3, 1, Qt::AlignLeft );
	pAttribLayout->addLayout( pInputLayout, 0, 1, 3, 1, Qt::AlignLeft );

	pAttribLayout->addLayout( pColLayout, 0, 3, 2, 1, Qt::AlignRight );
	pAttribLayout->addWidget( pApplyButton, 2, 3, Qt::AlignRight );

	connect( pApplyButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onApplyPressed );

	return pAttribBox;
}

void CFaceEditDisplacementTab::onApplyPressed()
{
	// QT_TODO: Hammer intergration
}

void CFaceEditDisplacementTab::onSelectAdjacentPressed()
{
}

void CFaceEditDisplacementTab::onSelectPressed()
{
}

void CFaceEditDisplacementTab::onPaintGeometryPressed()
{
}

void CFaceEditDisplacementTab::onPaintAlphaPressed()
{
}

void CFaceEditDisplacementTab::onInvertAlphaPressed()
{
}

void CFaceEditDisplacementTab::onSculptPressed()
{
}

void CFaceEditDisplacementTab::onCreatePressed()
{
}

void CFaceEditDisplacementTab::onDestroyPressed()
{
}

void CFaceEditDisplacementTab::onSubdividePressed()
{
}

void CFaceEditDisplacementTab::onNoisePressed()
{
}

void CFaceEditDisplacementTab::onSewPressed()
{
}