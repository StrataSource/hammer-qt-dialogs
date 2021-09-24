#include "dialogs/MakeHollow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace ui;

CMakeHollow::CMakeHollow(QWidget* pParent) :
	QDialog(pParent)
{
	this->setWindowTitle(tr("Hammer"));
	this->setFixedSize(280, 100);

	auto pDialogLayout = new QVBoxLayout(this);
	pDialogLayout->setAlignment(Qt::AlignLeft);

	auto pHollowLabel = new QLabel(tr("How thick do you want the walls? Use a negative number to hollow outward."), this);
	pHollowLabel->setWordWrap(true);
	m_pHollowAmount = new QSpinBox(this);
	m_pHollowAmount->setMinimum(INT_MIN);

	pDialogLayout->addWidget(pHollowLabel);
	pDialogLayout->addWidget(m_pHollowAmount);

	auto pButtonBox = new QDialogButtonBox(Qt::Orientation::Horizontal, this);
	auto pOKButton = pButtonBox->addButton(QDialogButtonBox::Ok);
	auto pCloseButton = pButtonBox->addButton(QDialogButtonBox::Close);

	pDialogLayout->addWidget(pButtonBox);

	this->setLayout(pDialogLayout);

	connect(pOKButton, &QPushButton::released, this, &CMakeHollow::onOKPressed);
	connect(pCloseButton, &QPushButton::released, this, &CMakeHollow::onClosePressed);

}

void CMakeHollow::onOKPressed()
{
	//QT_TODO: Make the brush hollow

	this->close();
}

void CMakeHollow::onClosePressed()
{
	this->close();
}