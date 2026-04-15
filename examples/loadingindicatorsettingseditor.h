#ifndef LOADINGINDICATORSETTINGSEDITOR_H
#define LOADINGINDICATORSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialLoadingIndicator;
class QtMaterialPullToRefresh;
class QtMaterialFlatButton;

class LoadingIndicatorSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingIndicatorSettingsEditor(QWidget *parent = 0);

private slots:
    void beginRefresh();
    void endRefresh();

private:
    QtMaterialLoadingIndicator *m_indicator;
    QtMaterialPullToRefresh *m_pullToRefresh;
    QtMaterialFlatButton *m_refreshButton;
};

#endif // LOADINGINDICATORSETTINGSEDITOR_H
