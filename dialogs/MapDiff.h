#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

namespace ui
{
    class CMapDiff : public QDialog
    {
        Q_OBJECT

    public:
        CMapDiff( QWidget *pParent );

        QLineEdit* m_pFindName;
        QCheckBox* m_pDiffSimilarVisgroup;

    private slots:
        void onOKPressed();
        void onBrowsePressed();
        void onClosePressed();
    };
} // namespace ui
