#include "dialogs/ActionsBar.h"

#include <QLabel>
#include <QPainter>
#include <QStyleOptionButton>
#include <QDebug>

using namespace ui;

void print_message()
{
	qDebug() << "Some words!";
}

CActionsBarDialog::CActionsBarDialog( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( "Actions Bar Example" );

	auto pDialogLayout = new QHBoxLayout();

	m_pVActionsBar = new CVActionsBar( this );
	m_pVActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );
	m_pVActionsBar->addSeparator();
	m_pVActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );

	m_pHActionsBar = new CHActionsBar( this );
	m_pHActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );
	m_pHActionsBar->addSeparator();
	m_pHActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", true, &print_message );

	pDialogLayout->addWidget( m_pVActionsBar );
	pDialogLayout->addWidget( m_pHActionsBar );

	this->setLayout( pDialogLayout );
	this->setMinimumSize( this->sizeHint() );
}

//-----------------------------------------------------------------------------------------//

CActionsBar::CActionsBar( QWidget *pParent ) :
	QWidget( pParent )
{

}

CActionBarButton *CActionsBar::addButton( const QString &pIconPath, const QString &pToolTip, const bool bCheckable, const std::function<void()> &func )
{
	if ( !m_pDialogLayout )
		return NULL;

	auto pButton = new CActionBarButton( this );
	pButton->setIcon( QIcon( QPixmap( pIconPath ) ) );
	pButton->setIconSize( QSize( 32, 32 ) );

	pButton->setCheckable( bCheckable );

	pButton->setToolTip( pToolTip );
	pButton->setFixedHeight( 64 );
	pButton->setFixedWidth( 64 );

	m_pDialogLayout->addWidget( pButton );

	connect( pButton, &QPushButton::released, this, func );

	return pButton;
}

void CActionsBar::addSeparator()
{
	if ( !m_pDialogLayout )
		return;

	auto pSepLine = new QFrame( this );

	// Set the sep bar shape
	if ( m_pDialogLayout->direction() == QBoxLayout::LeftToRight ||
		m_pDialogLayout->direction() == QBoxLayout::RightToLeft )
		pSepLine->setFrameShape( QFrame::VLine );
	else
		pSepLine->setFrameShape( QFrame::HLine );

	pSepLine->setFrameShadow( QFrame::Raised );
	m_pDialogLayout->addWidget( pSepLine );
}

//-----------------------------------------------------------------------------------------//

CActionBarButton::CActionBarButton( QWidget *pParent ) :
	QPushButton( pParent )
{

}

void CActionBarButton::paintEvent( QPaintEvent *pe )
{
	// TODO: Get rid of the background for the button

	QPushButton::paintEvent( pe );
}

//-----------------------------------------------------------------------------------------//

CHActionsBar::CHActionsBar( QWidget *pParent ) :
	CActionsBar( pParent )
{
	m_pDialogLayout = new QHBoxLayout( this );
}

//-----------------------------------------------------------------------------------------//

CVActionsBar::CVActionsBar( QWidget *pParent ) :
	CActionsBar( pParent )
{
	m_pDialogLayout = new QVBoxLayout( this );
}
