
#include <QKeySequence>
#include <QKeySequenceEdit>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QLabel>
#include <QSplitter>
#include <QFileDialog>
#include <QMessageBox>

#include "KeyBinds.h"
#include "Utils.h"

using namespace ui;

static QList<CKeyBind*>& KeyBindList()
{
	static QList<CKeyBind*> list;
	return list;
}

//-----------------------------------------------------------------//


CKeyBindingDialog::CKeyBindingDialog(QWidget* pParent) :
	QDialog(pParent)
{
	setWindowTitle(tr("Key Binding Editor"));
	
	auto* pLayout = new QVBoxLayout(this);
	auto* pTabs = new QTabWidget(this);
	
	this->setMinimumSize(750, 400);
	
	// Lambda to create a page of bindings
	auto CreatePage = [&,this](const QString& prefix, const QString& tabName) {
		auto* pFramePageMain = new QWidget(this); // Main widget
		auto* pFramePage = new QScrollArea(this);
		auto* pFrameWidget = new QWidget(this);
		auto* pFrameStacker = new QVBoxLayout(this); // Layout for the Scroll area + pFrameButtons
		auto* pFrameButtons = new QHBoxLayout(this); // Layout for the buttons at the very bottom of the dialog
		auto* pFrameGrid = new QGridLayout(this);
		
		int row = 0;
		for(auto& e : KeyBindList())
		{
			if(!e->m_name.startsWith(prefix))
				continue;
			auto* pLabel = new QLabel(this);
			pLabel->setText(e->m_displayName);
			
			auto* pDesc = new QLabel(this);
			pDesc->setText(tr(e->m_desc));
			
			auto* pBinder = new CKeyRecorder(this, e->m_defaultBind);
			m_recorders.push_back(pBinder);
			connect(pBinder, &CKeyRecorder::keySequenceChanged, [
				this,
				pBinder,
				bindInfo = e] (const QKeySequence& seq) {
				// Notify ourselves of keybind change
				KeyBindMgr().NotifyChangeKeyBind(bindInfo);
				// Mark ourselves as dirty
				m_bDirty = true;
			});
			connect(pBinder, &CKeyRecorder::keySequenceChanged, e, &CKeyBind::keybindChanged);
			
			pFrameGrid->addWidget(pLabel, row, 0);
			pFrameGrid->addWidget(pBinder, row, 1);
			pFrameGrid->addWidget(pDesc, row, 2);			
			row++;
		}
		pFrameGrid->setVerticalSpacing(0);
		pFrameGrid->setSpacing(0);
		pFrameGrid->setHorizontalSpacing(0);
		
		pFrameWidget->setLayout(pFrameGrid);
		pFramePage->setWidget(pFrameWidget);
		
		// Buttons on the bottom
		auto* pCancelBtn = new QPushButton(this);
		pCancelBtn->setText(tr("Cancel"));
		pCancelBtn->setFixedSize(pCancelBtn->sizeHint());
		
		auto* pSaveBtn = new QPushButton(this);
		pSaveBtn->setText(tr("Apply"));
		pSaveBtn->setFixedSize(pSaveBtn->sizeHint());
		
		auto* pSaveAsBtn = new QPushButton(this);
		pSaveAsBtn->setText(tr("Save As"));
		pSaveAsBtn->setFixedSize(pSaveAsBtn->sizeHint());
		
		auto* pLoadBtn = new QPushButton(this);
		pLoadBtn->setText(tr("Load"));
		pLoadBtn->setFixedSize(pLoadBtn->sizeHint());
		
		auto* pUseDefaultsBtn = new QPushButton(this);
		pUseDefaultsBtn->setText(tr("Use defaults"));
		pUseDefaultsBtn->setFixedSize(pUseDefaultsBtn->sizeHint());
		
		// Add the buttons
		pFrameButtons->setAlignment(Qt::AlignRight);
		pFrameButtons->addWidget(pUseDefaultsBtn);
		pFrameButtons->addWidget(pCancelBtn);
		pFrameButtons->addWidget(pLoadBtn);
		pFrameButtons->addWidget(pSaveAsBtn);
		pFrameButtons->addWidget(pSaveBtn);
		
		// Connect button events 
		connect(pUseDefaultsBtn, &QPushButton::released, this, &CKeyBindingDialog::onUseDefaults);
		connect(pCancelBtn, &QPushButton::released, this, &CKeyBindingDialog::onCancel);
		connect(pLoadBtn, &QPushButton::released, this, &CKeyBindingDialog::onLoad);
		connect(pSaveAsBtn, &QPushButton::released, this, &CKeyBindingDialog::onSaveAs);
		connect(pSaveBtn, &QPushButton::released, this, &CKeyBindingDialog::onSave);
		
		pFrameStacker->addWidget(pFramePage);
		pFrameStacker->addLayout(pFrameButtons);
		
		// Set layout and add tab finally! 
		pFramePageMain->setLayout(pFrameStacker);
		pTabs->addTab(pFramePageMain, tabName);
	};
	
	CreatePage("IDR_MAINFRAME", tr("Main Frame"));
	CreatePage("IDR_MAPDOC", tr("Map Editing"));
	CreatePage("MapView3D", tr("Map View 3D"));
	CreatePage("IDR_BLEND_ACCELERATOR", tr("Face Edit"));
	
	pLayout->addWidget(pTabs);
	this->setLayout(pLayout);
}

