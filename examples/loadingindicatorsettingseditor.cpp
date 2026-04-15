#include "loadingindicatorsettingseditor.h"
#include "../components/qtmaterialloadingindicator.h"
#include "../components/qtmaterialpulltorefresh.h"
#include "../components/qtmaterialflatbutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

LoadingIndicatorSettingsEditor::LoadingIndicatorSettingsEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(24);

    QLabel *title = new QLabel(tr("Loading indicator and pull-to-refresh"), this);
    layout->addWidget(title);

    QHBoxLayout *row = new QHBoxLayout;
    row->setSpacing(24);

    m_indicator = new QtMaterialLoadingIndicator(this);
    m_indicator->setIndeterminate(true);
    m_indicator->setAutoStart(true);
    row->addWidget(m_indicator, 0, Qt::AlignLeft | Qt::AlignVCenter);

    m_refreshButton = new QtMaterialFlatButton(tr("Trigger refresh"), this);
    connect(m_refreshButton, SIGNAL(clicked()), this, SLOT(beginRefresh()));
    row->addWidget(m_refreshButton, 0, Qt::AlignLeft | Qt::AlignVCenter);
    row->addStretch(1);

    layout->addLayout(row);

    m_pullToRefresh = new QtMaterialPullToRefresh(this);
    m_pullToRefresh->setLabelText(tr("Pull down to refresh"));
    m_pullToRefresh->setRefreshingText(tr("Refreshing content..."));
    layout->addWidget(m_pullToRefresh);

    connect(m_pullToRefresh, SIGNAL(refreshRequested()), this, SLOT(endRefresh()));
}

void LoadingIndicatorSettingsEditor::beginRefresh()
{
    m_pullToRefresh->beginRefresh();
    QTimer::singleShot(1200, this, SLOT(endRefresh()));
}

void LoadingIndicatorSettingsEditor::endRefresh()
{
    m_pullToRefresh->endRefresh();
}
