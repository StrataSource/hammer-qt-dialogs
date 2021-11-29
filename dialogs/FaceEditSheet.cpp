#include "dialogs/FaceEditSheet.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDoubleValidator>

using namespace ui;

CFaceEditSheet::CFaceEditSheet( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Face Edit Sheet" ) );

	auto pDialogLayout = new QVBoxLayout( this );

	auto pFaceEditTabWidget = new QTabWidget( this );
	//pFaceEditTabWidget->addTab( new CFaceEditMaterialTab( this ), tr( "Material" ) );
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

	this->setLayout( pWidgetLayout );
}

//-----------------------------------------------------------------------------------------//

CFaceEditDisplacementTab::CFaceEditDisplacementTab( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout( this );

	int row = 0;

#pragma region Tools
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
#pragma endregion Tools

#pragma region Attribute Box

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
	//pLabelLayout->setSpacing( 0 );
	pLabelLayout->addWidget( pPowerLabel, 0, Qt::AlignRight  );
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

#pragma endregion Attribute Box	

#pragma region Masks & Adjacent Button

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

#pragma endregion Masks & Adjacent Button

	pWidgetLayout->addWidget( pToolsBox );
	pWidgetLayout->addWidget( pAttribBox );
	pWidgetLayout->addLayout( pBottomRow );

	// Connect actions
	connect( pApplyButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onApplyPressed );
	connect( pAdjacentButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSelectAdjacentPressed );
	connect( pSelectButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSelectPressed );
	connect( pPaintGeometryButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onPaintGeometryPressed );
	connect( pPaintAlphaButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onPaintAlphaPressed );
	connect( pInvertAlphaButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onInvertAlphaPressed );
	connect( pSculptButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSculptPressed );
	connect( pCreateButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onCreatePressed );
	connect( pSubdivideButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSubdividePressed );
	connect( pNoiseButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onNoisePressed );
	connect( pSewButton, &QPushButton::released, this, &CFaceEditDisplacementTab::onSewPressed );

	this->setLayout( pWidgetLayout );
}

void CFaceEditDisplacementTab::onApplyPressed()
{
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