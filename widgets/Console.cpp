
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

#include "Console.h"

using namespace ui;

constexpr QColor WARNING_COLOR_BG(255, 255, 0);
constexpr QColor WARNING_COLOR_FG(0, 0, 0);
constexpr QColor ERROR_COLOR_BG(255, 0, 0);
constexpr QColor ERROR_COLOR_FG(0, 0, 0);
constexpr QColor ASSERT_COLOR_BG(255, 0, 0);
constexpr QColor ASSERT_COLOR_FG(0, 0, 0);
constexpr QColor DEFAULT_COLOR_BG(50, 50, 50);
constexpr QColor DEFAULT_COLOR_FG(255, 255, 255);

//-----------------------------------------------------------------//
// Convert message type enum to readable string
//-----------------------------------------------------------------//
static QString TypeToString(int type)
{
	switch(type)
	{
	case LS_MESSAGE:
		return "INFO";
	case LS_WARNING:
		return "WARN";
	case LS_ERROR:
		return "ERROR";
	default:
		return "ASSERT";
	}
}

//-----------------------------------------------------------------//
// Returns the bg QColor associated with the logging message type
//-----------------------------------------------------------------//
static QColor ColorFromType(int nType, bool bForeground)
{
	switch(nType)
	{
	case LS_WARNING:
		return bForeground ? WARNING_COLOR_FG : WARNING_COLOR_BG;
	case LS_ERROR:
		return bForeground ? ERROR_COLOR_FG : ERROR_COLOR_BG;
	case LS_ASSERT:
		return bForeground ? ASSERT_COLOR_FG : ASSERT_COLOR_BG;
	default:
		return bForeground ? DEFAULT_COLOR_FG : DEFAULT_COLOR_BG;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// ConsoleEntryBar implementation
//////////////////////////////////////////////////////////////////////////////////////


ConsoleEntryBar::ConsoleEntryBar(QWidget* parent) :
	QWidget(parent)
{
	auto* pLayout = new QHBoxLayout(this);
	
	//
	// Left "filters" configuration button
	//
	auto* pFiltersBtn = new QPushButton(this);
	pFiltersBtn->setText(tr("Filters"));
	pFiltersBtn->setToolTip(tr("Configure message filters"));
	
	pLayout->addWidget(pFiltersBtn);
	
	//
	// Actual text entry bar
	//
	auto* pTextEntry = new QLineEdit(this);
	pTextEntry->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum));
	pTextEntry->setToolTip(tr("Command to execute"));

	pLayout->addWidget(pTextEntry);
	
	//
	// Cheesy submit button
	//
	auto* pSubmitBtn = new QPushButton(this);
	pSubmitBtn->setText(tr("Submit"));
	pSubmitBtn->setToolTip(tr("Submit entered command"));
	
	pLayout->addWidget(pSubmitBtn);
}


//////////////////////////////////////////////////////////////////////////////////////
// ConsoleItemModel Implementation
//////////////////////////////////////////////////////////////////////////////////////

ConsoleItemModel::ConsoleItemModel(QObject* parent) : 
	QAbstractTableModel(parent)
{
	for(int i = 0; i < NUM_COLS; i++)
		m_colStates[i] = true;
}

int ConsoleItemModel::rowCount(const QModelIndex &parent) const
{
	return m_messages.size();
}

int ConsoleItemModel::columnCount(const QModelIndex &parent) const
{
	return NUM_COLS;
}

QVariant ConsoleItemModel::data(const QModelIndex &index, int role) const
{
	if (index.row() >= m_messages.size())
		return QVariant();
	auto& msg = m_messages[index.row()];
	
	// Handle actual data entries (channel, type, message)	
	if (role == Qt::DisplayRole)
	{
		switch(index.column())
		{
		case COL_CHANNEL: 
			return GetChannelName(msg.nChannel);
		case COL_TYPE:
			return TypeToString(msg.nType);
		default:
			return msg.message;
		}
	}
	// Handle background coloration
	else if (role == Qt::BackgroundRole)
	{
		if ( index.column() == COL_TYPE )
			return ColorFromType(msg.nType, false);
	}
	// Handle foreground coloration
	else if (role == Qt::ForegroundRole)
	{
		if (index.column() == COL_TYPE)
			return ColorFromType(msg.nType, true);
	}
	return QVariant();
}

QVariant ConsoleItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical)
	{
		switch(section)
		{
		case COL_CHANNEL:
			return QVariant("Channel");
		case COL_TYPE:
			return QVariant("Severity");
		default:
			return QVariant("Message");
		}
	}
	return QVariant();
}

QString ConsoleItemModel::GetChannelName(int nId) const
{
	if ( m_channels.size() >= nId )
		return "";
	return m_channels[nId];
}


void ConsoleItemModel::AddMessage(int nChannel, int nSeverity, const char* pMessage)
{
	beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
	m_messages.push_back({
		nChannel,
		nSeverity,
		QString(pMessage)
	});
	endInsertRows();
}

int ConsoleItemModel::AddChannel(const char* name)
{
	m_channels.push_back(name);
	return m_channels.size()-1;
}

//-----------------------------------------------------------------//
// Adjust the provided column index based on the visually disabled
// columns.
//-----------------------------------------------------------------//
int ConsoleItemModel::AdjustColumn(int col)
{
	// FIXME
	int i, j = 0;
	for(i = 0; i < NUM_COLS && col != i; i++)
		if (!m_colStates[i])
			j++;
	return col - j;
}

//////////////////////////////////////////////////////////////////////////////////////
// Console widget implementation
//////////////////////////////////////////////////////////////////////////////////////

Console::Console(QWidget* parent, uint32_t flags) :
	QWidget(parent)
{
	m_nFlags = flags;
	m_pItemModel = new ConsoleItemModel(this);
	
	auto* pLayout = new QVBoxLayout(this);
	
	//
	// Create a list view for our message data
	// 
	auto* pListView = new QTableView(this);
	pListView->setModel(m_pItemModel);
	pListView->verticalHeader()->hide();						// Hide the vertical left header, don't need it.
	pListView->horizontalHeader()->setStretchLastSection(true); // Automatically expand the message column to max
	
	pLayout->addWidget(pListView);
	
	// Entry bar
	auto* pEntry = new ConsoleEntryBar(this);
	pLayout->addWidget(pEntry);
}

//////////////////////////////////////////////////////////////////////////////////////
// Console dialog implementation
//////////////////////////////////////////////////////////////////////////////////////

// Very simple wrapper around the embeddable console widget
ConsoleDialog::ConsoleDialog(QWidget* parent) : 
	QDialog(parent)
{
	auto* pConsole = new Console(this, 0);
	auto* pLayout = new QVBoxLayout(this);
	pLayout->addWidget(pConsole);
	
	auto nEngChan = pConsole->GetItemModel().AddChannel("engine");
	auto nBlobChan = pConsole->GetItemModel().AddChannel("blobulator");
	
	pConsole->GetItemModel().AddMessage(nEngChan, LS_MESSAGE, "Loaded client.dll");
	pConsole->GetItemModel().AddMessage(nEngChan, LS_MESSAGE, "Loaded server.dll");
	pConsole->GetItemModel().AddMessage(nBlobChan, LS_WARNING, "Performance warning! Skipping some fragments!");

	this->setMinimumSize(sizeHint());
}
