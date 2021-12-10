#pragma once

#include <QDialog>

namespace ui
{
	class CMapInformation : public QDialog
	{
		Q_OBJECT
	public:
		CMapInformation( QWidget *pParent );

	private slots:
		void onClosePressed();
	};

} // namespace ui