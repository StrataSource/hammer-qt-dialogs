
#pragma once

#include <QPushButton>
#include <QKeySequence>
#include <QKeySequenceEdit>

namespace ui
{

class CKeyRecorder : public QWidget
{
	Q_OBJECT;
	
	bool m_bRecording = false;
	QKeySequence m_keySeq;
	QKeySequence m_old; // Saves m_keySeq when recording starts 
	QString m_default;
	
	QPushButton* m_pRecorder;
	QPushButton* m_pReset;
	QPushButton* m_pStopRecording;
public:
	CKeyRecorder(QWidget* pParent, const QString& def);
	
	const QKeySequence& GetKeySequence() const { return m_keySeq; };
	
	/**
	 * Reset the key sequence to default 
	 */
	void Reset();
	void SetRecording(bool);
	
protected:
	void keyPressEvent(QKeyEvent* ev) override;
	void keyReleaseEvent(QKeyEvent* ev) override;

signals:
	void keySequenceChanged(QKeySequence seq);
};

}