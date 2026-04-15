#ifndef RICHTOOLTIPSETTINGSEDITOR_H
#define RICHTOOLTIPSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialRaisedButton;
class QtMaterialRichTooltip;

class RichTooltipSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RichTooltipSettingsEditor(QWidget *parent = 0);
    ~RichTooltipSettingsEditor();

private slots:
    void updateWidget();

private:
    QtMaterialRaisedButton *m_button;
    QtMaterialRichTooltip  *m_tooltip;
};

#endif  // RICHTOOLTIPSETTINGSEDITOR_H
