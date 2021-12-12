
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

#include "FileSelector.h"

using namespace ui;

CFileSelector::CFileSelector(QWidget* pParent, Options opts) : 
	QWidget(pParent)
{
	m_opts = opts;
	
	m_pBrowseButton = new QPushButton(this);
	m_pBrowseButton->setText("Browse...");
	
	m_pEntryLabel = new QLabel(this);
	m_pEntryLabel->setText("Test text:");
	
	m_pLineEdit = new QLineEdit(this);
	m_pLineEdit->setText("/path/to/default");
	
	auto* pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(m_pEntryLabel, 0, 0);
	pGridLayout->addWidget(m_pLineEdit, 1, 0);
	pGridLayout->addWidget(m_pBrowseButton, 1, 1);

	pGridLayout->setContentsMargins( 0, 0, 0, 0 );
	
	this->setLayout(pGridLayout);
	
	connect(m_pBrowseButton, &QPushButton::pressed, this, &CFileSelector::onBrowsePressed);
}

void CFileSelector::onBrowsePressed()
{
	auto opts = QFileDialog::Option::DontUseNativeDialog;
	
	QString selected;
	if(m_opts == DirsOnly)
		selected = QFileDialog::getExistingDirectory(this, "Open", m_defaultDir);
	else
		selected = QFileDialog::getOpenFileName(this, "Open", m_defaultDir, m_filter, nullptr, opts);
	if(selected.isEmpty())
		return;
	m_pLineEdit->setText(selected);
	emit selectionChanged(selected);
}

