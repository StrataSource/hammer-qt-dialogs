#pragma once

#include <QDialog>
#include <QTreeWidget>
#include <QLineEdit>
#include <QFrame>

namespace ui
{
	class CEditVisgroups : public QDialog
	{
		Q_OBJECT
	public:
		CEditVisgroups( QWidget *pParent );

		QTreeWidget *m_pVisgroupTree;
		QLineEdit *m_pVisgroupNameBox;
		QFrame *m_pColorFrame;

	private:
		// The parameter here can be changed as fit, for now I set it to QColor
		void setColorFrameColor( int r, int g, int b );

	private slots:
		void onNewGroupPressed();
		void onPurgeEmptyPressed();
		void onClosePressed();
		void onColorPressed();
		void onRemovePressed();
	};
}