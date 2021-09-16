
#pragma once 

#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>

namespace ui
{
	
//-----------------------------------------------------------------------------------------//

class CPrefSlider : public QWidget
{
	Q_OBJECT
	QSlider* m_pSlider;
	QLabel* m_pLabel;
	float& m_setting;
	QLabel* m_pValueLabel;
	QString m_units;
	float m_inc;
	int m_prec;
	float m_default;
public:
	CPrefSlider(QWidget* pParent, const QString& label, const QString& units, float min, float max, float def, float& setting, float incrrement = 1.f);
	CPrefSlider(QWidget* pParent, const QString& label, const QString& units, float min, float max, float& setting, float increment = 1.f);
	
	QSlider& getSlider() { return *m_pSlider; };
	void setUnits(const QString& str) { m_units = str; onSliderValueChanged(m_setting * m_inc); };
	void reset() { onSliderValueChanged(m_default * m_inc); };
	
	
private slots:
	void onSliderValueChanged(int newval);
};

//-----------------------------------------------------------------------------------------//

class CPrefCheckbox : public QWidget
{
	Q_OBJECT;
	QCheckBox* m_pCheckBox;
	bool& m_setting;
	bool m_default;
public:
	CPrefCheckbox(QWidget* pParent, const QString& label, bool& setting, bool def);
	
private slots:
	void onCheckChanged(int newval);
};

//-----------------------------------------------------------------------------------------//

class CPrefIntEntry : public QWidget
{
	Q_OBJECT;
	QLineEdit* m_pLineEdit;
	int m_min;
	int m_max;
	int m_default;
	int& m_setting;
public:
	CPrefIntEntry(QWidget* pParent, const QString& label, int& setting, int min, int max, int def);
	
private slots:
	void onEntryChanged(const QString& val);
};

//-----------------------------------------------------------------------------------------//

class CPrefFloatEntry : public QWidget
{
	Q_OBJECT;
	QLineEdit* m_pLineEdit;
	float m_min;
	float m_max;
	float m_default;
	float& m_setting;
public:
	CPrefFloatEntry(QWidget* pParent, const QString& label, float& setting, float min, float max, float def);
	
private slots:
	void onEntryChanged(const QString& val);
};

}