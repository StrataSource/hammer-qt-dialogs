
#include "Utils.h"

#include <QString>
#include <QDir>

using namespace ui;

void ui::StripFileName(QString& path)
{
	int i;
	for(i = path.length()-1; i > 0; i--) 
	{
		auto c = path.at(i);
		if(c == QChar('/') || c == QChar('\\'))
			break;
	}
	
	if(i > 0)
	{
		path.remove(i, path.length());
	}
}