#include "dialogs/SmoothingGroups.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

using namespace ui;

CSmoothingGroups::CSmoothingGroups( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Smoothing Groups" ) );

	auto pDialogLayout = new QVBoxLayout( this );

	// Smooth
	auto pSmoothGroup = new QGroupBox( tr( "Smooth" ), this );
	auto pSmoothLayout = new QGridLayout( pSmoothGroup );
	pSmoothLayout->setVerticalSpacing( 0 );
	pSmoothLayout->setHorizontalSpacing( 0 );

	int row = 0;
	for ( int i = 1; i < 25; i++ )
	{
		auto pButton = new QPushButton( QString::number( i ), this );
		pButton->setMaximumWidth( 25 );
		pButton->setMaximumHeight( 20 );
		connect( pButton, &QPushButton::released, [this, i]
				 {
					 onSmoothPressed( i );
				 } );

		// Add to the dialog
		pSmoothLayout->addWidget( pButton, row, ( i - 1 ) % 8 );

		// Increment the row
		if ( i % 8 == 0 )
			row++;
	}

	pDialogLayout->addWidget( pSmoothGroup );

	// Hard
	row = 0;
	auto pHardGroup = new QGroupBox( tr( "Hard" ), this );
	auto pHardLayout = new QGridLayout( pHardGroup );
	pHardLayout->setVerticalSpacing( 0 );
	pHardLayout->setHorizontalSpacing( 0 );

	for ( int i = 25; i < 33; i++ )
	{
		auto pButton = new QPushButton( QString::number( i ), this );
		pButton->setMaximumWidth( 25 );
		pButton->setMaximumHeight( 20 );
		connect( pButton, &QPushButton::released, [this, i]
				 {
					 onHardPressed( i );
				 } );

		// Add to the dialog
		pHardLayout->addWidget( pButton, row, ( i - 1 ) % 8 );

		// Increment the row
		if ( i % 8 == 0 )
			row++;
	}

	pDialogLayout->addWidget( pHardGroup );

	this->setLayout( pDialogLayout );
	this->setFixedSize( this->sizeHint() );
}

void CSmoothingGroups::onSmoothPressed( int value )
{
	// QT_TODO: hammer integration
}

void CSmoothingGroups::onHardPressed( int value )
{
	// QT_TODO: hammer integration
}