#include "dialogs/EditVisgroups.h"

#include <QPushButton>
#include <QLabel>
#include <QHboxLayout>
#include <QVboxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QStyleFactory>
#include <QHeaderView>

using namespace ui;

CEditVisgroups::CEditVisgroups( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Edit Visgroups" ) );

	auto pDialogLayout = new QGridLayout( this );

	auto pGroupsLabel = new QLabel( tr( "Groups:" ), this );
	m_pVisgroupTree = new QTreeWidget( this );
	m_pVisgroupTree->setStyle( QStyleFactory::create( "Windows" ) );
	m_pVisgroupTree->setHeaderHidden( true );

	// We do this to allow the tree to be scrolled horizontally.. I wish it was easier
	m_pVisgroupTree->header()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
	m_pVisgroupTree->header()->setStretchLastSection( false ); 

	// Add junk to the tree for demo
	for ( int i = 0; i < 5; i++ )
	{
		auto pTreeItem = new QTreeWidgetItem();
		pTreeItem->setText( 0, "Visgroup " + QString::number( i ) );

		for ( int i = 0; i < 5; i++ )
		{
			auto pSubTreeItem = new QTreeWidgetItem();
			pSubTreeItem->setText( 0, "Sub Visgroup " + QString::number( i ) );

			pTreeItem->addChild( pSubTreeItem );
		}
		m_pVisgroupTree->insertTopLevelItem( i, pTreeItem );
	}
	m_pVisgroupTree->expandAll();

	// Select the first index from the tree
	m_pVisgroupTree->topLevelItem( 0 )->setSelected( true );

	// QT_TODO: Hammer integration, you'll have to handle the code for the visgroup tree

	// Selected Group box
	auto pSelGroupBox = new QGroupBox( tr( "Selected Group" ), this );
	auto pGroupLayout = new QGridLayout( pSelGroupBox );
	pGroupLayout->setAlignment( Qt::AlignTop );

	auto pNameLayout = new QHBoxLayout( this );
	auto pNameLabel = new QLabel( tr( "Name:" ), this );
	m_pVisgroupNameBox = new QLineEdit( this );	
	pNameLayout->addWidget( pNameLabel );
	pNameLayout->addWidget( m_pVisgroupNameBox, 0, Qt::AlignLeft );

	m_pColorFrame = new QFrame( this );
	m_pColorFrame->setFrameShadow( QFrame::Shadow::Sunken );
	m_pColorFrame->setFrameShape( QFrame::Shape::Panel );
	setColorFrameColor( 255, 0, 0 );

	auto pColorButton = new QPushButton( tr( "Color..." ), this );
	auto pRemoveButton = new QPushButton( tr( "Remove" ), this );

	// Add components to group box layout
	int row = 0;
	pGroupLayout->addLayout( pNameLayout, row, 0, 1, 2 );
	row++;

	//1
	pGroupLayout->addWidget( pColorButton, row, 0 );
	pGroupLayout->addWidget( m_pColorFrame, row, 1 );
	row++;

	//2
	pGroupLayout->addWidget( pRemoveButton, row, 0 );

	// Buttons
	auto pNewGroupButton = new QPushButton( tr( "New Group" ), this );
	auto pPurgeEmptyButton = new QPushButton( tr( "Purge Empty Visgroups" ), this );
	auto pCloseButton = new QPushButton( tr( "Close" ), this );

	auto pButtonLayout = new QHBoxLayout( this );
	pButtonLayout->addWidget( pNewGroupButton );
	pButtonLayout->addWidget( pPurgeEmptyButton );
	pButtonLayout->addWidget( pCloseButton, 0, Qt::AlignRight );

	// Add components to layout
	row = 0;
	pDialogLayout->addWidget( pGroupsLabel, row, 0 );
	row++;

	// 1
	pDialogLayout->addWidget( m_pVisgroupTree, row, 0, 5, 2 );
	pDialogLayout->addWidget( pSelGroupBox, row, 2, 5, 2 );

	//6
	row = 6;
	pDialogLayout->addWidget( pNewGroupButton, row, 0, 1, 1 );
	pDialogLayout->addWidget( pPurgeEmptyButton, row, 1 );
	pDialogLayout->addWidget( pCloseButton, row, 3 );

	this->setLayout( pDialogLayout );

	// Setup actions
	connect( pNewGroupButton, &QPushButton::released, this, &CEditVisgroups::onNewGroupPressed );
	connect( pPurgeEmptyButton, &QPushButton::released, this, &CEditVisgroups::onPurgeEmptyPressed );
	connect( pCloseButton, &QPushButton::released, this, &CEditVisgroups::onClosePressed );
	connect( pColorButton, &QPushButton::released, this, &CEditVisgroups::onColorPressed );
	connect( pRemoveButton, &QPushButton::released, this, &CEditVisgroups::onRemovePressed );

	this->setFixedSize( this->sizeHint() );
}

void CEditVisgroups::setColorFrameColor( int r, int g, int b )
{
	if ( m_pColorFrame == nullptr )
		return;

	m_pColorFrame->setStyleSheet( "background-color: rgb(" + QString::number( r ) + "," + QString::number( g ) + "," + QString::number( b ) + ")" );
}

void CEditVisgroups::onNewGroupPressed()
{
	// QT_TODO: Hammer integration
}

void CEditVisgroups::onPurgeEmptyPressed()
{
	// QT_TODO: Hammer integration
}

void CEditVisgroups::onClosePressed()
{
	this->close();
}

void CEditVisgroups::onColorPressed()
{
	// QT_TODO: Hammer integration
}

void CEditVisgroups::onRemovePressed()
{
	// QT_TODO: Hammer integration
}