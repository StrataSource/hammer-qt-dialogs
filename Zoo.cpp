#include "Zoo.h"

#include "dialogs/GoTo.h"
#include "dialogs/Options.h"
#include "dialogs/RunMapNormal.h"
#include "dialogs/MapInformation.h"
#include "dialogs/EntityReport.h"
#include "dialogs/CheckForProblems.h"
#include "dialogs/PasteSpecial.h"
#include "dialogs/FindEntities.h"
#include "dialogs/Sprinkle.h"
#include "dialogs/MakeHollow.h"

using namespace ui;

struct zooDialog_t
{
	const char* name;
	QDialog* (*makefn)();
};
// Default dialog factory
template<typename T>
QDialog* makeZooDialog()
{
	return new T(nullptr);
}

// List of all dialogs to display in the zoo
static zooDialog_t s_zooDialogs[] =
{
	{"Go To Brush",				makeZooDialog<CGoToBrushDialog> },
	{"Go To Coord",				makeZooDialog<CGoToCoordDialog> },
	{"Preferences",				makeZooDialog<CPrefManager>     },
	{"Run Map Normal",			makeZooDialog<CRunMapNormal>    },
	{"Map Information",			makeZooDialog<CMapInformation>  },
	{"Entity Report",			makeZooDialog<CEntityReport>    },
	{"Check map for problems",	makeZooDialog<CCheckForProblems>},
	{"Paste Special",			makeZooDialog<CPasteSpecial>    },
	{"Find Entities",			makeZooDialog<CFindEntities>    },
	{"Entity Sprinkle",			makeZooDialog<CSprinkle>        },
	{"Make Hollow",				makeZooDialog<CMakeHollow>      },
};
static int s_zooDialogCount = sizeof(s_zooDialogs) / sizeof(zooDialog_t);


CZoo::CZoo(QWidget* pParent) :
        QDialog(pParent)
{
    this->setWindowTitle(tr("You're a Qt :)"));
    this->setMinimumWidth(300);
    
	auto* pLayout = new QVBoxLayout(this);

	for(int i = 0; i < s_zooDialogCount; i++)
	{
		// Make a button for this dialog
		QPushButton* pButton = new QPushButton(this);
		pButton->setText(tr(s_zooDialogs[i].name));
		pLayout->addWidget(pButton);

		// On button press, call the function for creating the dialog and display it
		connect(pButton, &QPushButton::released, this,
			[=]() {
				QDialog* pDialog = s_zooDialogs[i].makefn();
				pDialog->setAttribute(Qt::WA_DeleteOnClose);
				pDialog->show();
			});
	}
    
    this->setLayout(pLayout);
}
