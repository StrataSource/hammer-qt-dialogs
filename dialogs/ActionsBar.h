#pragma once

#include <QDialog>
#include <QPixmap>
#include <QAction>
#include <QToolBar>

#include <functional>

namespace ui
{
	// This exists purely for the zoo application
	class CActionsBarDialog : public QDialog
	{
		Q_OBJECT
	public:
		CActionsBarDialog( QWidget *pParent );

	private:
		class CActionsBar *m_pHActionsBar;
		class CActionsBar *m_pVActionsBar;
	};

	//-----------------------------------------------------------------------------------------//

	// Wrapper for QToolBar to make stuff a little less verbose
	class CActionsBar : public QWidget
	{
		Q_OBJECT

	public:
		CActionsBar( QWidget *pParent, Qt::Orientation orientation = Qt::Horizontal );

		// Todo: Is this name really clear? QWidget already has addAction
		// so we dont really have any alternatives
		QAction *addButton( const QString &pIconPath, const QString &pToolTip, const bool bCheckable, const std::function<void()> &func );
		void addSeparator();

		// todo: Since we have getToolBar(), is this really needed?
		void setIconSize(const QSize &pSize);

		QToolBar *getToolBar() { return m_pToolBar; };

	private:
		QToolBar *m_pToolBar;
	};

} // namespace ui