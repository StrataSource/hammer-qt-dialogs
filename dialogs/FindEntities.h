#pragma once

#include <QDialog>
#include <QLineEdit>

namespace ui
{
	class CFindEntities : public QDialog
	{
		Q_OBJECT
	public:
		CFindEntities( QWidget *pParent );

		QLineEdit *m_pFindName;

	private slots:
		void onOKPressed();

		void onClosePressed();
	};

} // namespace ui