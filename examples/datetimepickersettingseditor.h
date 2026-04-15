#ifndef DATETIMEPICKERSETTINGSEDITOR_H
#define DATETIMEPICKERSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialDatePicker;
class QtMaterialTimePicker;
class QCheckBox;
class QLabel;

class DateTimePickerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimePickerSettingsEditor(QWidget *parent = 0);
    ~DateTimePickerSettingsEditor();

private slots:
    void updateInfo();

private:
    QtMaterialDatePicker *m_datePicker;
    QtMaterialTimePicker *m_timePicker;
    QCheckBox *m_themeCheckBox;
    QCheckBox *m_24hCheckBox;
    QLabel *m_infoLabel;
};

#endif // DATETIMEPICKERSETTINGSEDITOR_H
