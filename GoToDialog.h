
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

namespace ui
{
	
//-----------------------------------------------------------------//
// The Go to coord dialog, usually used for debugging compile issues
//-----------------------------------------------------------------//
class CGoToCoordDialog : public QDialog
{
	Q_OBJECT;
public:
	QPushButton* m_pGo;
	QPushButton* m_pCancel;
	QLineEdit* m_pXYZ;
	QLineEdit* m_pAngles;

	CGoToCoordDialog(QWidget* pParent);
	
private slots:
	void onGoPressed();
	void onCancelPressed();
};

//-----------------------------------------------------------------//
// The Go to brush dialog, usually used for debugging 
//-----------------------------------------------------------------//
class CGoToBrushDialog : public QDialog
{
	Q_OBJECT;
public:
	QLineEdit* m_pBrush;
	QPushButton* m_pGo;
	QPushButton* m_pCancel;

	CGoToBrushDialog(QWidget* pParent);
	
private slots:
	void onGoPressed();
	void onCancelPressed();
};
	
}