#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "MapInformation.h"

using namespace ui;

CMapInformation::CMapInformation(QWidget* pParent) :
	QDialog(pParent)
{
	this->setWindowTitle(tr("Map Information"));
	this->setFixedSize(275, 275);
	
	auto pDialogLayout = new QVBoxLayout(this);

	// Map stats
	auto pInfoLayout = new QGridLayout(this);
	pInfoLayout->setAlignment(Qt::AlignLeft);

	// Left side
	auto pSolidsLabel         = new QLabel(tr("Solids:"), this);
	auto pFacesLabel          = new QLabel(tr("Faces:"), this);
	auto pPointEntitiesLabel  = new QLabel(tr("PointEntities:"), this);
	auto pSolidEntitiesLabel  = new QLabel(tr("SolidEntities:"), this);
	auto pUniqueTexturesLabel = new QLabel(tr("Unique textures:"), this);
	auto pTextureMemoryLabel  = new QLabel(tr("Texture memory:"), this);
	auto pMaterialsUsedLabel  = new QLabel(tr("Materials used"), this);

	int pos = 0;
	pInfoLayout->addWidget(pSolidsLabel,         pos++, 0);
	pInfoLayout->addWidget(pFacesLabel,          pos++, 0);
	pInfoLayout->addWidget(pPointEntitiesLabel,  pos++, 0);
	pInfoLayout->addWidget(pSolidEntitiesLabel,  pos++, 0);
	pInfoLayout->addWidget(pUniqueTexturesLabel, pos++, 0);
	pInfoLayout->addWidget(pTextureMemoryLabel,  pos++, 0);
	pInfoLayout->addWidget(pMaterialsUsedLabel,  pos++, 0);

	// Right side
	auto pSolidsValue         = new QLabel(this);
	auto pFacesValue          = new QLabel(this);
	auto pPointEntitiesValue  = new QLabel(this);
	auto pSolidEntitiesValue  = new QLabel(this);
	auto pUniqueTexturesValue = new QLabel(this);
	auto pTextureMemoryValue  = new QLabel(this);
	
	pos = 0;
	pInfoLayout->addWidget(pSolidsValue,         pos++, 1);
	pInfoLayout->addWidget(pFacesValue,          pos++, 1);
	pInfoLayout->addWidget(pPointEntitiesValue,  pos++, 1);
	pInfoLayout->addWidget(pSolidEntitiesValue,  pos++, 1);
	pInfoLayout->addWidget(pUniqueTexturesValue, pos++, 1);
	pInfoLayout->addWidget(pTextureMemoryValue,  pos++, 1);

	pDialogLayout->addLayout(pInfoLayout);

	// Material list
	auto pMaterialList = new QListWidget(this);
	pDialogLayout->addWidget(pMaterialList);

	// Close
	auto pButtonBox   = new QDialogButtonBox();
	auto pCloseButton = pButtonBox->addButton(QDialogButtonBox::Close);
	pDialogLayout->addWidget(pButtonBox);

	this->setLayout(pDialogLayout);

	connect(pCloseButton, &QPushButton::released, this, &CMapInformation::onClosePressed);


	// QT_TODO: Backend hammer integration
	
	pSolidsValue->setText("8085");
	pFacesValue->setText("48188");
	pPointEntitiesValue->setText("0");
	pSolidEntitiesValue->setText("1113");
	pUniqueTexturesValue->setText("57");
	pTextureMemoryValue->setText("lots of bytes");

	for (int i = 0; i < 200; i++)
	{
		pMaterialList->addItem("cool/material");
		pMaterialList->addItem("nice/material");
	}
}

void CMapInformation::onClosePressed()
{
	this->close();
}