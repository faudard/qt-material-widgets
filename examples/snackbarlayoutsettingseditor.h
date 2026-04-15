#ifndef SNACKBARLAYOUTSETTINGSEDITOR_H
#define SNACKBARLAYOUTSETTINGSEDITOR_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QSlider;
class QtMaterialFlatButton;
class QtMaterialSnackbarLayout;

class SnackbarLayoutSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SnackbarLayoutSettingsEditor(QWidget *parent = 0);
    ~SnackbarLayoutSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();

private:
    QCheckBox *const m_dense;
    QCheckBox *const m_showAction;
    QCheckBox *const m_multiLine;
    QSlider *const m_widthSlider;
    QWidget *const m_preview;
    QLabel *const m_messageLabel;
    QtMaterialFlatButton *const m_actionButton;
    QtMaterialSnackbarLayout *const m_layout;
};

#endif // SNACKBARLAYOUTSETTINGSEDITOR_H
