#pragma once

#include <QDialog>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPushButton>

#include <functional>

namespace ui
{
	class CActionsBar : public QDialog
	{
		Q_OBJECT
	public:
		CActionsBar( QWidget *pParent );

		void addAction( const QString &pIconPath, const std::function<void()> &func );
		void addSeparator();

	private:
		QBoxLayout *m_pDialogLayout;
	};
} // namespace ui