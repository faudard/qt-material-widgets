#ifndef BANNERSETTINGSEDITOR_H
#define BANNERSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialBanner;
class QCheckBox;
class QLineEdit;
class QPushButton;

class BannerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BannerSettingsEditor(QWidget *parent = 0);

private slots:
    void updateBanner();

private:
    QtMaterialBanner *m_banner;
    QLineEdit        *m_titleEdit;
    QLineEdit        *m_supportingEdit;
    QCheckBox        *m_iconCheck;
    QCheckBox        *m_dismissibleCheck;
    QCheckBox        *m_supportingCheck;
};

#endif // BANNERSETTINGSEDITOR_H