void CKeyBindingDialog::onSaveAs()
{
	static QString prevDir = QDir::currentPath();
	
	auto fileToSave = QFileDialog::getSaveFileName(this, "Save Key Bindings", prevDir,
		"Configuration Files (*.cfg)");
	
	if(fileToSave.isEmpty())
	{
		return;
	}
	
	prevDir = fileToSave;
	StripFileName(prevDir);
	KeyBindMgr().SaveToFile(fileToSave.toUtf8().data());
	m_bDirty = false; // QT_TODO: Should this be marked as dirty still? It's possible that the user is just trying to export settings.
}

void CKeyBindingDialog::onSave()
{
	m_bDirty = false;
	KeyBindMgr().SaveToFile(KEYBINDS_FILE);
}

void CKeyBindingDialog::onLoad()
{
	static QString prevDir = QDir::currentPath();
	
	auto fileToLoad = QFileDialog::getOpenFileName(this, "Load Key Bindings From File", prevDir,
		"Configuration Files (*.cfg)");
		
	if(fileToLoad.isEmpty())
	{
		return;
	}
	
	prevDir = fileToLoad;
	StripFileName(prevDir);
	KeyBindMgr().LoadFromFile(fileToLoad.toUtf8().data());
}

void CKeyBindingDialog::onCancel()
{
	if(m_bDirty)
	{
		auto choice = QMessageBox::question(this, tr("Save changes?"), tr("You have unsaved changes. Would you like to save your key bindings?"),
			QMessageBox::Save, QMessageBox::Cancel, QMessageBox::No);
		switch(choice)
		{
			case QMessageBox::Save:
				this->onSave();
				m_bDirty = false;
				break;
			case QMessageBox::Cancel:
				return;
			default:
				KeyBindMgr().LoadFromFile(KEYBINDS_FILE); // QT_TODO: This can probably be done better. But yeah, if the user doesn't save settings and wants to keep the old, 
														  // 			it'll be saved in the keybinds config already, so just load it.
				break;
		}
	}
	
	this->close();
}

