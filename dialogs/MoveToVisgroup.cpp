#include "dialogs/MoveToVisgroup.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStyleFactory>

using namespace ui;

CMoveToVisgroup::CMoveToVisgroup( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Move To Visgroup" ) );

	auto pDialogLayout = new QVBoxLayout( this );

	m_pPlaceInExisting = new QRadioButton( tr( "Place object in existing visgroup:" ), this );
	m_pVisgroupTree = new QTreeWidget( this );
	m_pVisgroupTree->setStyle( QStyleFactory::create( "Windows" ) );
	m_pVisgroupTree->setEnabled( false );
	m_pVisgroupTree->setHeaderHidden( true );

	// Add junk to the tree for demo
	for (int i = 0; i < 5; i++)
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

	// QT_TODO: Hammer integration, you'll have to handle the code for the visgroup tree

	m_pCreateNew = new QRadioButton( tr( "Create new visgroup:" ), this );
	m_pCreateNew->setChecked( true );
	m_pNewVisgroupName = new QLineEdit( "1 object", this );

	m_pRemoveObjects = new QCheckBox( tr( "Remove objects from all other visgroups" ), this );
	m_pHideObjects = new QCheckBox( tr( "Hide Objects" ), this );
	m_pHideObjects->setChecked( true );

	auto pButtonGroup = new QDialogButtonBox( this );
	auto pOkButton = pButtonGroup->addButton( QDialogButtonBox::Ok );
	auto pCancelButton = pButtonGroup->addButton( QDialogButtonBox::Cancel );

	// Layout code
	pDialogLayout->addWidget( m_pPlaceInExisting );
	pDialogLayout->addWidget( m_pVisgroupTree );

	auto pCreateNewLayout = new QHBoxLayout( this );
	pCreateNewLayout->addWidget( m_pCreateNew );
	pCreateNewLayout->addWidget( m_pNewVisgroupName );
	pDialogLayout->addLayout( pCreateNewLayout );

	pDialogLayout->addWidget( m_pRemoveObjects );
	pDialogLayout->addWidget( m_pHideObjects );

	pDialogLayout->addWidget( pButtonGroup, 0, Qt::AlignCenter );

	this->setLayout( pDialogLayout );

	// Actions
	connect( m_pCreateNew, SIGNAL( toggled( bool ) ), m_pNewVisgroupName, SLOT( setEnabled( bool ) ) );
	connect( m_pPlaceInExisting, SIGNAL( toggled( bool ) ), m_pVisgroupTree, SLOT( setEnabled( bool ) ) );
	connect( pOkButton, &QPushButton::released, this, &CMoveToVisgroup::onOkPressed );
	connect( pCancelButton, &QPushButton::released, this, &CMoveToVisgroup::onCancelPressed );

	this->setFixedSize( this->sizeHint() );
}

void CMoveToVisgroup::onOkPressed()
{

}

void CMoveToVisgroup::onCancelPressed()
{
	this->close();
}