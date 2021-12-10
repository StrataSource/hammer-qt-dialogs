
#include "widgets/FileSelector.h"

#include <QDialog>
#include <QString>
#include <QTabWidget>

namespace ui
{
	class CPrefManager : public QDialog
	{
		Q_OBJECT

		CFileSelector *m_pSelector1;

	public:
		CPrefManager( QWidget *pParent );
	};

} // namespace ui