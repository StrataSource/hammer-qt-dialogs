#include "dialogs/CheckForProblems.h"

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace ui;

CCheckForProblems::CCheckForProblems( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Check map for problems" ) );

	auto pDialogLayout = new QVBoxLayout( this );

	// Problems found list
	auto pProblemsFoundTitle = new QLabel( tr( "Problems Found:" ), this );
	auto pProblemsFoundList = new QListWidget( this );

	pDialogLayout->addWidget( pProblemsFoundTitle );
	pDialogLayout->addWidget( pProblemsFoundList, 75 );

	// Visible Check
	auto pCheckVisiblePartsCheck = new QCheckBox( tr( "Check visible parts of the map only" ), this );

	pDialogLayout->addWidget( pCheckVisiblePartsCheck, 0, Qt::AlignHCenter );

	// Description
	auto pDescriptionLayout = new QGridLayout( this );

	// Description text
	auto pDescriptionText = new QPlainTextEdit( this );
	pDescriptionText->setReadOnly( true );

	pDescriptionLayout->addWidget( pDescriptionText, 0, 0 );

	// Buttons
	auto pCloseButtonBox = new QDialogButtonBox( Qt::Orientation::Vertical, this ); // Created here to force focus
	auto pCloseButton = pCloseButtonBox->addButton( QDialogButtonBox::Close );

	auto pButtonBox = new QDialogButtonBox( Qt::Orientation::Vertical, this );
	auto pGoToButton = pButtonBox->addButton( tr( "&Go to error" ), QDialogButtonBox::ButtonRole::ActionRole );
	auto pFixButton = pButtonBox->addButton( tr( "&Fix" ), QDialogButtonBox::ButtonRole::ActionRole );
	auto pFixAllButton = pButtonBox->addButton( tr( "Fix &all (of type)" ), QDialogButtonBox::ButtonRole::ActionRole );

	int buttonWidth = pButtonBox->sizeHint().width() + 20; // Pad buttons so centering doesn't act strange
	pButtonBox->setFixedWidth( buttonWidth );
	pCloseButtonBox->setFixedWidth( buttonWidth );

	pDescriptionLayout->addWidget( pButtonBox, 0, 1 );

	auto pDescriptionGroup = new QGroupBox( tr( "Description" ), this );
	pDescriptionGroup->setLayout( pDescriptionLayout );

	pDialogLayout->addWidget( pDescriptionGroup, 25 );

	pDialogLayout->addWidget( pCloseButtonBox, 0, Qt::AlignRight );

	connect( pGoToButton, &QPushButton::released, this, &CCheckForProblems::onGoToPressed );
	connect( pFixButton, &QPushButton::released, this, &CCheckForProblems::onFixPressed );
	connect( pFixAllButton, &QPushButton::released, this, &CCheckForProblems::onFixAllTypePressed );
	connect( pCloseButton, &QPushButton::released, this, &CCheckForProblems::onClosePressed );

	this->setLayout( pDialogLayout );

	// QT_TODO: Backend hammer integration

	for ( int i = 0; i < 200; i++ )
	{
		pProblemsFoundList->addItem( "There is no player start." );
		pProblemsFoundList->addItem( "Another error." );
	}

	pDescriptionText->setPlainText(
		"The entity has one or more I/O connections that are invalid, "
		"target a nonexistent entity, or connect to invalid inputs in "
		"the target entity. Fixing this error deletes the bad connections." );

	this->setMinimumSize( this->sizeHint() );
}

void CCheckForProblems::onGoToPressed()
{
	this->close();

	// QT_TODO: Go to the selected problem
}

void CCheckForProblems::onFixPressed()
{
	this->close();

	// QT_TODO: Fix the selected problem
}

void CCheckForProblems::onFixAllTypePressed()
{
	this->close();

	// QT_TODO: Fix all problems of the same type as the selected problem
}

void CCheckForProblems::onClosePressed()
{
	this->close();
}