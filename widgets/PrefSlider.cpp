
#include <QHBoxLayout>
#include <QIntValidator>
#include <QDoubleValidator>

#include "PrefSlider.h"

using namespace ui;

//-----------------------------------------------------------------------------------------//

CPrefSlider::CPrefSlider(QWidget* pParent, const QString& label, const QString& units, float min, float max, float& setting, float inc) :
	CPrefSlider(pParent, label, units, min, max, min, setting, inc)
{
}

CPrefSlider::CPrefSlider(QWidget* pParent, const QString& label, const QString& units, float min, float max, float def, float& setting, float inc) :
	QWidget(pParent),
	m_setting(setting)
{
	m_units = units;
	m_inc = inc;
	m_default = def;
	
	if(m_inc == 1.f)
		m_prec = 0;
	else if(m_inc == 0.5f)
		m_prec = 1;
	else
		m_prec = 2;
	
	m_pLabel = new QLabel(this);
	m_pSlider = new QSlider(Qt::Orientation::Horizontal, this);
	m_pValueLabel = new QLabel(this);
	
	m_pSlider->setMinimum(min / inc);
	m_pSlider->setMaximum(max / inc);
	m_pSlider->setValue(def * m_inc);
	m_setting = def;
	
	m_pLabel->setText(label);
	
	// Bit of a hack but I think it works. Maybe there's a better way to do this? 
	// Set the value label to it's absolute max and min setting, choose the widest and set it's slider value to that.
	auto estimateWidth = [&, this](int val) -> int {
		QString curVal = QString::number(m_setting);
		curVal.append(" ");
		curVal.append(units);
		this->m_pValueLabel->setText(curVal);
		return this->m_pValueLabel->width();
	};
	int smallW = estimateWidth(min);
	int largeW = estimateWidth(max);
	m_pValueLabel->setFixedWidth(smallW > largeW ? smallW : largeW);
	
	QString curVal = QString::number(m_setting, 'f', m_prec);
	curVal.append(" ");
	curVal.append(units);
	m_pValueLabel->setText(curVal);
	m_pValueLabel->setAlignment(Qt::AlignRight);
	
	
	auto* pLayout = new QHBoxLayout(this);
	pLayout->addWidget(m_pLabel);
	pLayout->addWidget(m_pSlider);
	pLayout->addWidget(m_pValueLabel);
	
	pLayout->setContentsMargins( 0, 0, 0, 0 );

	connect(m_pSlider, &QSlider::valueChanged, this, &CPrefSlider::onSliderValueChanged);
}

void CPrefSlider::onSliderValueChanged(int newval)
{
	m_setting = newval * m_inc;
	QString curVal = QString::number(m_setting, 'f', m_prec);
	if(!m_units.isEmpty())
	{
		curVal.append(" ");
		curVal.append(m_units);	
	}
	m_pValueLabel->setText(curVal);
}

//-----------------------------------------------------------------------------------------//

CPrefCheckbox::CPrefCheckbox(QWidget* pParent, const QString& label, bool& setting, bool def) :
	QWidget(pParent),
	m_setting(setting)
{
	m_default = def;
	
	m_pCheckBox = new QCheckBox(this);
	
	m_pCheckBox->setCheckable(true);
	m_pCheckBox->setChecked(def);
	m_pCheckBox->setText(label);
	
	connect(m_pCheckBox, &QCheckBox::stateChanged, this, &CPrefCheckbox::onCheckChanged);
}

void CPrefCheckbox::onCheckChanged(int newval)
{
	m_setting = newval;
}

//-----------------------------------------------------------------------------------------//

CPrefIntEntry::CPrefIntEntry(QWidget* pParent, const QString& label, int& setting, int min, int max, int def) :
	QWidget(pParent),
	m_setting(setting)
{
	m_setting = def;
	m_max = max;
	m_min = min;
	
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setText(label);
	m_pLineEdit->setValidator(new QIntValidator(min, max, this));
	
	connect(m_pLineEdit, &QLineEdit::textChanged, this, &CPrefIntEntry::onEntryChanged);
}

void CPrefIntEntry::onEntryChanged(const QString& str)
{
	m_setting = str.toInt();
}

//-----------------------------------------------------------------------------------------//

CPrefFloatEntry::CPrefFloatEntry(QWidget* pParent, const QString& label, float& setting, float min, float max, float def) :
	QWidget(pParent),
	m_setting(setting)
{
	m_setting = def;
	m_max = max;
	m_min = min;
	
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setText(label);
	m_pLineEdit->setValidator(new QDoubleValidator(min, max, 2, this));
	
	connect(m_pLineEdit, &QLineEdit::textChanged, this, &CPrefFloatEntry::onEntryChanged);
}

void CPrefFloatEntry::onEntryChanged(const QString& str)
{
	m_setting = str.toFloat();
}
