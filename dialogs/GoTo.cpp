
#include <QLabel>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QFontDatabase>

#include "GoTo.h"

using namespace ui;

//-----------------------------------------------------------------//

CGoToCoordDialog::CGoToCoordDialog(QWidget* pParent) :
	QDialog(pParent)
{
	const auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
	
	this->setWindowTitle(tr("Go to coordinates"));

	m_pXYZ = new QLineEdit(this);
	m_pXYZ->setPlaceholderText(tr("Position: x, y, z"));
	m_pXYZ->setFont(fixedFont);
	
	m_pAngles = new QLineEdit(this);
	m_pAngles->setPlaceholderText(tr("Angles: pitch, yaw, roll"));
	m_pAngles->setFont(fixedFont);

	m_pGo = new QPushButton(this);
	m_pGo->setText(tr("Go"));
	
	m_pCancel = new QPushButton(this);
	m_pCancel->setText(tr("Cancel"));
	
	auto* pLayout = new QVBoxLayout(this);
	pLayout->addWidget(m_pXYZ);
	pLayout->addWidget(m_pAngles);
	
	auto* pButtonLayout = new QHBoxLayout(this);
	pButtonLayout->addWidget(m_pCancel);
	pButtonLayout->addWidget(m_pGo);
	pLayout->addLayout(pButtonLayout);

	this->setLayout(pLayout);
	
	this->setMinimumSize(this->sizeHint());
	this->setMaximumHeight(0); // Disable vertical resize 
		
	connect(m_pGo, &QPushButton::released, this, &CGoToCoordDialog::onGoPressed);
	connect(m_pCancel, &QPushButton::released, this, &CGoToCoordDialog::onCancelPressed);
}

void CGoToCoordDialog::onCancelPressed()
{
	// QT_TODO: Backend hammer integration
	this->close();
}

void CGoToCoordDialog::onGoPressed()
{
	// QT_TODO: Backend hammer integration
}

//-----------------------------------------------------------------//

CGoToBrushDialog::CGoToBrushDialog(QWidget* pParent) : 
	QDialog(pParent)
{
	this->setWindowTitle(tr("Go to brush ID"));
	
	m_pBrush = new QLineEdit(this);
	m_pBrush->setValidator(new QIntValidator(this));
	m_pBrush->setPlaceholderText(tr("Brush ID"));
	
	m_pGo = new QPushButton(this);
	m_pGo->setText(tr("Go"));

	m_pCancel = new QPushButton(this);
	m_pCancel->setText(tr("Cancel"));
	
	auto* pLayout = new QVBoxLayout(this);
	auto* pBtnLayout = new QHBoxLayout(this);
	
	pBtnLayout->addWidget(m_pCancel);
	pBtnLayout->addWidget(m_pGo);
	
	pLayout->addWidget(m_pBrush);
	pLayout->addLayout(pBtnLayout);
	
	this->setLayout(pLayout);
	
	this->setMinimumSize(this->sizeHint());
	this->setMaximumHeight(0); // Disable vertical resize
	
	connect(m_pGo, &QPushButton::released, this, &CGoToBrushDialog::onGoPressed);
	connect(m_pCancel, &QPushButton::released, this, &CGoToBrushDialog::onCancelPressed);
}

void CGoToBrushDialog::onCancelPressed()
{
	// QT_TODO: Backend hammer integration
	this->close();
}

void CGoToBrushDialog::onGoPressed()
{
	// QT_TODO: Backend hammer integration
}

//-----------------------------------------------------------------//