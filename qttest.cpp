
#include <QApplication>
#include <QDir> 

#include "Zoo.h"

int main(int argc, char** argv)  {
	QApplication app(argc, argv);
	
	QDir::setSearchPaths("icons", QStringList(QDir::currentPath() + "/../resource/icons")); // Bad bad bad but fine...
	
	auto pZoo = new ui::CZoo(nullptr);
    pZoo->setAttribute(Qt::WA_DeleteOnClose);
    pZoo->show();
	
	return QApplication::exec();
}