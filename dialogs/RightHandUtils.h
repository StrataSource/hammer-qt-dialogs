#pragma once

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QLabel>
#include <QTreeWidget>
#include <QSpinBox>

namespace ui
{
	// Here for the zoo, so we can showcase them
	class CRightHandUtils : public QDialog
	{
		Q_OBJECT
	public:
		CRightHandUtils( QWidget *pParent );
	};

	//-----------------------------------------------------------------------------------------//

	class CSelectWidget : public QWidget
	{
		Q_OBJECT
	public:
		CSelectWidget( QWidget *pParent );

		QButtonGroup *m_pSelectGroup;
		QPushButton *m_pGroupsButton;
		QPushButton *m_pObjectsButton;
		QPushButton *m_pSolidsButton;

	private:
		void onGroupsPressed();
		void onObjectsPressed();
		void onSolidsPressed();
	};

	//-----------------------------------------------------------------------------------------//

	class CTextureGroupWidget : public QWidget
	{
		Q_OBJECT
	public:
		CTextureGroupWidget( QWidget *pParent );

		//void setTexture( const QString &pTexturePath );

		QLabel *m_pTextureLabel;

		QComboBox *m_pModSelectorBox;
		QComboBox *m_pCurrentTextureBox;

		QPushButton *m_pBrowseButton;
		QPushButton *m_pReplaceButton;
		QPushButton *m_pFavoriteButton;
		QPushButton *m_pNoDrawButton;
	};

	//-----------------------------------------------------------------------------------------//

	class CVisgroupsWidget : public QWidget
	{
		Q_OBJECT
	public:
		CVisgroupsWidget( QWidget *pParent );

		QTreeWidget *m_pUserTree;
		QTreeWidget *m_pAutoTree;
		QTreeWidget *m_pCordonTree;

		QPushButton *m_pShowButton;
		QPushButton *m_pEditButton;
		QPushButton *m_pMarkButton;
		QPushButton *m_pUpButton;
		QPushButton *m_pDownButton;

	private:
		void onShowPressed();
		void onEditPressed();
		void onMarkPressed();
		void onUpPressed();
		void onDownPresed();
	};

	//-----------------------------------------------------------------------------------------//

	class CPrefabsWidget : public QWidget
	{
		Q_OBJECT
	public:
		CPrefabsWidget( QWidget *pParent );

		QPushButton *m_pToWorldButton;
		QPushButton *m_pToEntityButton;
		QPushButton *m_pCreateButton;

		QComboBox *m_pCategoriesBox;
		QComboBox *m_pObjectsBox;

		QSpinBox *m_pFacesBox;

	private:
		void onToWorldPressed();
		void onToEntityPressed();
		void onCreatePrefabPressed();
	};

} // namespace ui