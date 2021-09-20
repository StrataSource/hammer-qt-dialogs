#pragma once

#include <QDialog>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>

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