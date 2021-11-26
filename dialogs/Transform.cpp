#include "dialogs/Transform.h"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QPushButton>

using namespace ui;

CTransform::CTransform( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Transformation" ) );

	auto pDialogLayout = new QGridLayout( this );

	auto pOkButton = new QPushButton( tr( "Ok" ), this );
	auto pCancelButton = new QPushButton( tr( "Cancel" ), this );

	auto pModeLabel = new QLabel( "Mode:", this );
	auto pValueLabel = new QLabel( "Values:", this );

	m_pRotate = new QRadioButton( tr( "Rotate" ), this );
	m_pRotate->setChecked( true ); // Set this as the first one checked
	m_pScale = new QRadioButton( tr( "Scale" ), this );
	m_pMove = new QRadioButton( tr( "Move" ), this );

	auto pXLabel = new QLabel( "X:", this );
	m_pXValue = new QLineEdit( "0", this );
	m_pXValue->setValidator( new QDoubleValidator( m_pXValue ) );
	auto pYLabel = new QLabel( "Y:", this );
	m_pYValue = new QLineEdit( "0", this );
	m_pYValue->setValidator( new QDoubleValidator( m_pYValue ) );
	auto pZLabel = new QLabel( "Z:", this );
	m_pZValue = new QLineEdit( "0", this );
	m_pZValue->setValidator( new QDoubleValidator( m_pZValue ) );

	// Add widgets to the grid layout
	int row = 0;

	//0
	pDialogLayout->addWidget( pModeLabel, row, 0 );
	pDialogLayout->addWidget( pValueLabel, row, 1 );
	row++;

	//1
	pDialogLayout->addWidget( m_pRotate, row, 0 );
	pDialogLayout->addWidget( pXLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pXValue, row, 1 );
	row++;

	//2
	pDialogLayout->addWidget( m_pScale, row, 0 );
	pDialogLayout->addWidget( pYLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pYValue, row, 1 );
	row++;

	//3
	pDialogLayout->addWidget( m_pMove, row, 0 );
	pDialogLayout->addWidget( pZLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pZValue, row, 1 );
	row++;

	//4
	pDialogLayout->addWidget( pOkButton, row, 0 );
	pDialogLayout->addWidget( pCancelButton, row, 1 );

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