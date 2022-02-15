#include "dialogs/RightHandUtils.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

using namespace ui;

CRightHandUtils::CRightHandUtils( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( "Right Hand Utils Example" );

	auto pDialogLayout = new QVBoxLayout();

	auto pSelect = new CSelectWidget( this );
	auto pTextureGroup = new CTextureGroupWidget( this );

	pDialogLayout->addWidget( pSelect );
	pDialogLayout->addSpacing( 5 );
	pDialogLayout->addWidget( pSelect );

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

	pWidgetLayout->addWidget( pHeader );

	this->setLayout( pWidgetLayout );
	this->setMinimumSize( this->sizeHint() );
}