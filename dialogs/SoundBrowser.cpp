#include "dialogs/SoundBrowser.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

using namespace ui;

CSoundBrowser::CSoundBrowser( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Sound Resource Browser" ) );

	auto pDialogLayout = new QGridLayout( this );

	// Sounds list
	auto pSoundsLabel = new QLabel( tr( "Sounds:" ), this );
	m_pSoundList = new QListWidget( this );

	// Add components to grid
	pDialogLayout->addWidget( pSoundsLabel, 0, 0 );
	pDialogLayout->addWidget( m_pSoundList, 1, 0, 1, 5 );

	for ( int i = 0; i < 200; i++ )
	{
		m_pSoundList->addItem( "game.sound.probably" );
		m_pSoundList->addItem( "more.better.game.sound" );
	}

	// Sound Name
	auto pSoundNameLabel = new QLabel( tr( "Sound Name:" ), this );
	m_pSoundNameEdit = new QLineEdit( this );

	// Sound File
	auto pSoundFileLabel = new QLabel( tr( "Sound File:" ), this );
	m_pSoundFileEdit = new QLineEdit( this );
	m_pSoundFileEdit->setEnabled( false );

	// Source File
	auto pSourceFileLabel = new QLabel( tr( "Source File:" ), this );
	m_pSourceFileEdit = new QLineEdit( this );
	m_pSourceFileEdit->setEnabled( false );

	// Sound Type
	auto pSoundTypeLabel = new QLabel( tr( "Sound Type:" ), this );
	m_pSoundType = new QComboBox( this );
	m_pSoundType->addItem( "Game Sounds" );
	m_pSoundType->addItem( "Scenes" );
	m_pSoundType->addItem( "Raw" );

	// Filter
	auto pFilterLabel = new QLabel( tr( "Filter:" ), this );
	m_pFilter = new QLineEdit( this );

	// Buttons & Checkboxes
	m_pAutoplaySounds = new QCheckBox( tr( "Autoplay Sounds" ), this );
	auto pOkButton = new QPushButton( tr( "Ok" ), this );
	auto pPreviewButton = new QPushButton( tr( "Preview" ), this );
	auto pStopButton = new QPushButton( tr( "Stop" ), this );
	auto pCancelButton = new QPushButton( tr( "Cancel" ), this );
	auto pOpenSourceButton = new QPushButton( tr( "Open Source" ), this );
	auto pRefreshSoundsButton = new QPushButton( tr( "Refresh Sounds" ), this );

	int row = 2;

	//2
	pDialogLayout->addWidget( pSoundNameLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pSoundNameEdit, row, 1, 1, 3 );
	row++;

	//3
	pDialogLayout->addWidget( pSoundFileLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pSoundFileEdit, row, 1, 1, 3 );
	row++;

	//4
	pDialogLayout->addWidget( pSourceFileLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pSourceFileEdit, row, 1, 1, 3 );
	row++;

	//5
	pDialogLayout->addWidget( pSoundTypeLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pSoundType, row, 1, 1, 3 );
	row++;

	//6
	pDialogLayout->addWidget( pFilterLabel, row, 0, Qt::AlignRight );
	pDialogLayout->addWidget( m_pFilter, row, 1, 1, 3 );
	row++;

	//7
	pDialogLayout->addWidget( m_pAutoplaySounds, row, 1, 1, 2, Qt::AlignCenter );
	row++;

	//8
	pDialogLayout->addWidget( pOkButton, row, 0 );
	pDialogLayout->addWidget( pPreviewButton, row, 1 );
	pDialogLayout->addWidget( pStopButton, row, 2 );
	row++;

	//9
	pDialogLayout->addWidget( pCancelButton, row, 0 );
	pDialogLayout->addWidget( pOpenSourceButton, row, 1 );
	pDialogLayout->addWidget( pRefreshSoundsButton, row, 3 );

	// Connections
	connect( pOkButton, &QPushButton::released, this, &CSoundBrowser::onOkPressed );
	connect( pPreviewButton, &QPushButton::released, this, &CSoundBrowser::onPreviewPresed );
	connect( pStopButton, &QPushButton::released, this, &CSoundBrowser::onStopPressed );
	connect( pCancelButton, &QPushButton::released, this, &CSoundBrowser::onCancelPressed );
	connect( pOpenSourceButton, &QPushButton::released, this, &CSoundBrowser::onOpenSourcePressed );
	connect( pRefreshSoundsButton, &QPushButton::released, this, &CSoundBrowser::onRefreshSoundsPressed );

	this->setLayout( pDialogLayout );
	this->setFixedSize( this->sizeHint() );
}

void CSoundBrowser::onOkPressed()
{
	// QT_TODO: hammer integration
}

void CSoundBrowser::onPreviewPresed()
{
	// QT_TODO: hammer integration
}

void CSoundBrowser::onStopPressed()
{
	// QT_TODO: hammer integration
}

void CSoundBrowser::onCancelPressed()
{
	this->close();
}

void CSoundBrowser::onOpenSourcePressed()
{
	// QT_TODO: hammer integration
}

void CSoundBrowser::onRefreshSoundsPressed()
{
	// QT_TODO: hammer integration
}