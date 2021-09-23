#pragma once

#include <QDialog>
#include <QSpinBox>

namespace ui
{
	class CMakeHollow : public QDialog
	{
		Q_OBJECT
	public:
		CMakeHollow( QWidget *pParent );

		QSpinBox *m_pHollowAmount;

	private slots:
		void onOKPressed();

		void onClosePressed();
	};

} // namespace ui