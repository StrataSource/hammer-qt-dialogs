#pragma once

#include <QDialog>
#include <QTextEdit>

namespace ui
{
	class CEntityHelp : public QDialog
	{
		Q_OBJECT
	public:

		// QT_TODO: Add the entity to the setEntity and this constructor
		// then you'll have to add all the keys, inputs and outputs in that method.
		CEntityHelp( QWidget *pParent );

		QTextEdit *m_pEntityHelpBox;

		// in the future, this would take an entity or something, for now
		// it just adds some demo junk
		void setEntity();

	private:
		void addText( QString pFriendlyName, QString pRawName, QString pType, QString pDescription );
	};
}