void CKeyBindingDialog::onUseDefaults()
{
	if(QMessageBox::question(this, tr("Confirm reset to default"), tr("Are you sure you want to reset your key bindings to default?\n This operation will ERASE any custom key bindings!"), 
		QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Cancel)
	{
		return;
	}
	
	// Reset the actual binds
	for(auto& b : KeyBindList())
	{
		b->Reset();
	}
	
	// Reset the recorder values
	for(auto& r : m_recorders)
	{
		r->Reset();
	}
}

//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
CKeyBind::CKeyBind(const QString& bindingName, const char* displayName, const char* defaultBind, const char* description) :
	QObject(nullptr)
{
	m_defaultBind = defaultBind;
	m_desc = description;
	m_displayName = displayName;
	m_name = bindingName;
	
	KeyBindList().push_back(this);
}

const QKeySequence& CKeyBind::Get() const
{
	return m_seq;
}

void CKeyBind::Reset()
{
	m_seq = QKeySequence::fromString(m_defaultBind);
	emit keybindChanged(m_seq);
}

void CKeyBind::Set(const QKeySequence& seq)
{
	m_seq = seq;
	emit keybindChanged(m_seq);
}
//-----------------------------------------------------------------//

CKeyBindManager& ui::KeyBindMgr()
{
	static CKeyBindManager mgr;
	return mgr;
}

void CKeyBindManager::ResetAllBinds()
{
	for(auto& b : KeyBindList())
	{
		b->Reset();
	}
}

void CKeyBindManager::NotifyChangeKeyBind(CKeyBind* pBind)
{
	// QT_TODO: Backend hammer integration
}

void CKeyBindManager::LoadFromFile(const char* path)
{
	// QT_TODO: Backend hammer integration
}

void CKeyBindManager::SaveToFile(const char* path)
{
	// QT_TODO: Backend hammer integration
}

CKeyBind* CKeyBindManager::FindBinding(const char* bindName)
{
	for(auto& b : KeyBindList())
	{
		if(b->GetName() == bindName)
			return b;
	}
	return nullptr;
}



//-----------------------------------------------------------------//
// Purpose: Massive huge list of keybinds
//-----------------------------------------------------------------//
namespace ui::binds
{

// --- IDR_MAINFRAME --- //
CKeyBind ContextHelp		("IDR_MAINFRAME::ID_CONTEXT_HELP",		 			"Context Help", 		"Shift+F1", "Shows help info");
CKeyBind EditCut			("IDR_MAINFRAME::ID_EDIT_CUT",						"Cut", 					"Ctrl+X", "Cut description");
CKeyBind EditPaste			("IDR_MAINFRAME::ID_EDIT_PASTE",					"Paste", 				"Ctrl+V", "Paste description");
CKeyBind EditUndo			("IDR_MAINFRAME::ID_EDIT_UNDO",					"Undo", 				"Ctrl+Z", "Undo description");
CKeyBind FileNew			("IDR_MAINFRAME::ID_FILE_NEW",		 				"New File", 			"Ctrl+N", "New file description");
CKeyBind FileOpen			("IDR_MAINFRAME::ID_FILE_OPEN",		 			"Open File", 			"Ctrl+O", "Open file description");
CKeyBind FilePrint			("IDR_MAINFRAME::ID_FILE_PRINT",		 			"Print File", 			"Ctrl+P", "Print file description");
CKeyBind FileSave			("IDR_MAINFRAME::ID_FILE_SAVE",		 			"Save File", 			"Ctrl+S", "Save file description");
CKeyBind Help				("IDR_MAINFRAME::ID_HELP_FINDER",		 			"Help", 				"F1", "Help finder description");
CKeyBind NextPane			("IDR_MAINFRAME::ID_NEXT_PANE",		 			"Next Pane", 			"F7", "Next pane description");
CKeyBind PrevPane			("IDR_MAINFRAME::ID_PREV_PANE",		 			"Previous Pane", 		"Shift+F7", "Previous pane description");
CKeyBind View2DXY			("IDR_MAINFRAME::ID_VIEW_2DXY",		 			"View mode 2D-XY", 		"F2", "View mode 2D XY description");
CKeyBind View2DXZ			("IDR_MAINFRAME::ID_VIEW_2DXZ",		 			"View mode 2D-XZ", 		"F3", "View mode 2D XZ description");
CKeyBind View2DYZ			("IDR_MAINFRAME::ID_VIEW_2DYZ",		 			"View mode 2D-YZ", 		"F4", "View mode 2D YZ description");
CKeyBind View3DTex			("IDR_MAINFRAME::ID_VIEW_3DTEXTURED",		 		"View mode 3D textured","F5", "View mode 3d textured description");
CKeyBind View3DTexShaded	("IDR_MAINFRAME::ID_VIEW_3DTEXTURED_SHADED",		"View mode 3D shaded", "Shift+F5", "View mode 3d textured shaded description");
	
// --- IDR_MAPDOC --- //
CKeyBind CreateObject				("IDR_MAPDOC::ID_CREATEOBJECT", "Create Object", "Alt+C", "CreateObject description");
CKeyBind ApplyTexture				("IDR_MAPDOC::ID_EDIT_APPLYTEXTURE", "Apply Texture", "Shift+T", "ApplyTexture description");
CKeyBind ClearSelection				("IDR_MAPDOC::ID_EDIT_CLEARSELECTION", "Clear Selection", "Shift+Q", "ClearSelection description");
CKeyBind CopyWC						("IDR_MAPDOC::ID_EDIT_COPYWC", "Copy", "Ctrl+C", "CopyWC description");
CKeyBind CutWC						("IDR_MAPDOC::ID_EDIT_CUTWC", "Cut", "Ctrl+X", "CutWC description");
CKeyBind FindEntities				("IDR_MAPDOC::ID_EDIT_FINDENTITIES", "Find Entities", "Shift+Ctrl+F", "FindEntities description");
CKeyBind PasteSpecial				("IDR_MAPDOC::ID_EDIT_PASTESPECIAL", "Paste Special", "Shift+Ctrl+V", "PasteSpecial description");
CKeyBind PasteWC					("IDR_MAPDOC::ID_EDIT_PASTEWC", "Paste", "Ctrl+V", "PasteWC description");
CKeyBind EditProperties				("IDR_MAPDOC::ID_EDIT_PROPERTIES", "Edit Properties", "Alt+Enter", "EditProperties description");
CKeyBind EditRedo					("IDR_MAPDOC::ID_EDIT_REDO", "Redo", "Ctrl+Y", "EditRedo description");
CKeyBind EditReplace				("IDR_MAPDOC::ID_EDIT_REPLACE", "Edit Replace", "Shift+Ctrl+R", "EditReplace description");
CKeyBind EditToEntity				("IDR_MAPDOC::ID_EDIT_TOENTITY", "To Entity", "Ctrl+T", "EditToEntity description");
CKeyBind EditToWorld				("IDR_MAPDOC::ID_EDIT_TOWORLD", "To World", "Shift+Ctrl+W", "EditToWorld description");
CKeyBind FileExportAgain			("IDR_MAPDOC::ID_FILE_EXPORTAGAIN", "Export File Again", "Alt+B", "FileExportAgain description");
CKeyBind RunMap						("IDR_MAPDOC::ID_FILE_RUNMAP", "Run Map", "F9", "RunMap description");
CKeyBind FlipHorizontal				("IDR_MAPDOC::ID_FLIP_HORIZONTAL", "Flip Horizontal", "Ctrl+L", "FlipHorizontal description");
CKeyBind FlipVertical				("IDR_MAPDOC::ID_FLIP_VERTICAL", "Flip Vertical", "Ctrl+I", "FlipVertical description");
CKeyBind GoToBrush					("IDR_MAPDOC::ID_GOTO_BRUSH", "Go To Brush", "Shift+Ctrl+G", "GoToBrush description");
CKeyBind HelpTopics					("IDR_MAPDOC::ID_HELP_TOPICS", "Help Topics", "F1", "HelpTopics description");
CKeyBind InsertPrefabOriginal		("IDR_MAPDOC::ID_INSERTPREFAB_ORIGINAL", "Insert Prefab", "Shift+Alt+C", "InsertPrefabOriginal description");
CKeyBind MapCheck					("IDR_MAPDOC::ID_MAP_CHECK", "Map Check", "Alt+P", "MapCheck description");
CKeyBind GridHigher					("IDR_MAPDOC::ID_MAP_GRIDHIGHER", "Grid Higher", "]", "GridHigher description");
CKeyBind GridLower					("IDR_MAPDOC::ID_MAP_GRIDLOWER", "Grid Lower", "[", "GridLower description");
CKeyBind SnapToGrid					("IDR_MAPDOC::ID_MAP_SNAPTOGRID", "Snap To Grid", "Shift+W", "SnapToGrid description");
CKeyBind ModeApplicator				("IDR_MAPDOC::ID_MODE_APPLICATOR", "Mode Applicator", "Shift+A", "ModeApplicator description");
CKeyBind Test						("IDR_MAPDOC::ID_TEST", "Test", "Shift+Alt+T", "Test description");
CKeyBind ToggleGroupIgnore			("IDR_MAPDOC::ID_TOGGLE_GROUPIGNORE", "Toggle Group Ignore", "Ctrl+W", "ToggleGroupIgnore description");
CKeyBind ApplyDecalsTool			("IDR_MAPDOC::ID_TOOLS_APPLYDECALS", "Apply Decals Tool", "Shift+D", "ApplyDecalsTool description");
CKeyBind BlockTool					("IDR_MAPDOC::ID_TOOLS_BLOCK", "Block Tool", "Shift+B", "BlockTool description");
CKeyBind CameraTool					("IDR_MAPDOC::ID_TOOLS_CAMERA", "Camera Tool", "Shift+C", "CameraTool description");
CKeyBind ClipperTool				("IDR_MAPDOC::ID_TOOLS_CLIPPER", "Clipper Tool", "Shift+X", "ClipperTool description");
CKeyBind CreatePrefab				("IDR_MAPDOC::ID_TOOLS_CREATEPREFAB", "Create Prefab", "Ctrl+R", "CreatePrefab description");
CKeyBind DisplaceTool				("IDR_MAPDOC::ID_TOOLS_DISPLACE", "Displace Tool", "Ctrl+D", "DisplaceTool description");
CKeyBind EntityTool					("IDR_MAPDOC::ID_TOOLS_ENTITY", "Entity Tool", "Shift+E", "EntityTool description");
CKeyBind GroupSelection				("IDR_MAPDOC::ID_TOOLS_GROUP", "Group Selection", "Ctrl+G", "GroupSelection description");
CKeyBind HideEntityNames			("IDR_MAPDOC::ID_TOOLS_HIDE_ENTITY_NAMES", "Hide Entity Names", "Shift+Ctrl+N", "HideEntityNames description");
CKeyBind Magnify					("IDR_MAPDOC::ID_TOOLS_MAGNIFY", "Magnify", "Shift+G", "Magnify description");
CKeyBind ToolsMorph					("IDR_MAPDOC::ID_TOOLS_MORPH", "Tools Morph", "Shift+V", "ToolsMorph description");
CKeyBind ToolsOverlay				("IDR_MAPDOC::ID_TOOLS_OVERLAY", "Tools Overlay", "Shift+O", "ToolsOverlay description");
CKeyBind ToolsPath					("IDR_MAPDOC::ID_TOOLS_PATH", "Tools Path", "Shift+P", "ToolsPath description");
CKeyBind ToolsPointer				("IDR_MAPDOC::ID_TOOLS_POINTER", "Tools Pointer", "Shift+S", "ToolsPointer description");
CKeyBind SnapToGridIndividual		("IDR_MAPDOC::ID_TOOLS_SNAP_SELECTED_TO_GRID_INDIVIDUALLY", "Snap To Grid Individual", "Shift+Ctrl+B", "SnapToGridIndividual description");
CKeyBind SnapToGridSelected			("IDR_MAPDOC::ID_TOOLS_SNAPSELECTEDTOGRID", "Snap To Grid Selected", "Ctrl+B", "SnapToGridSelected description");
CKeyBind OpenSoundBrowser			("IDR_MAPDOC::ID_TOOLS_SOUND_BROWSER", "Open Sound Browser", "Shift+Ctrl+S", "OpenSoundBrowser description");
CKeyBind SplitFace					("IDR_MAPDOC::ID_TOOLS_SPLITFACE", "Split Face", "Ctrl+F", "SplitFace description");
CKeyBind SubtractSelection			("IDR_MAPDOC::ID_TOOLS_SUBTRACTSELECTION", "Subtract Selection", "Shift+Ctrl+C", "SubtractSelection description");
CKeyBind ToggleTextureLock			("IDR_MAPDOC::ID_TOOLS_TOGGLETEXLOCK", "Toggle Texture Lock", "Shift+L", "ToggleTextureLock description");
CKeyBind Transform					("IDR_MAPDOC::ID_TOOLS_TRANSFORM", "Transform", "Ctrl+M", "Transform description");
CKeyBind Ungroup					("IDR_MAPDOC::ID_TOOLS_UNGROUP", "Ungroup", "Ctrl+U", "Ungroup description");
CKeyBind QuickHide					("IDR_MAPDOC::ID_VIEW_QUICKHIDE", "Quick Hide", "H", "QuickHide description");
CKeyBind QuickHideSelected			("IDR_MAPDOC::ID_VIEW_QUICKHIDEUNSELECTED", "Quick Hide Selected", "Ctrl+H", "QuickHideSelected description");
CKeyBind QuickHideVisgroup			("IDR_MAPDOC::ID_VIEW_QUICKHIDEVISGROUP", "Quick Hide Visgroup", "", "QuickHideVisgroup description");
CKeyBind QuickUnhide				("IDR_MAPDOC::ID_VIEW_QUICKUNHIDE", "Quick Unhide", "U", "QuickUnhide description");
CKeyBind View3DBrighter				("IDR_MAPDOC::ID_VIEW3D_BRIGHTER", "View 3D Brighter", "Ctrl+Home", "View3DBrighter description");
CKeyBind View3DDarker				("IDR_MAPDOC::ID_VIEW3D_DARKER", "View 3D Darker", "Ctrl+End", "View3DDarker description");
CKeyBind ViewAutosize				("IDR_MAPDOC::ID_VIEW_AUTOSIZE4", "View Autosize", "Ctrl+A", "ViewAutosize description");
CKeyBind ViewCenterOn3DSelection	("IDR_MAPDOC::ID_VIEW_CENTER3DVIEWSONSELECTION", "Center View On 3D Selection", "Shift+Ctrl+E", "ViewCenterOn3DSelection description");
CKeyBind ViewCenterOnSelection		("IDR_MAPDOC::ID_VIEW_CENTERONSELECTION", "Center View On Selection", "Ctrl+E", "ViewCenterOnSelection description");
CKeyBind ViewGrid					("IDR_MAPDOC::ID_VIEW_GRID", "ViewGrid", "Shift+R", "View Grid description");
CKeyBind ViewMaximizeCurView		("IDR_MAPDOC::ID_VIEW_MAXIMIZERESTOREACTIVEVIEW", "Maximize Current View", "Shift+Z", "ViewMaximizeCurView description");
CKeyBind ViewShowModelsIn2D			("IDR_MAPDOC::ID_VIEW_SHOWMODELSIN2D", "Show Models In 2D", "Shift+M", "ViewShowModelsIn2D description");
CKeyBind OpenTextureBrowser			("IDR_MAPDOC::ID_VIEW_TEXTUREBROWSER", "Open Texture Browser", "Alt+F8", "OpenTextureBrowser description");
CKeyBind VscaleToggle				("IDR_MAPDOC::ID_VSCALE_TOGGLE", "Vertex Scale Toggle", "Alt+E", "Vertex Scale Toggle description");
CKeyBind ToolsSprinkle				("IDR_MAPDOC::ID_TOOLS_SPRINKLE", "Sprinkle Tool", "", "ToolsSprinkle description");
CKeyBind OpenModelBrowser			("IDR_MAPDOC::ID_TOOLS_MODEL_BROWSER", "Open Model Browser", "", "OpenModelBrowser description");

// --- MapView3D --- //
CKeyBind LogicalKeyForward		("MapView3D::LOGICAL_KEY_FORWARD", "Move Forward", "W", "Moves the 3D camerca forwards");
CKeyBind LogicalKeyForwardNml	("MapView3D::LOGICAL_KEY_FORWARD_NML", "Move Forward", "D", "Moves the 3D camera forwards when mouse look is disabled");
CKeyBind LogicalKeyBack			("MapView3D::LOGICAL_KEY_BACK", "Move Backwards", "S", "Moves the 3D camera backwards");
CKeyBind LogicalKeyBackNml		("MapView3D::LOGICAL_KEY_BACK_NML", "Move Backwards", "C", "Moves the 3D camera backwards when mouse look is disabled");
CKeyBind LogicalKeyLeft			("MapView3D::LOGICAL_KEY_LEFT", "Move Left", "A", "Moves the 3D camera left");
CKeyBind LogicalKeyLeftNN		("MapView3D::LOGICAL_KEY_LEFT_NN", "Move Left", "Shift+Left", "Moves the 3D camera left when nudging 2D views is disabled");
CKeyBind LogicalKeyRight		("MapView3D::LOGICAL_KEY_RIGHT", "Move Right", "D", "Moves 3D camera right");
CKeyBind LogicalKeyRightNN		("MapView3D::LOGICAL_KEY_RIGHT_NN", "Move Right", "Shift+Right", "Moves the 3D camera right when nudging 2D views is disabled");
CKeyBind LogicalKeyDown			("MapView3D::LOGICAL_KEY_DOWN", "Move Down", "Shift+Down", "Moves the 3d camera down");
CKeyBind LogicalKeyPitchDown	("MapView3D::LOGICAL_KEY_PITCH_DOWN", "Look Down", "Down", "Points the 3D camera down");
CKeyBind LogicalKeyPitchUp		("MapView3D::LOGICAL_KEY_PITCH_UP", "Look Up", "Up", "Points the 3D camera up");
CKeyBind LogicalKeyUp			("MapView3D::LOGICAL_KEY_UP", "Move Camera Up", "Shift+Up", "Moves the 3D camera upwards");
CKeyBind LogicalKeyYawLeft		("MapView3D::LOGICAL_KEY_YAW_LEFT", "Turn Left", "Left", "Turns the 3D camera left");
CKeyBind LogcialkeyYawRight		("MapView3D::LOGICAL_KEY_YAW_RIGHT", "Turn Right", "Right", "Turns the 3D camera right");
CKeyBind LogicalKeyToggleGrid	("MapView3D::LOGICAL_KEY_TOGGLE_GRID", "Toggle 3D Grid", "P", "Toggles the 3D Grid");
CKeyBind LogicalKeyToggleMouse	("MapView3D::LOGICAL_KEY_TOGGLE_MOUSELOOK", "Toggle Mouse Look", "Z", "Toggles mouse capture and look");
CKeyBind LogicalKeyBackplaneDecr("MapView3D::LOGICAL_KEY_BACKPLANE_DECR", "Move backplane closer", "1", "Moves the 3D clipping plane closer");
CKeyBind LogicalKeyBackplaneIncr("MapView3D::LOGICAL_KEY_BACKPLANE_INCR", "Move backplane further", "2", "Moves the 3d clipping plane further away");
	
// --- IDR_BLEND_ACCELERATOR --- //
CKeyBind EnlargeBrush	("IDR_BLEND_ACCELERATOR::ID_BLEND_ENLARGE_BRUSH", "Enlarge Grid", "]", "Increases grid size");
CKeyBind ShrinkBrush	("IDR_BLEND_ACCELERATOR::ID_BLEND_SHRINK_BRUSH", "Shrink Grid", "[", "Decreases grid size");
CKeyBind SelectTex1		("IDR_BLEND_ACCELERATOR::ID_BLEND_SELECT_TEXTURE_1", "Select Texture 1", "1", "Selects texture 1");
CKeyBind SelectTex2		("IDR_BLEND_ACCELERATOR::ID_BLEND_SELECT_TEXTURE_2", "Select Texture 2", "2", "Selects texture 2");
CKeyBind SelectTex3		("IDR_BLEND_ACCELERATOR::ID_BLEND_SELECT_TEXTURE_3", "Select Texture 3", "3", "Selects texture 3");
CKeyBind SelectTex4		("IDR_BLEND_ACCELERATOR::ID_BLEND_SELECT_TEXTURE_4", "Select Texture 4", "4", "Selects texture 4");

} // namespace ui::binds