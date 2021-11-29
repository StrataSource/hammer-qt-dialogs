#pragma once

#include <QDialog>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

namespace ui
{
	class CFaceEditSheet : public QDialog
	{
		Q_OBJECT
	public:
		CFaceEditSheet( QWidget *pParent );
	};

	//-----------------------------------------------------------------------------------------//

	class CFaceEditMaterialTab : public QWidget
	{
		Q_OBJECT
	public:
		CFaceEditMaterialTab( QWidget *pParent );

		QDoubleSpinBox *m_pTextureScaleX;
		QDoubleSpinBox *m_pTextureScaleY;

		QSpinBox *m_pTextureShiftX;
		QSpinBox *m_pTextureShiftY;

		QSpinBox *m_pLightmapScale;
		QDoubleSpinBox *m_pRotation;

		QCheckBox *m_pTreatAsOne;
		QCheckBox *m_pAlignWorld;
		QCheckBox *m_pAlignFace;

		QLabel *m_pTextureLabel;
		QComboBox *m_pTextureGroupBox;
		QComboBox *m_pCurrentTextureBox;

	private slots:
		/*
		void onXPressed();
		void onYPressed();

		void OnLPressed();
		void OnRPressed();
		void OnFitPressed();

		void OnTPressed();
		void OnBPressed();
		void OnCPressed();

		void onHideMaskPressed();
		void onBrowsePressed();
		void onReplacePressed();
		void onApplyPressed();
		void OnMarkPressed();
		void onModePressed();
		void onSmoothingGroupsPressed();
		*/
	};

	//-----------------------------------------------------------------------------------------//

	class CFaceEditDisplacementTab : public QWidget
	{
		Q_OBJECT
	public:
		CFaceEditDisplacementTab( QWidget *pParent );

		// Attributes
		QSpinBox *m_pPowerSpinBox;
		QDoubleSpinBox *m_pElevSpinBox;
		QLineEdit *m_pScale;
		QCheckBox *m_pNoPhysColBox;
		QCheckBox *m_pNoHullColBox;
		QCheckBox *m_pNoRayColBox;

		// Masks
		QCheckBox *m_pGridBox;
		QCheckBox *m_pSelectBox;

	private slots:
		// these could probably be moved to the main tab widget
		void onApplyPressed();
		void onSelectAdjacentPressed();

		void onSelectPressed();
		void onPaintGeometryPressed();
		void onPaintAlphaPressed();
		void onInvertAlphaPressed();
		void onSculptPressed();
		void onCreatePressed();
		void onDestroyPressed();
		void onSubdividePressed();
		void onNoisePressed();
		void onSewPressed();
	};
} // namespace ui