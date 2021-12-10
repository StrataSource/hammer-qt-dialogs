#pragma once

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>

namespace ui
{
	class CCheckForProblems : public QDialog
	{
		Q_OBJECT
	public:
		CCheckForProblems( QWidget *pParent );

	private slots:
		void onGoToPressed();
		void onFixPressed();
		void onFixAllTypePressed();

		void onClosePressed();
	};

} // namespace ui