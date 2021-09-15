#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>

#include "RunMapNormal.h"

using namespace ui;


CRunMapNormal::CRunMapNormal(QWidget* pParent) :
	QDialog(pParent)
{
	this->setWindowTitle(tr("Run Map"));

	auto pDialogLayout = new QVBoxLayout(this);

	// BSP Group
	auto pBspGroup = new QGroupBox(tr("Run BSP"));
	auto pBspLayout = new QVBoxLayout(pBspGroup);
	m_pBspRadioGroup = new QButtonGroup(this);

	auto pBspNo = new QRadioButton(tr("No"), this);
	auto pBspNormal = new QRadioButton(tr("Normal"), this);
	auto pBspOnlyEntities = new QRadioButton(tr("Only entities"), this);
	pBspLayout->addWidget(pBspNo);
	pBspLayout->addWidget(pBspNormal);
	pBspLayout->addWidget(pBspOnlyEntities);
	m_pBspRadioGroup->addButton(pBspNo,           CompilerMode::NO);
	m_pBspRadioGroup->addButton(pBspNormal,       CompilerMode::NORMAL);
	m_pBspRadioGroup->addButton(pBspOnlyEntities, CompilerMode::ONLY_ENTS);

	pBspGroup->setLayout(pBspLayout);
	pDialogLayout->addWidget(pBspGroup);


	// VIS Group
	auto pVisGroup = new QGroupBox(tr("Run VIS"));
	auto pVisLayout = new QVBoxLayout(pVisGroup);
	m_pVisRadioGroup = new QButtonGroup(this);

	auto pVisNo = new QRadioButton(tr("No"), this);
	auto pVisNormal = new QRadioButton(tr("Normal"), this);
	auto pVisFast = new QRadioButton(tr("Fast"), this);
	pVisLayout->addWidget(pVisNo);
	pVisLayout->addWidget(pVisNormal);
	pVisLayout->addWidget(pVisFast);
	m_pVisRadioGroup->addButton(pVisNo,     CompilerMode::NO);
	m_pVisRadioGroup->addButton(pVisNormal, CompilerMode::NORMAL);
	m_pVisRadioGroup->addButton(pVisFast,   CompilerMode::FAST);

	pVisGroup->setLayout(pVisLayout);
	pDialogLayout->addWidget(pVisGroup);


	// RAD Group
	auto pRadGroup = new QGroupBox(tr("Run RAD"));
	auto pRadLayout = new QGridLayout(pRadGroup);
	m_pRadRadioGroup = new QButtonGroup(this);

	// Left side
	auto pRadNo = new QRadioButton(tr("No"), this);
	auto pRadNormal = new QRadioButton(tr("Normal"), this);
	auto pRadFast = new QRadioButton(tr("Fast"), this);
	pRadLayout->addWidget(pRadNo,     0, 0, Qt::AlignLeft);
	pRadLayout->addWidget(pRadNormal, 1, 0, Qt::AlignLeft);
	pRadLayout->addWidget(pRadFast,   2, 0, Qt::AlignLeft);
	m_pRadRadioGroup->addButton(pRadNo,     CompilerMode::NO);
	m_pRadRadioGroup->addButton(pRadNormal, CompilerMode::NORMAL);
	m_pRadRadioGroup->addButton(pRadFast,   CompilerMode::FAST);

	// Right side
	m_pRadHDRCheck = new QCheckBox(this);
	m_pRadHDRCheck->setCheckable(true);
	m_pRadHDRCheck->setText(tr("HDR"));
	pRadLayout->addWidget(m_pRadHDRCheck, 0, 1, Qt::AlignRight);
	
	pRadGroup->setLayout(pRadLayout);
	pDialogLayout->addWidget(pRadGroup);


	// Extras
	m_pDontRunGameCheck = new QCheckBox(this);
	m_pDontRunGameCheck->setCheckable(true);
	m_pDontRunGameCheck->setText(tr("Don't run the game after compiling"));
	pDialogLayout->addWidget(m_pDontRunGameCheck);

	m_pWaitForKeyCheck = new QCheckBox(this);
	m_pWaitForKeyCheck->setCheckable(true);
	m_pWaitForKeyCheck->setText(tr("Wait for keypress when done compiling"));
	pDialogLayout->addWidget(m_pWaitForKeyCheck);
	
	auto pGameParamLabel = new QLabel(this);
	pGameParamLabel->setText("Additional game parameters:");
	pDialogLayout->addWidget(pGameParamLabel);

	m_pGameParameters = new QLineEdit(this);
	m_pGameParameters->setText("");
	pDialogLayout->addWidget(m_pGameParameters);


	// Buttons
	auto pButtonLayout = new QHBoxLayout(this);
	
	auto pExpertButton = new QPushButton(this);
	pExpertButton->setText(tr("Expert..."));
	pButtonLayout->addWidget(pExpertButton);
	
	// We're using a button box, as the order of these buttons change from one OS to the other
	auto pButtonBox = new QDialogButtonBox();
	auto pOkButton = pButtonBox->addButton(QDialogButtonBox::Ok);
	auto pCancelButton = pButtonBox->addButton(QDialogButtonBox::Cancel);
	pButtonLayout->addWidget(pButtonBox);
	
	pDialogLayout->addLayout(pButtonLayout);


	this->setLayout(pDialogLayout);

	// Connect up buttons
	connect(pExpertButton, &QPushButton::released, this, &CRunMapNormal::onExpertPressed);
	connect(pOkButton,     &QPushButton::released, this, &CRunMapNormal::onOkPressed);
	connect(pCancelButton, &QPushButton::released, this, &CRunMapNormal::onCancelPressed);



	// QT_TODO: Retain options
	m_pBspRadioGroup->button(CompilerMode::NO)->setChecked(true);
	m_pVisRadioGroup->button(CompilerMode::NORMAL)->setChecked(true);
	m_pRadRadioGroup->button(CompilerMode::FAST)->setChecked(true);

	m_pRadHDRCheck->setChecked(true);
	m_pDontRunGameCheck->setChecked(true);
	m_pWaitForKeyCheck->setChecked(false);
	m_pGameParameters->setText("-dev");

}

void CRunMapNormal::onExpertPressed()
{
	this->close();
	
	//QT_TODO: Open the expert menu
}

void CRunMapNormal::onOkPressed()
{
	CompilerMode bspMode = (CompilerMode)m_pBspRadioGroup->checkedId();
	CompilerMode visMode = (CompilerMode)m_pVisRadioGroup->checkedId();
	CompilerMode radMode = (CompilerMode)m_pRadRadioGroup->checkedId();
	bool hdrChecked = m_pRadHDRCheck->isChecked();
	
	bool dontRunGame = m_pDontRunGameCheck->isChecked();
	bool waitForKey = m_pWaitForKeyCheck->isChecked();

	QString gameParameters = m_pGameParameters->text();

	this->close();

	// QT_TODO: Backend hammer integration
}


void CRunMapNormal::onCancelPressed()
{
	this->close();
}