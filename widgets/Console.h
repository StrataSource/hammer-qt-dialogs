//====================================================================//
// 
// Purpose: Defines a bunch of 
//
//====================================================================//
#include <QWidget>
#include <QLabel>
#include <QAbstractListModel>
#include <QDialog>

#include <vector>

namespace ui
{
	
	enum EMessageType
	{
		LS_MESSAGE,
		LS_WARNING,
		LS_ERROR,
		LS_ASSERT,
	};
	
	struct ConsoleMessage_t
	{
		int nChannel;
		int nType;
		QString message;
	};
	
	class ConsoleEntryBar : public QWidget
	{
		Q_OBJECT;
		
	public:
		ConsoleEntryBar(QWidget* parent);
	};
	
	//--------------------------------------------------------------------//
	// Console item model. Stores a list of messages in a circular queue
	//--------------------------------------------------------------------//
	class ConsoleItemModel : public QAbstractTableModel
	{
		Q_OBJECT;
	public:
		//--------------------------------------------------------------------//
		// Column enum
		//--------------------------------------------------------------------//
		enum
		{
			COL_CHANNEL = 0,	// Leftmost column is channel name
			COL_TYPE,			// Middle column is message type (LS_MESSAGE, LS_WARNING, etc.)
			COL_MSG,			// Rightmost column is the actual message text
			NUM_COLS,
		};
	
	public:
		ConsoleItemModel(QObject* parent);
		
		// QAbstractListModel
    	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
		
		
		// Our methods
		void AddMessage(int nChannel, int nSeverity, const char* pMessage);
		int AddChannel(const char* name);
		
	private:
		QString GetChannelName(int nId) const;
		int AdjustColumn(int col);
		
		std::vector<ConsoleMessage_t> m_messages;
		std::vector<QString> m_channels;
		bool m_colStates[NUM_COLS];
	};
	
	//--------------------------------------------------------------------//
	// Embeddable console widget. Can have different input sources. Logging
	// system, pipes, etc.
	//--------------------------------------------------------------------//
	class Console : public QWidget
	{
		Q_OBJECT;
		
		ConsoleItemModel* m_pItemModel = nullptr;
		uint32_t m_nFlags = 0;
	public:
		//--------------------------------------------------------------------//
		// Flags to determine behavior of the console
		//--------------------------------------------------------------------//
		enum
		{
			NO_ENTRY = 0x1,		// No entry bar at the bottom with submit and filters buttons
			NO_CHAN_COL = 0x2,	// No channel column (leftmost)
			NO_TYPE_COL = 0x4,	// No type column (middle)
		};
	
	public:
		Console(QWidget* parent, uint32_t flags);

		ConsoleItemModel& GetItemModel() const { return *m_pItemModel; }
	};
	
	//--------------------------------------------------------------------//
	// Simple console dialog to be used in an external window
	//--------------------------------------------------------------------//
	class ConsoleDialog : public QDialog
	{
		Q_OBJECT;
	public:
		ConsoleDialog(QWidget* parent);
	};
	
}