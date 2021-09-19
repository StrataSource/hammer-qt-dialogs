#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>

namespace ui
{
	class CEntityReport : public QDialog
	{
		Q_OBJECT
	public:
		CEntityReport( QWidget *pParent );

		enum FilterMode
		{
			EVERYTHING,
			BRUSH_ENTS,
			POINT_ENTS,
		};

		QButtonGroup *m_pFilterModeRadioGroup;

		QCheckBox *m_pFilterIncludeHiddenCheck;

		QCheckBox *m_pFilterByKVCheck;
		QCheckBox *m_pFilterKVExactCheck;

		QLineEdit *m_pFilterKey;
		QLineEdit *m_pFilterVal;

		QCheckBox *m_pFilterByClassCheck;

	private slots:
		void onGoToPressed();
		void onDeletePressed();
		void onPropertiesPressed();

		void onClosePressed();
	};

} // namespace ui