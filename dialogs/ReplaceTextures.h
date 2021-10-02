#pragma once
#include <QDialog>

class QGroupBox;
class QLineEdit;
class QLabel;
class QPushButton;
class QRadioButton;
class QCheckBox;
class QDialogButtonBox;

namespace ui
{
	class CReplaceTextures : public QDialog
	{
		Q_OBJECT;
	public:

		CReplaceTextures( QWidget *parent );

	private:

		enum class TextureTarget
		{
			Find,
			Replace
		};
		enum class FindCriteria
		{
			SelectedObjects,	// Only find textures in selected objects
			Everything			// Find textures in everything
		};

		enum class ReplaceOperation
		{
			ReplaceExactMatches,		// Replace matches using an absolute path
			ReplacePartialMatches,		// Replace matches satisfying an expression
			SubstitutePartialMatches	// Substitute matches using an expression
		};

		void SelectTexture( TextureTarget target );
		void ReplaceTextures();

		FindCriteria m_FindCriteria = FindCriteria::Everything;
		bool m_IncludeHiddenObjects = false;

		ReplaceOperation m_ReplaceOperation = ReplaceOperation::ReplaceExactMatches;

		bool m_DontReplaceTextures = false;
		bool m_ScaleTextureCoordinates = false;

private slots:

		void OnTextureEdited( const QString &text );

private:

		QLabel *m_FindTexturePreview;
		QLineEdit *m_FindTextureEntry;

		QLabel *m_ReplaceTexturePreview;
		QLineEdit *m_ReplaceTextureEntry;
	};
}
