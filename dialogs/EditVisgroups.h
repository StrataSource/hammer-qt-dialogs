#pragma once

#include <QDialog>
#include <QTreeWidget>
#include <QLineEdit>
#include <QFrame>
#include <QColor>

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
		void setColorFrameColor( const QColor &pNewColor );

		QColor m_pColorFrameColor;

	private slots:
		void onNewGroupPressed();
		void onPurgeEmptyPressed();
		void onClosePressed();
		void onColorPressed();
		void onRemovePressed();
	};
}