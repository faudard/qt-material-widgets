#ifndef TOOLTIPSETTINGSEDITOR_H
#define TOOLTIPSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialRaisedButton;
class QtMaterialTooltip;
class QCheckBox;
class QSpinBox;

class TooltipSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TooltipSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialRaisedButton *m_button;
    QtMaterialTooltip *m_tooltip;
    QCheckBox *m_themeColors;
    QSpinBox *m_fontSize;
    QSpinBox *m_padding;
    QSpinBox *m_autoHide;
};

#endif // TOOLTIPSETTINGSEDITOR_H
