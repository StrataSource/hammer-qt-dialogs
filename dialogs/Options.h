#pragma once

#include <QDialog>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QListWidget>

#include "widgets/FileSelector.h"
#include "widgets/PrefSlider.h"

namespace ui
{
	class COptions : public QDialog
	{
		Q_OBJECT
	public:
		COptions( QWidget *pParent );

		class COptionsGeneralTab *m_pGeneralTab;
		class COptions2DViewsTab *m_p2DViewsTab;
		class COptions3DViewsTab *m_p3DViewsTab;
		class COptionsGameConfigsTab *m_pGameConfigsTab;
		class COptionsBuildProgramsTab *m_pBuildProgramsTab;
		class COptionsMaterialsTab *m_pMaterialsTab;
		class COptionsColorsTab *m_pColorsTab;

		void loadSettings();
		void saveSettings();

	private slots:
		void onOkPressed();
		void onCancelPressed();
		void onApplyPressed();
		void onHelpPressed();
	};

	//-----------------------------------------------------------------------------------------//

	class COptionsGeneralTab : public QWidget
	{
		Q_OBJECT
	public:
		COptionsGeneralTab( QWidget *pParent );

		// Window Setup
		QCheckBox *m_pUseIndependentWindowConfigs;
		QCheckBox *m_pLoadDefaultWindowPosWithMaps;
		QCheckBox *m_pShowMessagesWindowOnStartUp;

		// Autosave
		QCheckBox *m_pEnableAutosave;
		QLineEdit *m_pAutosaveTime;
		QLineEdit *m_pAutosaveSize;
		QLineEdit *m_pAutosaveIterations;
		CFileSelector *m_pAutosaveDirectory;

		// Discord
		QCheckBox *m_pEnableDiscord;
		QLineEdit *m_pDiscordLine1;
		QLineEdit *m_pDiscordLine2;

		// Other settings
		QSpinBox *m_pUndoLevels;
		QSpinBox *m_pMaxCameras;

		CFileSelector *m_pFavoriteMaterial;

		QCheckBox *m_pAllowGroupingWhileIgnoreGroups;
		QCheckBox *m_pStretchToFitOrigBounding;
		QCheckBox *m_pEnableMatProxies;
		QCheckBox *m_pEnablePerforce;
		QCheckBox *m_pUseNodrawForClippedFaces;
		QLineEdit *m_pFavMaterial;
		QCheckBox *m_pAutoDeleteEmptyVisgroups;
		QCheckBox *m_pShowCarveWarning;

	private:
		QGroupBox *addWindowSetupGroup();
		QGroupBox *addAutosaveGroup();
		QGroupBox *addDiscordGroup();
	};

	//-----------------------------------------------------------------------------------------//

	class COptions2DViewsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptions2DViewsTab( QWidget *pParent );

		// Window
		QCheckBox *m_pDefaultTo15DegRots;
		QCheckBox *m_pDisplayScrollbars;
		QCheckBox *m_pDrawVertices;
		QCheckBox *m_pDrawModels;
		QCheckBox *m_pWhiteOnBlackColorScheme;
		QCheckBox *m_pUseVisgroupColorsForObjectLines;
		QCheckBox *m_pKeepVisgroupWhenCloneDragging;
		QCheckBox *m_pArrowkeyNudgeSelected;
		QCheckBox *m_pReorientPrimiitvesOnCreation;
		QCheckBox *m_pAutoInfiniteSelection;
		QCheckBox *m_pSelectObjectsByCenter;
		QCheckBox *m_pCenterOnCameraAfterMovement;

		// Grid
		QComboBox *m_pGridSizeBox;

		CPrefSlider *m_pIntensitySlider;
		float m_fIntensityValue;

		QCheckBox *m_pHighlightEvery64UnitsBox;
		QCheckBox *m_pHighlightEveryXGridLinesBox;
		QLineEdit *m_pHighlightEveryXGridLinesLine;
		QCheckBox *m_pDottedGridBox;
		QCheckBox *m_pHideGridSmallerThan4PixelsBox;

