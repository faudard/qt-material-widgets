#ifndef SEGMENTEDBUTTONSETTINGSEDITOR_H
#define SEGMENTEDBUTTONSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialSegmentedButton;
class QCheckBox;

class SegmentedButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SegmentedButtonSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSegmentedButton *m_segmentedButton;
    QCheckBox *m_useThemeColors;
    QCheckBox *m_exclusive;
    QCheckBox *m_showIcons;
};

#endif // SEGMENTEDBUTTONSETTINGSEDITOR_H
