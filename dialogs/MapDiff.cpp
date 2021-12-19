#include "dialogs/MapDiff.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

using namespace ui;

CMapDiff::CMapDiff( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Map Diff" ) );

	auto pDialogLayout = new QGridLayout( this );

	auto pFindLayout = new QHBoxLayout( this );
	auto pFindLabel = new QLabel( tr( "Map to Diff Against " ), this );
	m_pFindName = new QLineEdit( this );

	auto pBrowseButton = new QPushButton( this );
	pBrowseButton->setText( tr( "Browse" ) );

	pFindLayout->addWidget( pFindLabel );
	pFindLayout->addWidget( m_pFindName );
	pFindLayout->addWidget( pBrowseButton );

	auto pOptionLabel = new QLabel( tr( "Diff Options" ), this );
	m_pDiffSimilarVisgroup = new QCheckBox( tr( "Place Similarities in \"Similar\" Visgroup" ), this );
	m_pDiffSimilarVisgroup->setChecked( true );

	auto pButtonBox = new QDialogButtonBox( Qt::Orientation::Horizontal, this );
	auto pOKButton = pButtonBox->addButton( QDialogButtonBox::Ok );
	auto pCloseButton = pButtonBox->addButton( QDialogButtonBox::Close );

	pDialogLayout->addLayout( pFindLayout, 0, 0, 1, 3 );
	pDialogLayout->addWidget( pOptionLabel, 1, 0 );
	pDialogLayout->addWidget( m_pDiffSimilarVisgroup, 2, 0 );
	pDialogLayout->addWidget( pButtonBox, 3, 0, Qt::AlignLeft );

	connect( pOKButton, &QPushButton::released, this, &CMapDiff::onOKPressed );
	connect( pCloseButton, &QPushButton::released, this, &CMapDiff::onClosePressed );
	connect( pBrowseButton, &QPushButton::released, this, &CMapDiff::onBrowsePressed );

	this->setLayout( pDialogLayout );
	this->setFixedSize( this->sizeHint() );
}

void CMapDiff::onOKPressed()
{
	// QT_TODO: Integrate
	this->close();
}

void CMapDiff::onBrowsePressed()
{
	// QT_TODO: Integrate
	this->close();
}

void CMapDiff::onClosePressed()
{
	// QT_TODO: Integrate
	this->close();
}
