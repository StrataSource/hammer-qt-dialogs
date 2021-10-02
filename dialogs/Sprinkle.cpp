#include "dialogs/Sprinkle.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QLineEdit>

using namespace ui;

CSprinkle::CSprinkle( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle(tr("Entity Sprinkle"));

	auto pDialogLayout = new QGridLayout(this);

	// Labels
	auto pTypeLabel = new QLabel(tr("Type:"), this);
	auto pModeLabel = new QLabel(tr("Mode:"), this);
	auto pDensityLabel = new QLabel(tr("Density:"), this);
	auto pGridOffsetLabel = new QLabel(tr("Grid Offset:"), this);
	auto pGridSizeLabel = new QLabel(tr("Grid Size:"), this);

	// Combos
	m_pTypeBox = new QComboBox(this);
	m_pModeBox = new QComboBox(this);

	// Slider
	auto pSliderLayout = new QHBoxLayout(this);
	m_pDensitySlider = new QSlider(Qt::Orientation::Horizontal, this);
	m_pDensitySlider->setMinimum(0);
	m_pDensitySlider->setMaximum(100);
	m_pDensitySlider->setTickInterval(10);
	m_pDensitySlider->setTickPosition(QSlider::TickPosition::TicksAbove);
	m_pSliderLabel = new QLabel(this);
	
	pSliderLayout->addWidget(m_pDensitySlider, 85);
	pSliderLayout->addWidget(m_pSliderLabel, 15);

	// Grid
	m_pGridOffsetX = new QLineEdit(this);
	m_pGridOffsetY = new QLineEdit(this);

	m_pGridSizeX = new QLineEdit(this);
	m_pGridSizeY = new QLineEdit(this);
	auto pUseGridButton = new QPushButton(tr("Use Grid"));
	
	// Set validators 
	m_pGridOffsetX->setValidator(new QDoubleValidator(this));
	m_pGridOffsetY->setValidator(new QDoubleValidator(this));
	m_pGridSizeX->setValidator(new QDoubleValidator(this));
	m_pGridSizeY->setValidator(new QDoubleValidator(this));

	m_pUseDefinitionGridSize = new QCheckBox(tr("Use Grid Size from Definition"), this);
	m_pRandomYaw = new QCheckBox(tr("Random Yaw"), this);

	// Add widgets row by row
	int row = 0;

	pDialogLayout->addWidget(pTypeLabel, row, 0);
	pDialogLayout->addWidget(m_pTypeBox, row, 1, 1, 3);
	row++;

	pDialogLayout->addWidget(pModeLabel, row, 0);
	pDialogLayout->addWidget(m_pModeBox, row, 1, 1, 2);
	row++;

	pDialogLayout->addWidget(pDensityLabel, row, 0);
	pDialogLayout->addLayout(pSliderLayout, row, 1, 1, 3);
	row++;

	pDialogLayout->addWidget(pGridOffsetLabel, row, 0);
	pDialogLayout->addWidget(m_pGridOffsetX, row, 1);
	pDialogLayout->addWidget(m_pGridOffsetY, row, 2);
	row++;

	pDialogLayout->addWidget(pGridSizeLabel, row, 0);
	pDialogLayout->addWidget(m_pGridSizeX, row, 1);
	pDialogLayout->addWidget(m_pGridSizeY, row, 2);
	pDialogLayout->addWidget(pUseGridButton, row, 3);
	row++;

	pDialogLayout->addWidget(m_pUseDefinitionGridSize, row, 1, 1, 3);
	row++;

	pDialogLayout->addWidget(m_pRandomYaw, row, 1, 1, 3);
	row++;

	this->setLayout(pDialogLayout);
	
	// QT_TODO: Backend hammer integration
	
	int initialSliderPosition = 25;
	m_pDensitySlider->setSliderPosition(initialSliderPosition);
	changeSliderLabel(initialSliderPosition);

	// Temporary, no tr
	m_pTypeBox->addItem("Sprinkle Type 1"); 
	m_pTypeBox->addItem("Sprinkle Type 2");
	m_pTypeBox->addItem("Sprinkle Type 3");

	m_pModeBox->addItem(tr("Additive"));
	m_pModeBox->addItem(tr("Subtractive"));
	m_pModeBox->addItem(tr("Replace"));
	m_pModeBox->addItem(tr("Overwrite"));

	m_pUseDefinitionGridSize->setChecked(true);
	m_pGridSizeX->setEnabled(false);
	m_pGridSizeY->setEnabled(false);
	m_pGridSizeX->setText("1");
	m_pGridSizeY->setText("1");

	connect(pUseGridButton, &QPushButton::released, this, &CSprinkle::onUseGridPressed);
	connect(m_pDensitySlider, &QSlider::valueChanged, this, &CSprinkle::changeSliderLabel);
	connect(m_pUseDefinitionGridSize, SIGNAL(toggled(bool)), m_pGridSizeX, SLOT(setDisabled(bool)));
	connect(m_pUseDefinitionGridSize, SIGNAL(toggled(bool)), m_pGridSizeY, SLOT(setDisabled(bool)));
	
	this->setFixedSize(this->sizeHint());
}

void CSprinkle::onUseGridPressed()
{
	this->close();
	
	//QT_TODO: Use grid
}

void CSprinkle::changeSliderLabel(int value)
{
	m_pSliderLabel->setText(QString("%1%").arg(value));
}