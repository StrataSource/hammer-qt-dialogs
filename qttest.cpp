
#include <QApplication>

#include "Preferences.h"

int main(int argc, char** argv)  {
	QApplication app(argc, argv);
	
	auto pPrefs = new ui::CPrefManager(nullptr);
	pPrefs->show();
	
	return app.exec();
}