#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QTreeWidget>

namespace ui
{
	class CMoveToVisgroup : public QDialog
	{
		Q_OBJECT
	public:
		CMoveToVisgroup( QWidget *pParent );

		QRadioButton *m_pPlaceInExisting;
		QRadioButton *m_pCreateNew;

		QCheckBox *m_pRemoveObjects;
		QCheckBox *m_pHideObjects;

		QLineEdit *m_pNewVisgroupName;

		QTreeWidget *m_pVisgroupTree;

	private slots:
		void onOkPressed();
		void onCancelPressed();
	};
}