#include "dialogs/Transform.h"

#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

using namespace ui;

CTransform::CTransform( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Transformation" ) );

	auto pDialogLayout = new QGridLayout( this );

	auto pButtonBox = new QDialogButtonBox( this );
	auto pOkButton = pButtonBox->addButton( QDialogButtonBox::Ok );
	auto pCancelButton = pButtonBox->addButton( QDialogButtonBox::Cancel );

	auto pModeLabel = new QLabel( "Mode:", this );
	auto pValueLabel = new QLabel( "Values:", this );

	m_pRotate = new QRadioButton( tr( "Rotate" ), this );
	m_pRotate->setChecked( true ); // Set this as the first one checked
	m_pScale = new QRadioButton( tr( "Scale" ), this );
	m_pMove = new QRadioButton( tr( "Move" ), this );

	auto pXLayout = new QHBoxLayout( this );
	auto pXLabel = new QLabel( "X:", this );
	m_pXValue = new QLineEdit( "0", this );
	m_pXValue->setValidator( new QDoubleValidator( m_pXValue ) );
	pXLayout->addWidget( pXLabel );
	pXLayout->addWidget( m_pXValue );

	auto pYLayout = new QHBoxLayout( this );
	auto pYLabel = new QLabel( "Y:", this );
	m_pYValue = new QLineEdit( "0", this );
	m_pYValue->setValidator( new QDoubleValidator( m_pYValue ) );
	pYLayout->addWidget( pYLabel );
	pYLayout->addWidget( m_pYValue );

	auto pZLayout = new QHBoxLayout( this );
	auto pZLabel = new QLabel( "Z:", this );
	m_pZValue = new QLineEdit( "0", this );
	m_pZValue->setValidator( new QDoubleValidator( m_pZValue ) );
	pZLayout->addWidget( pZLabel );
	pZLayout->addWidget( m_pZValue );

	// Add widgets to the grid layout
	int row = 0;

	// 0
	pDialogLayout->addWidget( pModeLabel, row, 0 );
	pDialogLayout->addWidget( pValueLabel, row, 1 );
	row++;

	// 1
	pDialogLayout->addWidget( m_pRotate, row, 0 );
	pDialogLayout->addLayout( pXLayout, row, 1 );
	row++;

	// 2
	pDialogLayout->addWidget( m_pScale, row, 0 );
	pDialogLayout->addLayout( pYLayout, row, 1 );
	row++;

	// 3
	pDialogLayout->addWidget( m_pMove, row, 0 );
	pDialogLayout->addLayout( pZLayout, row, 1 );
	row++;

	// 4
	pDialogLayout->addWidget( pButtonBox, row, 0, 1, 2, Qt::AlignCenter );
	;

	this->setLayout( pDialogLayout );

	// Setup actions
	connect( pOkButton, &QPushButton::released, this, &CTransform::onOkPressed );
	connect( pCancelButton, &QPushButton::released, this, &CTransform::onCancelPressed );

	this->setFixedSize( this->sizeHint() );
};

void CTransform::onCancelPressed()
{
	this->close();
}

void CTransform::onOkPressed()
{
	// QT_TODO: hammer integration
}