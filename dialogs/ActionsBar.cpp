#include "dialogs/ActionsBar.h"

#include <QLabel>
#include <QHBoxLayout>
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

	m_pVActionsBar = new CActionsBar( this, Qt::Vertical );
	m_pVActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );
	m_pVActionsBar->addSeparator();
	m_pVActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );

	m_pHActionsBar = new CActionsBar( this );
	m_pHActionsBar->setIconSize( QSize( 128, 128 ) );
	m_pHActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", false, &print_message );
	m_pHActionsBar->addSeparator();
	m_pHActionsBar->addButton( ":/zoo_textures/64x64.png", "This is a test button", true, &print_message );

	pDialogLayout->addWidget( m_pVActionsBar );
	pDialogLayout->addWidget( m_pHActionsBar );	

	this->setLayout( pDialogLayout );
	this->setMinimumSize( this->sizeHint() );
}

//-----------------------------------------------------------------------------------------//

CActionsBar::CActionsBar( QWidget *pParent, Qt::Orientation orientation ) :
	QWidget( pParent )
{
	m_pToolBar = new QToolBar( this );
	m_pToolBar->setOrientation( orientation );
}

template <class Func>
QAction *CActionsBar::addButton( const QString &pIconPath, const QString &pToolTip, const bool bCheckable, Func func )
{
	if ( !m_pToolBar )
		return NULL;

	auto pButton = new QAction( this );
	pButton->setIcon( QIcon( QPixmap( pIconPath ) ) );
	pButton->setToolTip( pToolTip );
	pButton->setStatusTip( pToolTip );
	pButton->setCheckable( bCheckable );

	m_pToolBar->addAction( pButton );

	connect( pButton, &QAction::triggered, this, std::move(func) );

	// Return it, just in case we need a pointer to the action
	return pButton;
}

void CActionsBar::addSeparator()
{
	if ( !m_pToolBar )
		return;

	m_pToolBar->addSeparator();
}

void CActionsBar::setIconSize( const QSize &pSize )
{
	if ( !m_pToolBar )
		return;

	m_pToolBar->setIconSize( pSize );
}
