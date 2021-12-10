#include "PasteSpecial.h"

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

using namespace ui;

CPasteSpecial::CPasteSpecial( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Paste Special" ) );
	this->setMinimumSize( this->sizeHint() );

	auto pDialogLayout = new QGridLayout( this );
	pDialogLayout->setAlignment( Qt::AlignLeft | Qt::AlignTop );
	int row = 0;

	// Copy count
	auto pCopyCountLabel = new QLabel( this );
	pCopyCountLabel->setText( tr( "Number of copies to paste:" ) );
	pDialogLayout->addWidget( pCopyCountLabel, row, 0 );

	m_pCopyCount = new QLineEdit( this );
	m_pCopyCount->setValidator( new QIntValidator( 1, 4096, m_pCopyCount ) );
	m_pCopyCount->setText( "1" );
	pDialogLayout->addWidget( m_pCopyCount, row, 1 );
	row++;

	// Position and group properties
	m_pStartAtCenterCheckbox = new QCheckBox( this );
	m_pGroupCopiesCheckbox = new QCheckBox( this );
	m_pStartAtCenterCheckbox->setText( tr( "Start at center of original" ) );
	m_pGroupCopiesCheckbox->setText( tr( "Group copies" ) );
	pDialogLayout->addWidget( m_pStartAtCenterCheckbox, row++, 0 );
	pDialogLayout->addWidget( m_pGroupCopiesCheckbox, row++, 0 );

	// Space movers

	// Offset
	auto pOffsetGroup = new QGroupBox( tr( "Offset (accumulative):" ) );
	auto pOffsetLayout = new QGridLayout( pOffsetGroup );

	// Offset Components
	int orow = 0;

	auto pOffsetXLabel = new QLabel( this );
	m_pOffsetX = new QLineEdit( this );
	auto pOffsetXFetch = new QPushButton( this );
	pOffsetXLabel->setText( "X:" );
	m_pOffsetX->setValidator( new QDoubleValidator( m_pOffsetX ) );
	m_pOffsetX->setText( "0" );
	pOffsetXFetch->setText( "<" );
	pOffsetLayout->addWidget( pOffsetXLabel, orow, 0 );
	pOffsetLayout->addWidget( m_pOffsetX, orow, 1 );
	pOffsetLayout->addWidget( pOffsetXFetch, orow, 2 );
	orow++;

	auto pOffsetYLabel = new QLabel( this );
	m_pOffsetY = new QLineEdit( this );
	auto pOffsetYFetch = new QPushButton( this );
	pOffsetYLabel->setText( "Y:" );
	m_pOffsetY->setValidator( new QDoubleValidator( m_pOffsetY ) );
	m_pOffsetY->setText( "0" );
	pOffsetYFetch->setText( "<" );
	pOffsetLayout->addWidget( pOffsetYLabel, orow, 0 );
	pOffsetLayout->addWidget( m_pOffsetY, orow, 1 );
	pOffsetLayout->addWidget( pOffsetYFetch, orow, 2 );
	orow++;

	auto pOffsetZLabel = new QLabel( this );
	m_pOffsetZ = new QLineEdit( this );
	auto pOffsetZFetch = new QPushButton( this );
	pOffsetZLabel->setText( "Z:" );
	m_pOffsetZ->setValidator( new QDoubleValidator( m_pOffsetZ ) );
	m_pOffsetZ->setText( "0" );
	pOffsetZFetch->setText( "<" );
	pOffsetLayout->addWidget( pOffsetZLabel, orow, 0 );
	pOffsetLayout->addWidget( m_pOffsetZ, orow, 1 );
	pOffsetLayout->addWidget( pOffsetZFetch, orow, 2 );
	orow++;

	// Rotation
	auto pRotationGroup = new QGroupBox( tr( "Rotation (accumulative):" ) );
	auto pRotationLayout = new QGridLayout( pRotationGroup );

	// Rotation Components
	orow = 0;

	auto pRotationXLabel = new QLabel( this );
	m_pRotationX = new QLineEdit( this );
	pRotationXLabel->setText( "X:" );
	m_pRotationX->setValidator( new QDoubleValidator( m_pRotationX ) );
	m_pRotationX->setText( "0" );
	pRotationLayout->addWidget( pRotationXLabel, orow, 0 );
	pRotationLayout->addWidget( m_pRotationX, orow, 1 );
	orow++;

	auto pRotationYLabel = new QLabel( this );
	m_pRotationY = new QLineEdit( this );
	pRotationYLabel->setText( "Y:" );
	m_pRotationY->setValidator( new QDoubleValidator( m_pRotationY ) );
	m_pRotationY->setText( "0" );
	pRotationLayout->addWidget( pRotationYLabel, orow, 0 );
	pRotationLayout->addWidget( m_pRotationY, orow, 1 );
	orow++;

	auto pRotationZLabel = new QLabel( this );
	m_pRotationZ = new QLineEdit( this );
	pRotationZLabel->setText( "Z:" );
	m_pRotationZ->setValidator( new QDoubleValidator( m_pRotationZ ) );
	m_pRotationZ->setText( "0" );
	pRotationLayout->addWidget( pRotationZLabel, orow, 0 );
	pRotationLayout->addWidget( m_pRotationZ, orow, 1 );
	orow++;

	pDialogLayout->addWidget( pOffsetGroup, row, 0 );
	pDialogLayout->addWidget( pRotationGroup, row, 1 );

	row++;

	// Name properties
	m_pUniqueNamesCheckbox = new QCheckBox( this );
	m_pUniqueNamesCheckbox->setText( tr( "Make pasted entity names unique" ) );
	pDialogLayout->addWidget( m_pUniqueNamesCheckbox, row++, 0 );

	m_pAddPrefixCheckbox = new QCheckBox( this );
	m_pNamePrefix = new QLineEdit( this );
	m_pAddPrefixCheckbox->setText( tr( "Add this prefix to all named entities:" ) );
	m_pNamePrefix->setEnabled( m_pAddPrefixCheckbox->isChecked() );
	pDialogLayout->addWidget( m_pAddPrefixCheckbox, row, 0 );
	pDialogLayout->addWidget( m_pNamePrefix, row, 1 );
	row++;

	// Close
	auto pButtonBox = new QDialogButtonBox();
	auto pOkButton = pButtonBox->addButton( QDialogButtonBox::Ok );
	auto pCancelButton = pButtonBox->addButton( QDialogButtonBox::Cancel );

	pDialogLayout->addWidget( pButtonBox, row, 1, Qt::AlignRight );

	this->setLayout( pDialogLayout );

	// Wiring

	// Only enable the prefix line edit if our checkbox is on
	connect( m_pAddPrefixCheckbox, SIGNAL( toggled( bool ) ), m_pNamePrefix, SLOT( setEnabled( bool ) ) );

	// Fetch x/y/z
	connect( pOffsetXFetch, &QPushButton::released, this, &CPasteSpecial::onFetchOffsetXPressed );
	connect( pOffsetYFetch, &QPushButton::released, this, &CPasteSpecial::onFetchOffsetYPressed );
	connect( pOffsetZFetch, &QPushButton::released, this, &CPasteSpecial::onFetchOffsetZPressed );

	connect( pOkButton, &QPushButton::released, this, &CPasteSpecial::onOkPressed );
	connect( pCancelButton, &QPushButton::released, this, &CPasteSpecial::onCancelPressed );

	// We put all of our required line edits into an array.
	// When these get edited, we check for each if it's empty,
	//   and if it is, we mark a bitflag that shows
	//   it's currently empty and make our background
	//   yellow to tell the user this field is required.
	// If that bitflag is 0, we enable our ok button,
	// 	 or if it's not 0, we disable it.
	//
	// Is there a better way to do this? If there isn't should this be generalized down for other dialogs?

	QLineEdit *requiredLineEdits[] =
		{
			m_pCopyCount,
			m_pOffsetX,
			m_pOffsetY,
			m_pOffsetZ,
			m_pRotationX,
			m_pRotationY,
			m_pRotationZ };

	for ( int i = 0; i < sizeof( requiredLineEdits ) / sizeof( QLineEdit * ); i++ )
	{
		QLineEdit *required = requiredLineEdits[i];

		connect( required, &QLineEdit::textChanged, this,
				 [=]()
				 {
					 if ( required->text().isEmpty() )
					 {
						 // Mark we lack content
						 m_readyToCopy |= 1 << i;

						 required->setStyleSheet( "background-color:yellow;" );
					 }
					 else
					 {
						 // Mark we have content
						 m_readyToCopy &= ~( 1 << i );

						 required->setStyleSheet( "" );
					 }

					 // Check if we can copy now
					 pOkButton->setEnabled( m_readyToCopy == 0 );
				 } );
	}

	// By default, all our fields are filled
	m_readyToCopy = 0;
}

