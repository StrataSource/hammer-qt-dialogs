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

		QPlainTextEdit *m_pGridOffsetX;
		QPlainTextEdit *m_pGridOffsetY;

		QPlainTextEdit *m_pGridSizeX;
		QPlainTextEdit *m_pGridSizeY;

		QCheckBox *m_pUseDefinitionGridSize;
		QCheckBox *m_pRandomYaw;

	private:
		QLabel *m_pSliderLabel;

	private slots:
		void onUseGridPressed();

		void changeSliderLabel(int value);
	};

} // namespace ui