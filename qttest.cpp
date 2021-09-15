
#include <QApplication>

#include "Zoo.h"

int main(int argc, char** argv)  {
	QApplication app(argc, argv);
	
	auto pZoo = new ui::CZoo(nullptr);
	pZoo->show();
	
	return QApplication::exec();
}