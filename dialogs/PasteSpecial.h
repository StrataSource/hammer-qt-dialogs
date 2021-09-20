#pragma once

#include <QDialog>

class QLineEdit;
class QCheckBox;
namespace ui
{

class CPasteSpecial : public QDialog
{
	Q_OBJECT
public:

	CPasteSpecial(QWidget* pParent);

	QLineEdit* m_pCopyCount;

	QLineEdit* m_pOffsetX;
	QLineEdit* m_pOffsetY;
	QLineEdit* m_pOffsetZ;

	QLineEdit* m_pRotationX;
	QLineEdit* m_pRotationY;
	QLineEdit* m_pRotationZ;

	QCheckBox* m_pStartAtCenterCheckbox;
	QCheckBox* m_pGroupCopiesCheckbox;
	
	QCheckBox* m_pUniqueNamesCheckbox;
	QCheckBox* m_pAddPrefixCheckbox;
    QLineEdit* m_pNamePrefix;


	int m_readyToCopy;
private slots:
	
	void onFetchOffsetXPressed();
	void onFetchOffsetYPressed();
	void onFetchOffsetZPressed();

	
	void onOkPressed();
	void onCancelPressed();
};

}