#include "dialogs/EntityHelp.h"

#include <QVBoxLayout>

using namespace ui;

CEntityHelp::CEntityHelp( QWidget *pParent ) :
	QDialog( pParent )
{
	this->setWindowTitle( tr( "Entity Help" ) );
	this->setMinimumSize( 420, 450 );

	auto pDialogLayout = new QVBoxLayout( this );

	m_pEntityHelpBox = new QTextEdit( this );
	m_pEntityHelpBox->setReadOnly( true );

	pDialogLayout->addWidget( m_pEntityHelpBox );

	setEntity();

	m_pEntityHelpBox->moveCursor( QTextCursor::Start );

	this->setLayout( pDialogLayout );
}

void CEntityHelp::setEntity()
{
	if ( !m_pEntityHelpBox )
		return;

	// Entity name
	m_pEntityHelpBox->append( "<b><font color=\"red\"><h3>epic_p2ce_entity</h3></font</b>" );

	// Description
	m_pEntityHelpBox->append( "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque aliquet, nulla vitae placerat efficitur, massa diam faucibus dolor, efficitur ullamcorper lorem est eget est. Quisque lobortis aliquet dui. Fusce scelerisque pharetra ex a facilisis. Praesent elementum non purus at scelerisque. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse sed varius arcu. Suspendisse ut sollicitudin erat. Donec ut metus turpis. Morbi ultrices purus sit amet finibus venenatis. Nulla facilisi. Donec at sem a felis aliquam interdum et quis ante. Vestibulum nec velit vel lacus rhoncus sollicitudin. Mauris congue sem libero, consectetur convallis leo elementum ac. Vestibulum sit amet dolor nisl. Sed hendrerit sapien ac libero dictum pharetra in eu ex. Maecenas est justo, accumsan ut ante at, sodales consequat sapien." );

	// KEYS
	m_pEntityHelpBox->append( "<b><font color=\"green\"><h3>KEYS</h3></font</b>" );
	addText( "Name", "targetname", "target_source", "The name that other entities refer to this entity by" );
	addText( "Global Entity Name", "globalname", "string", "Name by which this entity is linked to another entity in a different map. When the player transitions to a new map, entities in the new map with globalnames matching entities in the previous map will have the previous map's state copied over their state." );

	// INPUTS
	m_pEntityHelpBox->append( "<b><font color=\"green\"><h3>INPUTS</h3></font</b>" );
	addText( "Kill", "", "", "Removes the entity from the world" );

	// OUTPUTS
	m_pEntityHelpBox->append( "<b><font color=\"green\"><h3>OUTPUTS</h3></font</b>" );
	addText( "OnUser1", "", "", "Fired in response to FireUser1 input." );
}

void CEntityHelp::addText( const QString &pFriendlyName, const QString &pRawName, const QString &pType, const QString &pDescription )
{
	QStringList text;
	text << "<b>" << pFriendlyName << "</b>";

	if ( pRawName != "" )
		text << " <u><i>" << pRawName << "</i></u>";
	if ( pType != "" )
		text << " <i>&lt;<font color=\"blue\">" << pType << "</font>&gt;</i>";
	if ( pDescription != "" )
		text << " " << pDescription;

	m_pEntityHelpBox->append( text.join( "" ) );
}