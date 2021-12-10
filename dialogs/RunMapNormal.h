#pragma once

#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>

namespace ui
{
	class CRunMapNormal : public QDialog
	{
		Q_OBJECT
	public:
		// The button groups use this enum for ids
		enum CompilerMode
		{
			NO,
			NORMAL,
			FAST,
			ONLY_ENTS
		};

		QButtonGroup *m_pBspRadioGroup;
		QButtonGroup *m_pVisRadioGroup;
		QButtonGroup *m_pRadRadioGroup;
		QCheckBox *m_pRadHDRCheck;

		QCheckBox *m_pWaitForKeyCheck;
		QCheckBox *m_pDontRunGameCheck;

		QLineEdit *m_pGameParameters;

		CRunMapNormal( QWidget *pParent );

	private slots:
		void onOkPressed();
		void onExpertPressed();
		void onCancelPressed();
	};

} // namespace ui