	private:
		QGroupBox *addOptionsGroup();
		QGroupBox *addGridGroup();
	};

	//-----------------------------------------------------------------------------------------//

	class COptions3DViewsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptions3DViewsTab( QWidget *pParent );

		// Performance
		QCheckBox *m_pFilterTextures;
		QCheckBox *m_pAnimateModels;

		CPrefSlider *m_pBackClippingPlaneSlider;
		float m_fBackClippingPlaneValue;
		CPrefSlider *m_pModelRenderDistanceSlider;
		float m_fModelRenderDistanceValue;
		CPrefSlider *m_pDetailRenderDistanceSlider;
		float m_fDetailRenderDistanceValue;

		// Navigation
		QCheckBox *m_pUseMouseLookNavigation;
		QCheckBox *m_pReverseMouseYAxis;

		CPrefSlider *m_pMouseSensitivitySlider;
		float m_fMouseSensitivityValue;
		CPrefSlider *m_pForwardSpeedSlider;
		float m_fForwardSpeedValue;
		CPrefSlider *m_pTimeToTopSpeedSlider;
		float m_fTimeToTopSpeedValue;

		// General
		QCheckBox *m_pReverseSelectionOrder;
		QCheckBox *m_pDrawSkyboxPreview;
		QSpinBox *m_pCameraFov;
		QSpinBox *m_pLightSpotConeModifier;

	private:
		QGroupBox *addPerformanceBox();
		QGroupBox *addNavigationBox();
		QGroupBox *addGeneralBox();
	};

	//-----------------------------------------------------------------------------------------//

	class COptionsGameConfigsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptionsGameConfigsTab( QWidget *pParent );

		QComboBox *m_pConfigCombo;
		QComboBox *m_pDefaultPointEntity;
		QComboBox *m_pDefaultSolidEntity;

		QLineEdit *m_pDefTextureScale;
		QLineEdit *m_pDefLightMapScale;

		QListWidget *m_pGameDataList;

		CFileSelector *m_pCordonTexture;
		CFileSelector *m_pGameExec;
		CFileSelector *m_pGameDir;
		CFileSelector *m_pHammerVmfDir;
		CFileSelector *m_pPrefabDir;

	private:
		QGridLayout *addConfigAndGameDataLayout();
		QGridLayout *addEntityAndScaleLayout();

	private slots:
		void onConfigEditPressed();
		void onGameDataAddPressed();
		void onGameDataEditPressed();
		void onGameDataRemovePressed();
	};

	//-----------------------------------------------------------------------------------------//

	class COptionsBuildProgramsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptionsBuildProgramsTab( QWidget *pParent );

		QComboBox *m_pConfigCombo;

		CFileSelector *m_pGameExe;
		CFileSelector *m_pBSPExe;
		CFileSelector *m_pPostCompExe;
		CFileSelector *m_pVISExe;
		CFileSelector *m_pRADExe;
		CFileSelector *m_pOutputDir;
	};

	//-----------------------------------------------------------------------------------------//

	class COptionsMaterialsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptionsMaterialsTab( QWidget *pParent );

		QListWidget *m_pMaterialExclusionList;
		QCheckBox *m_pEnableColor;

	private:
		QGroupBox *addMaterialGroup();

	private slots:
		void onAddPressed();
		void onRemovePressed();
	};

	//-----------------------------------------------------------------------------------------//

	// Forward declare for the options tab
	class CColorBox;

	class COptionsColorsTab : public QWidget
	{
		Q_OBJECT
	public:
		COptionsColorsTab( QWidget *pParent );

		QCheckBox *m_pCustomColors;
		QCheckBox *m_pAxis;
		QCheckBox *m_pGrid;
		QCheckBox *m_pDotGrid;
		QCheckBox *m_p10Grid;
		QCheckBox *m_p1024Grid;

		CColorBox *m_pGridColor;
		CColorBox *m_pDotGridColor;
		CColorBox *m_p10GridColor;
		CColorBox *m_p1024GridColor;
		CColorBox *m_pBackgroundColor;

		CColorBox *m_pAxisColor;
		CColorBox *m_pBrushColor;
		CColorBox *m_pEntityColor;
		CColorBox *m_pSelectionColor;
		CColorBox *m_pVertexColor;

		CColorBox *m_pHandleColor;
		CColorBox *m_pBlockColor;
		CColorBox *m_pToolSelectionColor;
		CColorBox *m_pMorphColor;
		CColorBox *m_pPathColor;
		CColorBox *m_pDragColor;

		CColorBox *m_pWireframeColor;
		CColorBox *m_pWireframeNonSolidColor;

	private:
		QGroupBox *add2DColorGroup();
		QGroupBox *addColorsGroup();
	};

	//-----------------------------------------------------------------------------------------//

	class CColorBox : public QWidget
	{
		Q_OBJECT
	public:
		CColorBox( QWidget *pParent, const QString &label );

		void setColor( const QColor &pNewColor );
		QLabel *GetLabel() { return m_pLabel; }
		QColor GetColor() { return m_Color; }

	private:
		QLabel *m_pLabel;
		class CColorPushButton *m_pButton;
		QColor m_Color;

	private slots:
		void onButtonPressed();
	};

	//-----------------------------------------------------------------------------------------//

	class CColorPushButton : public QPushButton
	{
		Q_OBJECT
	public:
		CColorPushButton( QWidget *pParent, const QColor &color = Qt::white );
		void setColor( const QColor &pNewColor );

	protected:
		void paintEvent( QPaintEvent *pe ) override;

	private:
		QColor m_Color;
	};

} // namespace ui