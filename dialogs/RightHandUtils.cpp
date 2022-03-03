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
	auto pPrefabs = new CPrefabsWidget( this );

	pDialogLayout->addWidget( pSelect );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pTextureGroup );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pVisGroups );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pPrefabs );

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

	m_pTexSizeLabel = new QLabel( "128x128", this );
	m_pTextureLabel = new QLabel( this );
	auto pPixMap = new QPixmap( ":/zoo_textures/128x128.png" );
	m_pTextureLabel->setPixmap( pPixMap->scaled( 80, 80 ) );

	m_pBrowseButton = new QPushButton( tr( "Browse..." ), this );
	m_pReplaceButton = new QPushButton( tr( "Replace..." ), this );
	m_pFavoriteButton = new QPushButton( tr( "Favorite" ), this );
	m_pNoDrawButton = new QPushButton( tr( "Nodraw" ), this );

	// This was a pain in the ass to actually get working
	// Qt's layout system didn't like me having to add the tex size label
	pTexAndButLayout->addWidget( m_pTextureLabel, 0, 0, Qt::AlignBottom );
	pTexAndButLayout->addWidget( m_pTexSizeLabel, 0, 1, Qt::AlignTop );
	pTexAndButLayout->addWidget( m_pBrowseButton, 0, 1 );
	pTexAndButLayout->addWidget( m_pReplaceButton, 0, 1, Qt::AlignBottom );
	pTexAndButLayout->addWidget( m_pFavoriteButton, 2, 1, Qt::AlignTop );
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

	auto pButtonLayout = new QHBoxLayout();
	m_pShowButton = new QPushButton( tr( "Show" ), this );
	m_pEditButton = new QPushButton( tr( "Edit" ), this );
	m_pMarkButton = new QPushButton( tr( "Mark" ), this );
	m_pUpButton = new QPushButton( "e", this );
	m_pDownButton = new QPushButton( "e", this );

	// Sets the buttons to an okay size
	m_pShowButton->setMaximumHeight( 20 );
	m_pEditButton->setMaximumHeight( 20 );
	m_pMarkButton->setMaximumHeight( 20 );
	m_pUpButton->setMaximumSize( 20, 20 );
	m_pDownButton->setMaximumSize( 20, 20 );

	pButtonLayout->setSpacing( 1 );
	pButtonLayout->addWidget( m_pShowButton );
	pButtonLayout->addWidget( m_pEditButton );
	pButtonLayout->addWidget( m_pMarkButton );
	pButtonLayout->addWidget( m_pUpButton );
	pButtonLayout->addWidget( m_pDownButton );

	pWidgetLayout->addWidget( pHeader );
	pWidgetLayout->addWidget( pTabWidget );
	pWidgetLayout->addLayout( pButtonLayout );

	connect( m_pShowButton, &QPushButton::released, this, &CVisgroupsWidget::onShowPressed );
	connect( m_pEditButton, &QPushButton::released, this, &CVisgroupsWidget::onEditPressed );
	connect( m_pMarkButton, &QPushButton::released, this, &CVisgroupsWidget::onMarkPressed );
	connect( m_pUpButton, &QPushButton::released, this, &CVisgroupsWidget::onUpPressed );
	connect( m_pDownButton, &QPushButton::released, this, &CVisgroupsWidget::onDownPresed );

	this->setLayout( pWidgetLayout );
	this->setFixedHeight( 200 );
	this->setFixedWidth( 180 );
}

void CVisgroupsWidget::onShowPressed()
{
	// QT_TODO
}

void CVisgroupsWidget::onEditPressed()
{
	// QT_TODO
}

void CVisgroupsWidget::onMarkPressed()
{
	// QT_TODO
}

void CVisgroupsWidget::onUpPressed()
{
	// QT_TODO
}

void CVisgroupsWidget::onDownPresed()
{
	// QT_TODO
}

//-----------------------------------------------------------------------------------------//

CPrefabsWidget::CPrefabsWidget( QWidget *pParent ) :
	QWidget( pParent )
{
	auto pWidgetLayout = new QVBoxLayout();

	auto pMoveLayout = new QHBoxLayout();
	auto pMoveSelLabel = new QLabel( tr( "Move\nSelected:" ), this );
	m_pToWorldButton = new QPushButton( tr( "toWorld" ), this );
	m_pToEntityButton = new QPushButton( tr( "toEntity" ), this );

	pMoveLayout->addWidget( pMoveSelLabel );
	pMoveLayout->addWidget( m_pToWorldButton );
	pMoveLayout->addWidget( m_pToEntityButton );

	auto pCatLabel = new QLabel( tr( "Categories:" ), this );
	m_pCategoriesBox = new QComboBox( this );
	auto pObjLabel = new QLabel( tr( "Objects:" ), this );
	m_pObjectsBox = new QComboBox( this );
	m_pObjectsBox->setEditable( true );

	m_pFacesBox = new QSpinBox( this );
	m_pFacesBox->setMaximum( INT_MAX );
	m_pFacesBox->setMaximumWidth( 50 );

	m_pCreateButton = new QPushButton( tr( "Create Prefab" ), this );

	pWidgetLayout->addLayout( pMoveLayout );
	pWidgetLayout->addWidget( pCatLabel );
	pWidgetLayout->addWidget( m_pCategoriesBox );
	pWidgetLayout->addWidget( pObjLabel );
	pWidgetLayout->addWidget( m_pObjectsBox );
	pWidgetLayout->addWidget( m_pFacesBox, 0, Qt::AlignCenter );
	pWidgetLayout->addWidget( m_pCreateButton );

	connect( m_pToWorldButton, &QPushButton::released, this, &CPrefabsWidget::onToWorldPressed );
	connect( m_pToEntityButton, &QPushButton::released, this, &CPrefabsWidget::onToEntityPressed );
	connect( m_pCreateButton, &QPushButton::released, this, &CPrefabsWidget::onCreatePrefabPressed );

	this->setLayout( pWidgetLayout );
	this->setFixedWidth( 180 );
	//this->setFixedSize( this->sizeHint() );
}

void CPrefabsWidget::onToWorldPressed()
{
	// QT_TODO
}

void CPrefabsWidget::onToEntityPressed()
{
	// QT_TODO
}

void CPrefabsWidget::onCreatePrefabPressed()
{
	// QT_TODO
}