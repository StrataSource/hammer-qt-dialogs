
#pragma once

#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>

namespace ui
{


class CFileSelector : public QWidget
{
	Q_OBJECT
	
	QLabel* m_pEntryLabel;
	QPushButton* m_pBrowseButton;
	QLineEdit* m_pLineEdit;
	
	QString m_defaultDir;
	QString m_filter;
public:
	
	enum Options
	{
		DirsOnly
	};
	
private:
	Options m_opts;

public:
	CFileSelector(QWidget* pParent, Options opts);
	
	void setLabelText(const QString& text);
	
	QLineEdit& getLineEdit() { return *m_pLineEdit; };
	QLabel& getLabel() { return *m_pEntryLabel; };
	QPushButton& getButton() { return *m_pBrowseButton; };
	
	void setDefaultDir(const QString& str) { m_defaultDir = str; };
	void setFilter(const QString& str) { m_filter = str; };
private slots:
	void onBrowsePressed();
	
signals:
	void selectionChanged(const QString& newPath);
};

}