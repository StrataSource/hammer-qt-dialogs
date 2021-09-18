
#include <QPushButton>
#include <QKeySequenceEdit>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QStyle>

#include "KeyRecorder.h"

using namespace ui;

CKeyRecorder::CKeyRecorder(QWidget* pParent, const QString& def) :
	QWidget(pParent)
{
	m_default = def;
	
	auto* pLayout = new QHBoxLayout(this);
	
	// Recorder button
	m_pRecorder = new QPushButton(this);
	m_pRecorder->setText("");
	m_pRecorder->setAutoDefault(false);
	m_pRecorder->setDefault(false);
	m_pRecorder->setCheckable(true);
	m_pRecorder->setChecked(false);
	m_pRecorder->setMinimumWidth(100);
	
	// Stop recording button
	m_pStopRecording = new QPushButton(this);
	m_pStopRecording->setIcon(style()->standardIcon(QStyle::SP_DialogNoButton));
	m_pStopRecording->setToolTip(tr("Stop recording"));
	m_pStopRecording->setFixedSize(m_pStopRecording->sizeHint());
	
	// Reset button
	m_pReset = new QPushButton(this);
	m_pReset->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
	m_pReset->setToolTip(tr("Reset binding to default"));
	m_pReset->setFixedSize(m_pReset->sizeHint());
	
	pLayout->addWidget(m_pRecorder);
	pLayout->addWidget(m_pStopRecording);
	pLayout->addWidget(m_pReset);
	
	this->setLayout(pLayout);
	
	// Run a reset to get the correct text 
	this->Reset();
	
	connect(m_pRecorder, &QPushButton::pressed, [this]() {
		this->m_old = this->m_keySeq;
		SetRecording(true);
	});
	
	connect(m_pStopRecording, &QPushButton::pressed, [this](){
		if(!this->m_bRecording)
		{
			SetRecording(true);
			return;
		}
		
		// Determine if we need ot reset to the previous recording
		bool needsReset = false;
		for(int i = 0; i < this->m_keySeq.count(); i++) {
			if((this->m_keySeq[i] & ~Qt::KeyboardModifierMask) == 0 || this->m_keySeq[i] == Qt::Key_unknown)
				needsReset = true;
		}
		
		// Reset if needed
		if(needsReset) 
		{
			this->m_keySeq = this->m_old;
			this->m_pRecorder->setText(this->m_keySeq.toString());
		}
		SetRecording(false);
	});
	
	connect(m_pReset, &QPushButton::pressed, [this]() {
		this->Reset();
	});
}

void CKeyRecorder::keyPressEvent(QKeyEvent* ev) 
{
	if(m_bRecording)
	{
		auto nKey = ev->key();
		
		// If this is a modifier key, set nKey to 0, otherwise QKeySequence will print garbage.
		if(nKey == Qt::Key_Shift || nKey == Qt::Key_Alt || nKey == Qt::Key_Control || nKey == Qt::Key_Meta)
			nKey = 0;
		auto bIsKey = nKey != 0;
	
		if(ev->modifiers() & Qt::Modifier::CTRL)
			nKey += Qt::Modifier::CTRL;
		if(ev->modifiers() & Qt::Modifier::ALT)
			nKey += Qt::Modifier::ALT;
		if(ev->modifiers() & Qt::Modifier::SHIFT)
			nKey += Qt::Modifier::SHIFT;
		
		m_keySeq = QKeySequence(nKey);
		m_pRecorder->setText(m_keySeq.toString());
		
		// Done recording if there's actually a key.
		if(bIsKey != 0)
		{
			SetRecording(false);
			emit keySequenceChanged(m_keySeq);
		}
	}
}

void CKeyRecorder::keyReleaseEvent(QKeyEvent* ev) 
{
	
}

// Reset back to the default key sequence
void CKeyRecorder::Reset()
{
	SetRecording(false);
	m_keySeq = QKeySequence::fromString(m_default);
	m_pRecorder->setText(m_keySeq.toString());
	emit keySequenceChanged(m_keySeq);
}

void CKeyRecorder::SetRecording(bool recording)
{
	m_bRecording = recording;
	m_pRecorder->setChecked(recording);
	if(recording)
		m_pStopRecording->setIcon(style()->standardIcon(QStyle::SP_BrowserStop));
	else
	{
		m_pStopRecording->setIcon(QIcon("icons:record.svg"));
	}
}
