#pragma once

#include <QColor>
#include <QDialog>
#include <QFrame>
#include <QLineEdit>
#include <QTreeWidget>

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
} // namespace ui