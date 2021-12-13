#pragma once

#include <QDialog>
#include <QListWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

namespace ui
{
	class CSoundBrowser : public QDialog
	{
		Q_OBJECT
	public:
		CSoundBrowser( QWidget *pParent );

		QCheckBox *m_pAutoplaySounds;
		QComboBox *m_pSoundType;

		QListWidget *m_pSoundList;

		QLineEdit *m_pSoundNameEdit;
		QLineEdit *m_pSoundFileEdit;
		QLineEdit *m_pSourceFileEdit;
		QLineEdit *m_pFilter; // I need to figure out which box to actually use here

	private slots:
		void onOkPressed();
		void onPreviewPresed();
		void onStopPressed();
		void onCancelPressed();
		void onOpenSourcePressed();
		void onRefreshSoundsPressed();
	};
}