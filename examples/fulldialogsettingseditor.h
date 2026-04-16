#ifndef FULLDIALOGSETTINGSEDITOR_H
#define FULLDIALOGSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialFullScreenDialog;
class QPushButton;

class FullDialogSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FullDialogSettingsEditor(QWidget *parent = 0);

private slots:
    void showDialog();

private:
    QtMaterialFullScreenDialog *m_dialog;
    QPushButton *m_button;
};

#endif // FULLDIALOGSETTINGSEDITOR_H
