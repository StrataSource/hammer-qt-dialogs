#include "dialogs/EntityReport.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox.h>
#include <QRadioButton.h>
#include <QCheckBox.h>

using namespace ui;

CEntityReport::CEntityReport( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle(tr("Entity Report"));

	auto pDialogLayout = new QGridLayout(this);
	pDialogLayout->setAlignment(Qt::AlignLeft);

	// Entities list
	auto pEntityListTitle = new QLabel(tr("Entities:"), this);
	auto pEntityList = new QListWidget(this);

	// Filter
	auto pFilterLayout = new QGridLayout(this);

	// Left side
	m_pFilterModeRadioGroup = new QButtonGroup(this);

	auto pFilterEverything = new QRadioButton(tr("Everything"), this);
	auto pFilterBrushEnts = new QRadioButton(tr("Brush entities"), this);
	auto pFilterPointEnts = new QRadioButton(tr("Point entities"), this);

	m_pFilterModeRadioGroup->addButton(pFilterEverything,	FilterMode::EVERYTHING);
	m_pFilterModeRadioGroup->addButton(pFilterBrushEnts,	FilterMode::BRUSH_ENTS);
	m_pFilterModeRadioGroup->addButton(pFilterPointEnts,	FilterMode::POINT_ENTS);

	m_pFilterIncludeHiddenCheck = new QCheckBox(tr("Include hidden objects"), this);

	// Right side
	m_pFilterByKVCheck = new QCheckBox(tr("By key/value:"), this); 
	m_pFilterKVExactCheck = new QCheckBox(tr("Exact"), this);

	connect(m_pFilterByKVCheck, SIGNAL(toggled(bool)), m_pFilterKVExactCheck, SLOT(setEnabled(bool)));

	m_pFilterKey = new QLineEdit(this);
	auto pFilterKVEquals = new QLabel(tr("="), this);
	m_pFilterVal = new QLineEdit(this);

	connect(m_pFilterByKVCheck, SIGNAL(toggled(bool)), m_pFilterKey, SLOT(setEnabled(bool)));
	connect(m_pFilterByKVCheck, SIGNAL(toggled(bool)), m_pFilterVal, SLOT(setEnabled(bool)));

	m_pFilterByClassCheck = new QCheckBox(tr("By class:"), this);

	auto pClassNameCombo = new QComboBox(this);
	pClassNameCombo->setEditable(true);

	connect(m_pFilterByClassCheck, SIGNAL(toggled(bool)), pClassNameCombo, SLOT(setEnabled(bool)));

	// Add row by row
	int filterRow = 0;
	pFilterLayout->addWidget(pFilterEverything,		filterRow, 0);
	pFilterLayout->addWidget(m_pFilterByKVCheck,	filterRow, 1);
	pFilterLayout->addWidget(m_pFilterKVExactCheck, filterRow, 3);
	filterRow++;

	pFilterLayout->addWidget(pFilterBrushEnts,	filterRow, 0);
	pFilterLayout->addWidget(m_pFilterKey,		filterRow, 1);
	pFilterLayout->addWidget(pFilterKVEquals,	filterRow, 2);
	pFilterLayout->addWidget(m_pFilterVal,		filterRow, 3);
	filterRow++;

	pFilterLayout->addWidget(pFilterPointEnts,		filterRow, 0);
	pFilterLayout->addWidget(m_pFilterByClassCheck, filterRow, 1);
	filterRow++;

	pFilterLayout->addWidget(m_pFilterIncludeHiddenCheck,	filterRow, 0);
	pFilterLayout->addWidget(pClassNameCombo,				filterRow, 1, 1, 3);

	auto pFilterGroup = new QGroupBox(tr("Filter"), this);
	pFilterGroup->setLayout(pFilterLayout);

	pDialogLayout->addWidget(pEntityListTitle,	0, 0);
	pDialogLayout->addWidget(pEntityList,		1, 0);
	pDialogLayout->addWidget(pFilterGroup,		2, 0);

	// Buttons
	auto pButtonBox = new QDialogButtonBox(Qt::Orientation::Vertical, this);
	auto pGoToButton = pButtonBox->addButton(tr("&Go to"), QDialogButtonBox::ButtonRole::ActionRole);
	auto pDeleteButton = pButtonBox->addButton(tr("&Delete"), QDialogButtonBox::ButtonRole::ActionRole);
	auto pPropertiesButton = pButtonBox->addButton(tr("&Properties"), QDialogButtonBox::ButtonRole::ActionRole);

	auto pCloseButtonBox = new QDialogButtonBox(Qt::Orientation::Vertical, this);
	auto pCloseButton = pCloseButtonBox->addButton(QDialogButtonBox::Close);

	pDialogLayout->addWidget(pButtonBox,		1, 1);
	pDialogLayout->addWidget(pCloseButtonBox,	2, 1, Qt::AlignBottom);

	this->setLayout(pDialogLayout);

	connect( pGoToButton, &QPushButton::released, this, &CEntityReport::onGoToPressed );
	connect( pDeleteButton, &QPushButton::released, this, &CEntityReport::onDeletePressed );
	connect( pPropertiesButton, &QPushButton::released, this, &CEntityReport::onPropertiesPressed );
	connect( pCloseButton, &QPushButton::released, this, &CEntityReport::onClosePressed );

	// QT_TODO: Backend hammer integration

	for ( int i = 0; i < 200; i++ )
	{
		pEntityList->addItem( "func_brush" );
		pEntityList->addItem( "info_player_start" );
	}

	pClassNameCombo->addItem( "func_brush" );
	pClassNameCombo->addItem( "info_player_start" );

	pClassNameCombo->setCurrentIndex(-1);

	m_pFilterModeRadioGroup->button(FilterMode::EVERYTHING)->setChecked(true);
	m_pFilterIncludeHiddenCheck->setChecked(false);

	m_pFilterByKVCheck->setChecked(false);

	m_pFilterKVExactCheck->setChecked(false);
	m_pFilterKVExactCheck->setEnabled(false);

	m_pFilterKey->setEnabled(false);
	m_pFilterVal->setEnabled(false);

	m_pFilterByClassCheck->setChecked(false);
	pClassNameCombo->setEnabled(false);
}

void CEntityReport::onGoToPressed()
{
	this->close();
	
	//QT_TODO: Go to the selected entity
}

void CEntityReport::onDeletePressed()
{
	this->close();
	
	//QT_TODO: Delete the selected entity
}

void CEntityReport::onPropertiesPressed()
{
	this->close();
	
	//QT_TODO: Open the properties of the selected entity
}

void CEntityReport::onClosePressed()
{
	this->close();
}