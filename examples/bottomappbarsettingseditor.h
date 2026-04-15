#ifndef BOTTOMAPPBARSETTINGSEDITOR_H
#define BOTTOMAPPBARSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialBottomAppBar;
class QtMaterialIconButton;
class QCheckBox;
class QSpinBox;

class BottomAppBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BottomAppBarSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    void setupForm();

    QtMaterialBottomAppBar *m_bottomAppBar;
    QtMaterialIconButton *m_navButton;
    QtMaterialIconButton *m_searchButton;
    QtMaterialIconButton *m_moreButton;

    QCheckBox *m_centerFabCheckBox;
    QCheckBox *m_showCradleCheckBox;
    QSpinBox *m_fabDiameterSpinBox;
};

#endif // BOTTOMAPPBARSETTINGSEDITOR_H
