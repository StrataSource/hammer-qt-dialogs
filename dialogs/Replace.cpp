#include "dialogs/Replace.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace ui;

CReplace::CReplace( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Replace" ) );

	auto pDialogLayout = new QGridLayout( this );

	auto pFindLabel = new QLabel( tr( "Find what:" ), this );
	m_pFindBox = new QLineEdit( this );
	auto pFindBoxLayout = new QHBoxLayout( this );
	pFindBoxLayout->setSpacing( 20 );
	pFindBoxLayout->addWidget( pFindLabel );
	pFindBoxLayout->addWidget( m_pFindBox );

	auto pReplaceLabel = new QLabel( tr( "Replace with:" ), this );
	m_pReplaceBox = new QLineEdit( this );
	auto pReplaceBoxLayout = new QHBoxLayout( this );
	pReplaceBoxLayout->addWidget( pReplaceLabel );
	pReplaceBoxLayout->addWidget( m_pReplaceBox );

	// Push Buttons
	auto pFindNextButton = new QPushButton( tr( "Find Next" ), this );
	auto pReplaceButton = new QPushButton( tr( "Replace" ), this );
	auto pReplaceAllButton = new QPushButton( tr( "Replace All" ), this );
	auto pCancelButton = new QPushButton( tr( "Cancel" ), this );

	// Checkboxes
	m_pWholeWordsOnly = new QCheckBox( tr( "Whole words only" ), this );
	m_pCaseSensitive = new QCheckBox( tr( "Case Sensitive" ), this );

	// Find In box
	auto pFindInGroup = new QGroupBox( tr( "Find in" ), this );
	auto pFindInLayout = new QVBoxLayout( pFindInGroup );
	m_pSelectionButton = new QRadioButton( tr( "Selection" ), this );
	m_pSelectionButton->setChecked( true );
	m_pEntireFileButton = new QRadioButton( tr( "Entire File" ), this );
	m_pVisibleObjectsOnly = new QCheckBox( tr( "Visible objects only" ), this );

	pFindInLayout->addWidget( m_pSelectionButton );
	pFindInLayout->addWidget( m_pEntireFileButton );
	pFindInLayout->addWidget( m_pVisibleObjectsOnly );

	// Add all the widgets to the layout
	int row = 0;

	// 0
	pDialogLayout->addLayout( pFindBoxLayout, row, 0, 1, 3 );
	pDialogLayout->addWidget( pFindNextButton, row, 3 );
	pFindNextButton->setMaximumSize( pFindNextButton->sizeHint() );
	row++;

	// 1
	pDialogLayout->addLayout( pReplaceBoxLayout, row, 0, 1, 3 );
	pDialogLayout->addWidget( pReplaceButton, row, 3 );
	row++;

	// 2
	pDialogLayout->addWidget( m_pWholeWordsOnly, row, 0 );
	pDialogLayout->addWidget( pFindInGroup, row, 1, 3, 2, Qt::AlignRight );
	pDialogLayout->addWidget( pReplaceAllButton, row, 3 );
	row++;

	// 3
	pDialogLayout->addWidget( m_pCaseSensitive, row, 0 );
	pDialogLayout->addWidget( pCancelButton, row, 3 );

	// Setup actions
	connect( pFindNextButton, &QPushButton::released, this, &CReplace::onFindNextPressed );
	connect( pReplaceButton, &QPushButton::released, this, &CReplace::onReplacePressed );
	connect( pReplaceAllButton, &QPushButton::released, this, &CReplace::onReplaceAllPressed );
	connect( pCancelButton, &QPushButton::released, this, &CReplace::onCancelPressed );

	this->setLayout( pDialogLayout );

	this->setMinimumWidth( this->sizeHint().width() );
	this->setFixedHeight( this->sizeHint().height() );
}

void CReplace::onFindNextPressed()
{
	// QT_TODO: hammer integration
}

void CReplace::onReplacePressed()
{
	// QT_TODO: hammer integration
}

void CReplace::onReplaceAllPressed()
{
	// QT_TODO: hammer integration
}

void CReplace::onCancelPressed()
{
	this->close();
}