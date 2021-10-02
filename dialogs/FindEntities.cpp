#include "dialogs/FindEntities.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace ui;

CFindEntities::CFindEntities(QWidget* pParent) :
	QDialog(pParent)
{
	this->setWindowTitle(tr("Find Entities"));

	auto pDialogLayout = new QVBoxLayout(this);
	pDialogLayout->setAlignment(Qt::AlignLeft);

	auto pFindLabel = new QLabel(tr("Targetname to find:"), this);
	m_pFindName = new QLineEdit(this);

	pDialogLayout->addWidget(pFindLabel);
	pDialogLayout->addWidget(m_pFindName);

	auto pButtonBox = new QDialogButtonBox(Qt::Orientation::Horizontal, this);
	auto pOKButton = pButtonBox->addButton(QDialogButtonBox::Ok);
	auto pCloseButton = pButtonBox->addButton(QDialogButtonBox::Close);

	pDialogLayout->addWidget(pButtonBox);

	this->setLayout(pDialogLayout);

	connect(pOKButton, &QPushButton::released, this, &CFindEntities::onOKPressed);
	connect(pCloseButton, &QPushButton::released, this, &CFindEntities::onClosePressed);

	this->setMinimumSize(this->sizeHint());
	this->setMaximumHeight(0); // Disable height resize

}

void CFindEntities::onOKPressed()
{
	//QT_TODO: Find the searched entity

	this->close();
}

void CFindEntities::onClosePressed()
{
	this->close();
}