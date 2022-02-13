#include "dialogs/ActionsBar.h"

#include <QLabel>
#include <QDebug>


using namespace ui;

void print_message()
{
	qDebug() << "Some words!";
}

CActionsBar::CActionsBar( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( "Action Bar" );

	m_pDialogLayout = new QHBoxLayout();

	this->addAction( ":/zoo_textures/128x128.png", &print_message );
	this->addAction( ":/zoo_textures/128x128.png", &print_message );
	this->addSeparator();
	this->addAction( ":/zoo_textures/128x128.png", &print_message );
	this->addAction( ":/zoo_textures/128x128.png", &print_message );

	this->setLayout( m_pDialogLayout );
	this->setMinimumSize( this->sizeHint() );
}

void CActionsBar::addAction( const QString &pIconPath, const std::function<void()> &func )
{
	auto pButton = new QPushButton( this );
	pButton->setIcon( QIcon( QPixmap( pIconPath ) ) );
	pButton->setIconSize( QSize( 32, 32 ) );
	pButton->setFlat( true );
	pButton->setFixedHeight( 64 );
	pButton->setFixedWidth( 64 );

	m_pDialogLayout->addWidget( pButton );

	connect( pButton, &QPushButton::released, this, func );
}

void CActionsBar::addSeparator()
{
	auto pSepLine = new QFrame();
	pSepLine->setFrameShape( QFrame::VLine );
	pSepLine->setFrameShadow( QFrame::Raised );
	m_pDialogLayout->addWidget( pSepLine );
}