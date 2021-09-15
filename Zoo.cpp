#include "Zoo.h"

#include "FileSelector.h"
#include "GoToDialog.h"
#include "Preferences.h"
#include "RunMapNormal.h"

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


// Specialization for File Selector
template<>
QDialog* makeZooDialog<CFileSelector>()
{
	return (QDialog*)new CFileSelector(nullptr, CFileSelector::DirsOnly);
}


// List of all dialogs to display in the zoo
static zooDialog_t s_zooDialogs[] =
{
	{"File Selector",  makeZooDialog<CFileSelector>   },
	{"Go To Brush",    makeZooDialog<CGoToBrushDialog>},
	{"Go To Coord",    makeZooDialog<CGoToCoordDialog>},
	{"Preferences",    makeZooDialog<CPrefManager>    },
	{"Run Map Normal", makeZooDialog<CRunMapNormal>   },
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