#pragma once

#include <QDialog>
#include <QComboBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QLabel>

namespace ui
{
	class CSprinkle : public QDialog
	{
		Q_OBJECT
	public:
		CSprinkle( QWidget *pParent );

		QComboBox *m_pTypeBox;
		QComboBox *m_pModeBox;
		QSlider *m_pDensitySlider;

		QLineEdit *m_pGridOffsetX;
		QLineEdit *m_pGridOffsetY;

		QLineEdit *m_pGridSizeX;
		QLineEdit *m_pGridSizeY;

		QCheckBox *m_pUseDefinitionGridSize;
		QCheckBox *m_pRandomYaw;

	private:
		QLabel *m_pSliderLabel;

	private slots:
		void onUseGridPressed();

		void changeSliderLabel(int value);
	};

} // namespace ui