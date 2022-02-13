#pragma once

#include <QDialog>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

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
		class CHActionsBar *m_pHActionsBar;
		class CVActionsBar *m_pVActionsBar;
	};

	//-----------------------------------------------------------------------------------------//

	// This is the base class for the actions bar
	// we create 2 other ones so it's easier to know
	// which is horizontal and which is vertical
	class CActionsBar : public QWidget
	{
		Q_OBJECT
	protected:
		CActionsBar( QWidget *pParent );

	public:
		// Todo: Is this name really clear? QWidget already has addAction
		// so we dont really have any alternatives
		class CActionBarButton *addButton( const QString &pIconPath, const QString &pToolTip, const bool bCheckable, const std::function<void()> &func );
		void addSeparator();

		QBoxLayout *m_pDialogLayout;
	};

	//-----------------------------------------------------------------------------------------//

	class CActionBarButton : public QPushButton
	{
		Q_OBJECT
	public:
		CActionBarButton( QWidget *pParent );

	protected:
		void paintEvent( QPaintEvent *pe ) override;
	};

	//-----------------------------------------------------------------------------------------//

	class CHActionsBar : public CActionsBar
	{
		Q_OBJECT
	public:
		CHActionsBar( QWidget *pParent );
	};

	//-----------------------------------------------------------------------------------------//

	class CVActionsBar : public CActionsBar
	{
		Q_OBJECT
	public:
		CVActionsBar( QWidget *pParent );
	};

} // namespace ui