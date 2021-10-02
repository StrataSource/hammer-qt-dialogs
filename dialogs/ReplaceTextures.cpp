#include "ReplaceTextures.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QAction>
#include <QGridLayout>

using namespace ui;

CReplaceTextures::CReplaceTextures( QWidget *parent ) :
	QDialog( parent )
{
	QIcon searchIcon( "icons/search.svg" );
	QPixmap placeholderImage( 100, 100 );
	placeholderImage.fill( Qt::black );

	m_FindTextureEntry = new QLineEdit( this );
	m_FindTextureEntry->addAction( new QAction( searchIcon, tr( "Select texture" ), m_FindTextureEntry ), QLineEdit::TrailingPosition );

	m_FindTexturePreview = new QLabel( this );
	m_FindTexturePreview->setPixmap( placeholderImage );

	auto findLayout = new QVBoxLayout( this );
	findLayout->addWidget( m_FindTextureEntry );
	findLayout->addWidget( m_FindTexturePreview );

	auto findBox = new QGroupBox( tr( "Find" ), this );
	findBox->setLayout( findLayout );
	findBox->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

	m_ReplaceTextureEntry = new QLineEdit( this );
	m_ReplaceTextureEntry->addAction( new QAction( searchIcon, tr( "Select texture" ), m_ReplaceTextureEntry ), QLineEdit::TrailingPosition );

	m_ReplaceTexturePreview = new QLabel( this );
	m_ReplaceTexturePreview->setPixmap( placeholderImage );

	auto replaceLayout = new QVBoxLayout( this );
	replaceLayout->addWidget( m_ReplaceTextureEntry );
	replaceLayout->addWidget( m_ReplaceTexturePreview );

	auto replaceBox = new QGroupBox( tr( "Replace" ), this );
	replaceBox->setLayout( replaceLayout );

	auto texturesBoxLayout = new QHBoxLayout( this );
	texturesBoxLayout->addWidget( findBox );
	texturesBoxLayout->addWidget( replaceBox );

	auto texturesBox = new QWidget( this );
	texturesBox->setLayout( texturesBoxLayout );

	auto searchSelected = new QRadioButton( tr( "Marked objects" ), this );
	auto searchEverything = new QRadioButton( tr( "Everything" ), this );
	auto searchIncludeHidden = new QCheckBox( tr( "Hidden objects too" ), this );

	// QT_TODO: Callbacks/event listening - needed here to check when objects are selected
	searchSelected->setDisabled( true );
	searchEverything->setChecked( true );

	auto filterLayout = new QVBoxLayout( this );
	filterLayout->addWidget( searchSelected );
	filterLayout->addWidget( searchEverything );
	filterLayout->addWidget( searchIncludeHidden );

	auto filterBox = new QGroupBox( tr( "Filter" ), this );
	filterBox->setLayout( filterLayout );

	auto replaceExact = new QRadioButton( tr( "Replace exact matches" ), this );
	auto replacePartial = new QRadioButton( tr( "Replace partial matches" ), this );
	auto substitutePartial = new QRadioButton( tr( "Substitute partial matches" ), this );
	replaceExact->setChecked( true );

	auto operationLayout = new QVBoxLayout( this );
	operationLayout->addWidget( replaceExact );
	operationLayout->addWidget( replacePartial );
	operationLayout->addWidget( substitutePartial );

	auto operationBox = new QGroupBox( tr( "Operation" ), this );
	operationBox->setLayout( operationLayout );

	auto configurationBoxLayout = new QHBoxLayout( this );
	configurationBoxLayout->addWidget( filterBox );
	configurationBoxLayout->addWidget( operationBox );

	auto configurationBox = new QWidget( this );
	configurationBox->setLayout( configurationBoxLayout );

	auto dontReplaceTextures = new QCheckBox( tr( "Do not replace textures (mark found solids)" ), this );
	auto scaleTextureCoordinates = new QCheckBox( tr( "Rescale texture coordinates for new texture size" ), this );
	auto dialogControls = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this );

	auto rootLayout = new QVBoxLayout( this );
	rootLayout->addWidget( new QLabel( tr("Textures:"), this ) );
	rootLayout->addWidget( texturesBox );

	rootLayout->addWidget( new QLabel( tr("Configuration:"), this ) );
	rootLayout->addWidget( configurationBox );

	rootLayout->addWidget( dontReplaceTextures );
	rootLayout->addWidget( scaleTextureCoordinates );
	rootLayout->addWidget( dialogControls );

	setWindowTitle( tr( "Replace Textures" ) );
	setLayout( rootLayout );
	setVisible( true );

	connect(m_FindTextureEntry, SIGNAL(textChanged), this, SLOT(OnTextureEdited));
	connect(m_ReplaceTextureEntry, SIGNAL(textChanged), this, SLOT(OnTextureEdited));

	connect(searchSelected, &QRadioButton::toggled, this,
		[=] (bool checked) {
			m_FindCriteria = FindCriteria::SelectedObjects;
		});

	connect(searchEverything, &QRadioButton::toggled, this,
		[=] (bool checked) {
			m_FindCriteria = FindCriteria::Everything;
		});
	
	connect(searchIncludeHidden, &QCheckBox::toggled, this,
		[=] (bool checked) {
			m_IncludeHiddenObjects = checked;
		});

	connect(dontReplaceTextures, &QCheckBox::toggled, this,
		[=] (bool checked) {
			m_DontReplaceTextures = checked;
		});

	connect(scaleTextureCoordinates, &QCheckBox::toggled, this,
		[=] (bool checked) {
			m_ScaleTextureCoordinates = checked;
		});

	connect(dialogControls, &QDialogButtonBox::accepted, this,
		[=] {
			this->ReplaceTextures();
		});

	connect(dialogControls, SIGNAL(rejected), this, SLOT(close));
}

void CReplaceTextures::SelectTexture( TextureTarget target )
{
	// QT_TODO: Open the Texture Browser to select the new texture for 'target'

	auto textureEntry = target == TextureTarget::Find ? m_FindTextureEntry : m_ReplaceTextureEntry;
//	textureEntry->setText("found texture");

	printf("CReplaceTextures::SelectTexture()\n");
}

void CReplaceTextures::ReplaceTextures()
{
	// QT_TODO: Perform the texture replacement

	printf("CReplaceTextures::ReplaceTextures()\n");
}

void CReplaceTextures::OnTextureEdited( const QString &text )
{
	QLineEdit *entry = static_cast<QLineEdit *>(sender());
/*
	CQtTexture texture( text );
	if ( !texture.valid() )
		return

	if ( sender == m_FindTextureEntry )
		m_FindTexturePreview->setPixmap( texture.toPixmap() );
	else
		m_ReplaceTexturePreview->setPixmap( texture.toPixmap() );
*/

	printf("CReplaceTextures::UpdateTexture()\n");
}