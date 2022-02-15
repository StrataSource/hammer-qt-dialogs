#include "dialogs/RightHandUtils.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>

using namespace ui;

CRightHandUtils::CRightHandUtils( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( "Right Hand Utils Example" );

	auto pDialogLayout = new QVBoxLayout();

	auto pSelect = new CSelectWidget( this );
	auto pTextureGroup = new CTextureGroupWidget( this );
	auto pVisGroups = new CVisgroupsWidget( this );

	pDialogLayout->addWidget( pSelect );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pTextureGroup );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pVisGroups );

	this->setLayout( pDialogLayout );
	this->setMinimumSize( this->sizeHint() );
}

//-----------------------------------------------------------------------------------------//

CSelectWidget::CSelectWidget( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	auto pHeader = new QLabel( tr( "Select:" ), this );

	m_pSelectGroup = new QButtonGroup( this );

	m_pGroupsButton = new QPushButton( tr( "Groups" ), this );
	m_pGroupsButton->setCheckable( true );

	m_pObjectsButton = new QPushButton( tr( "Objects" ), this );
	m_pObjectsButton->setCheckable( true );

	m_pSolidsButton = new QPushButton( tr( "Solids" ), this );
	m_pSolidsButton->setCheckable( true );

	m_pSelectGroup->addButton( m_pGroupsButton );
	m_pSelectGroup->addButton( m_pObjectsButton );
	m_pSelectGroup->addButton( m_pSolidsButton );

	pWidgetLayout->addWidget( pHeader );
	pWidgetLayout->addWidget( m_pGroupsButton );
	pWidgetLayout->addWidget( m_pObjectsButton );
	pWidgetLayout->addWidget( m_pSolidsButton );

	connect( m_pGroupsButton, &QPushButton::released, this, &CSelectWidget::onGroupsPressed );
	connect( m_pObjectsButton, &QPushButton::released, this, &CSelectWidget::onObjectsPressed );
	connect( m_pSolidsButton, &QPushButton::released, this, &CSelectWidget::onSolidsPressed );

	this->setLayout( pWidgetLayout );
	this->setMinimumSize( this->sizeHint() );
}

void CSelectWidget::onGroupsPressed()
{
	// QT_TODO
}

void CSelectWidget::onObjectsPressed()
{
	// QT_TODO
}

void CSelectWidget::onSolidsPressed()
{
	// QT_TODO
}

//-----------------------------------------------------------------------------------------//

CTextureGroupWidget::CTextureGroupWidget( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	auto pHeader = new QLabel( tr( "Texture Group:" ), this );
	auto pCurrentTextureHeader = new QLabel( tr( "Current Texture:" ), this );

	m_pModSelectorBox = new QComboBox( this );
	m_pCurrentTextureBox = new QComboBox( this );
	m_pCurrentTextureBox->setEditable( true );

	auto pTexAndButLayout = new QGridLayout();

	m_pTextureLabel = new QLabel( this );
	auto pPixMap = new QPixmap( ":/zoo_textures/128x128.png" );
	m_pTextureLabel->setPixmap( pPixMap->scaled( 80, 80 ) );

	m_pBrowseButton = new QPushButton( tr( "Browse..." ), this );
	m_pReplaceButton = new QPushButton( tr( "Replace..." ), this );
	m_pFavoriteButton = new QPushButton( tr( "Favorite" ), this );
	m_pNoDrawButton = new QPushButton( tr( "Nodraw" ), this );

	pTexAndButLayout->addWidget( m_pTextureLabel, 0, 0, Qt::AlignBottom );
	pTexAndButLayout->addWidget( m_pBrowseButton, 0, 1 );
	pTexAndButLayout->addWidget( m_pFavoriteButton, 0, 1, Qt::AlignBottom );
	pTexAndButLayout->addWidget( m_pReplaceButton, 2, 1, Qt::AlignTop );
	pTexAndButLayout->addWidget( m_pNoDrawButton, 2, 0 );

	pWidgetLayout->addWidget( pHeader );
	pWidgetLayout->addWidget( m_pModSelectorBox );
	pWidgetLayout->addWidget( pCurrentTextureHeader );
	pWidgetLayout->addWidget( m_pCurrentTextureBox );
	pWidgetLayout->addLayout( pTexAndButLayout );


	this->setLayout( pWidgetLayout );
	this->setMinimumSize( this->sizeHint() );
}

//-----------------------------------------------------------------------------------------//

CVisgroupsWidget::CVisgroupsWidget( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	auto pHeader = new QLabel( tr( "VisGroups:" ), this );

	m_pUserTree = new QTreeWidget( this );
	m_pAutoTree = new QTreeWidget( this );
	m_pCordonTree = new QTreeWidget( this );

	auto pTabWidget = new QTabWidget( this );
	pTabWidget->addTab( m_pUserTree, tr( "User" ) );
	pTabWidget->addTab( m_pAutoTree, tr( "Auto" ) );
	pTabWidget->addTab( m_pCordonTree, tr( "Cordon" ) );

	pWidgetLayout->addWidget( pHeader );
	pWidgetLayout->addWidget( pTabWidget );

	this->setLayout( pWidgetLayout );
	this->setFixedHeight( 200 );
	this->setFixedWidth( 180 );
}