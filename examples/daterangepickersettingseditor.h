#ifndef DATERANGEPICKERSETTINGSEDITOR_H
#define DATERANGEPICKERSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialDateRangePicker;
class QLabel;
class QCheckBox;
class QSpinBox;

class DateRangePickerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DateRangePickerSettingsEditor(QWidget *parent = 0);

private slots:
    void updateRangeText();

private:
    QtMaterialDateRangePicker *const m_picker;
    QLabel *const m_label;
    QCheckBox *const m_dualMonthCheckBox;
};

#endif // DATERANGEPICKERSETTINGSEDITOR_H
