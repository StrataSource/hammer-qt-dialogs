
#pragma once

#include <QDialog>
#include <QAbstractItemModel>

#include "widgets/KeyRecorder.h"

// QT_TODO: Change this to the actual file 
constexpr const char* KEYBINDS_FILE = "KeyBinds.cfg";

namespace ui
{
//-----------------------------------------------------------------//
// Purpose: Individual keybind
//-----------------------------------------------------------------//
class CKeyBind : public QObject
{
	Q_OBJECT;
private:
	friend class CKeyBindingDialog;
	QString m_name;
	const char* m_displayName;
	const char* m_defaultBind;
	const char* m_desc;
	QKeySequence m_seq;
public:
	CKeyBind(const QString& bindingName, const char* displayName, const char* defaultBind, const char* description);

	const QKeySequence& Get() const;
	void Reset();
	void Set(const QKeySequence& seq);
	
	const QString& GetName() const { return m_name; };
	const char* GetDefaultBind() const { return m_defaultBind; };
	
signals:
	void keybindChanged(const QKeySequence newsequence);
};

//-----------------------------------------------------------------//
// Purpose: Dialog to handle key binding
//-----------------------------------------------------------------//
class CKeyBindingDialog : public QDialog
{
	Q_OBJECT;	
	
	QList<CKeyRecorder*> m_recorders;
	bool m_bDirty = false;
public:
	CKeyBindingDialog(QWidget* pParent);
	
private:
	void onUseDefaults();
	void onLoad();
	void onSave();
	void onSaveAs();
	void onCancel();
};

//-----------------------------------------------------------------//
// Purpose: Manages all keybinds
//-----------------------------------------------------------------//
class CKeyBindManager
{
public:
	// Reset all binds to default
	void ResetAllBinds(); 
	
	CKeyBind* FindBinding(const char* bindName);
	
	// Save bindings to a config file, which can then be loaded by LoadFromFile
	void SaveToFile(const char* path);
	
	// Load existing bindings from file
	void LoadFromFile(const char* path);
	
	// Notify change of bind
	void NotifyChangeKeyBind(CKeyBind* pBind);
};

CKeyBindManager& KeyBindMgr();

//-----------------------------------------------------------------//
// Purpose: Massive huge list of keybinds
//-----------------------------------------------------------------//
namespace binds
{
// --- IDR_MAINFRAME --- //
extern CKeyBind ContextHelp;
extern CKeyBind EditCut;
extern CKeyBind EditPaste;
extern CKeyBind EditUndo;
extern CKeyBind FileNew;
extern CKeyBind FileOpen;
extern CKeyBind FilePrint;
extern CKeyBind FileSave;
extern CKeyBind Help;
extern CKeyBind NextPane;
extern CKeyBind PrevPane;
extern CKeyBind View2DXY;
extern CKeyBind View2DXZ;
extern CKeyBind View2DYZ;
extern CKeyBind View3DTex;
extern CKeyBind View3DTexShaded;
	
// --- IDR_MAPDOC --- //
extern CKeyBind CreateObject;
extern CKeyBind ApplyTexture;
extern CKeyBind ClearSelection;
extern CKeyBind CopyWC;
extern CKeyBind CutWC;
extern CKeyBind FindEntities;
extern CKeyBind PasteSpecial;
extern CKeyBind PasteWC;
extern CKeyBind EditProperties;
extern CKeyBind EditRedo;
extern CKeyBind EditReplace;
extern CKeyBind EditToEntity;
extern CKeyBind EditToWorld;
extern CKeyBind FileExportAgain;
extern CKeyBind RunMap;
extern CKeyBind FlipHorizontal;
extern CKeyBind FlipVertical;
extern CKeyBind GoToBrush;
extern CKeyBind HelpTopics;
extern CKeyBind InsertPrefabOriginal;
extern CKeyBind MapCheck;
extern CKeyBind GridHigher;
extern CKeyBind GridLower;
extern CKeyBind SnapToGrid;
extern CKeyBind ModeApplicator;
extern CKeyBind Test;
extern CKeyBind ToggleGroupIgnore;
extern CKeyBind ApplyDecalsTool;
extern CKeyBind BlockTool;
extern CKeyBind CameraTool;
extern CKeyBind ClipperTool;
extern CKeyBind CreatePrefab;
extern CKeyBind DisplaceTool;
extern CKeyBind EntityTool;
extern CKeyBind GroupSelection;
extern CKeyBind HideEntityNames;
extern CKeyBind Magnify;
extern CKeyBind ToolsMorph;
extern CKeyBind ToolsOverlay;
extern CKeyBind ToolsPath;
extern CKeyBind ToolsPointer;
extern CKeyBind SnapToGridIndividual;
extern CKeyBind SnapToGridSelected;
extern CKeyBind OpenSoundBrowser;
extern CKeyBind SplitFace;
extern CKeyBind SubtractSelection;
extern CKeyBind ToggleTextureLock;
extern CKeyBind Transform;
extern CKeyBind Ungroup;
extern CKeyBind QuickHide;
extern CKeyBind QuickHideSelected;
extern CKeyBind QuickHideVisgroup;
extern CKeyBind QuickUnhide;
extern CKeyBind View3DBrighter;
extern CKeyBind View3DDarker;
extern CKeyBind ViewAutosize;
extern CKeyBind ViewCenterOn3DSelection;
extern CKeyBind ViewCenterOnSelection;
extern CKeyBind ViewGrid;
extern CKeyBind ViewMaximizeCurView;
extern CKeyBind ViewShowModelsIn2D;
extern CKeyBind OpenTextureBrowser;
extern CKeyBind VscaleToggle;
extern CKeyBind ToolsSprinkle;
extern CKeyBind OpenModelBrowser;

// --- MapView3D --- //
extern CKeyBind LogicalKeyBack;
extern CKeyBind LogicalKeyBackNml;
extern CKeyBind LogicalKeyBackplaneDecr;
extern CKeyBind LogicalKeyBackplaneIncr;
extern CKeyBind LogicalKeyDown;
extern CKeyBind LogicalKeyForward;
extern CKeyBind LogicalKeyForwardNml;
extern CKeyBind LogicalKeyLeft;
extern CKeyBind LogicalKeyLeftNN;
extern CKeyBind LogicalKeyPitchDown;
extern CKeyBind LogicalKeyPitchUp;
extern CKeyBind LogicalKeyRight;
extern CKeyBind LogicalKeyRightNN;
extern CKeyBind LogicalKeyToggleGrid;
extern CKeyBind LogicalKeyToggleMouse;
extern CKeyBind LogicalKeyUp;
extern CKeyBind LogicalKeyYawLeft;
extern CKeyBind LogcialkeyYawRight;
	
// --- IDR_BLEND_ACCELERATOR --- //
extern CKeyBind EnlargeBrush;
extern CKeyBind ShrinkBrush;
extern CKeyBind SelectTex1;
extern CKeyBind SelectTex2;
extern CKeyBind SelectTex3;
extern CKeyBind SelectTex4;

} // namespace binds 


} // namespace ui 