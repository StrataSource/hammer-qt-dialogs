
#include <QString>
#include <QTabWidget>
#include <QDialog>

#include "widgets/FileSelector.h"

namespace ui
{

class CPrefManager : public QDialog
{
	Q_OBJECT
	
	CFileSelector* m_pSelector1;
public:
	CPrefManager(QWidget* pParent);
};

}