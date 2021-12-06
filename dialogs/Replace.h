#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>

namespace ui
{
	class CReplace : public QDialog
	{
		Q_OBJECT
	public:
		CReplace( QWidget *pParent );

		QRadioButton *m_pSelectionButton;
		QRadioButton *m_pEntireFileButton;

		QCheckBox *m_pWholeWordsOnly;
		QCheckBox *m_pCaseSensitive;
		QCheckBox *m_pVisibleObjectsOnly;

		QLineEdit *m_pFindBox;
		QLineEdit *m_pReplaceBox;

	private slots:
		void onFindNextPressed();
		void onReplacePressed();
		void onReplaceAllPressed();
		void onCancelPressed();
	};
}