#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>

namespace ui
{
	class CTransform : public QDialog
	{
		Q_OBJECT
	public:
		CTransform( QWidget *pParent );

		QRadioButton *m_pRotate;
		QRadioButton *m_pScale;
		QRadioButton *m_pMove;

		QLineEdit *m_pXValue;
		QLineEdit *m_pYValue;
		QLineEdit *m_pZValue;

	private slots:
		void onOkPressed();
		void onCancelPressed();
	};

} // namespace ui