void CPasteSpecial::onOkPressed()
{
	int copyCount = m_pCopyCount->text().toInt();

	float offsetX = m_pOffsetX->text().toFloat();
	float offsetY = m_pOffsetY->text().toFloat();
	float offsetZ = m_pOffsetZ->text().toFloat();

	float rotationX = m_pRotationX->text().toFloat();
	float rotationY = m_pRotationY->text().toFloat();
	float rotationZ = m_pRotationZ->text().toFloat();

	bool startAtCenter = m_pStartAtCenterCheckbox->isChecked();
	bool groupCopies = m_pGroupCopiesCheckbox->isChecked();

	bool uniqueNames = m_pUniqueNamesCheckbox->isChecked();
	bool addPrefix = m_pAddPrefixCheckbox->isChecked();
	QString namePrefix = m_pNamePrefix->text();

	// QT_TODO: Backend hammer integration
	this->close();
}

void CPasteSpecial::onCancelPressed()
{
	this->close();
}

void CPasteSpecial::onFetchOffsetXPressed()
{
	// Fetch the length of the copy on the X axis and fill in our line edit

	// QT_TODO: Backend hammer integration
	m_pOffsetX->setText( "512" );
}

void CPasteSpecial::onFetchOffsetYPressed()
{
	// Fetch the length of the copy on the Y axis and fill in our line edit

	// QT_TODO: Backend hammer integration
	m_pOffsetY->setText( "64" );
}

void CPasteSpecial::onFetchOffsetZPressed()
{
	// Fetch the length of the copy on the Z axis and fill in our line edit

	// QT_TODO: Backend hammer integration
	m_pOffsetZ->setText( "128" );
}