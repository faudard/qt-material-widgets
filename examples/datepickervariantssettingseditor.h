#ifndef DATEPICKERVARIANTSSETTINGSEDITOR_H
#define DATEPICKERVARIANTSSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialDateField;
class QtMaterialDockedDatePicker;

class DatePickerVariantsSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DatePickerVariantsSettingsEditor(QWidget *parent = 0);

private:
    QtMaterialDateField *m_dateField;
    QtMaterialDockedDatePicker *m_dockedPicker;
};

#endif // DATEPICKERVARIANTSSETTINGSEDITOR_H
