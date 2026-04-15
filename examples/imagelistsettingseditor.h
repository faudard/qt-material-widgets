#ifndef IMAGELISTSETTINGSEDITOR_H
#define IMAGELISTSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialImageList;
class QCheckBox;
class QSpinBox;

class ImageListSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ImageListSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    void setupForm();
    void setupList();

    QtMaterialImageList *m_list;
    QCheckBox *m_masonryCheckBox;
    QCheckBox *m_overlayCheckBox;
    QSpinBox *m_widthSpinBox;
    QSpinBox *m_spacingSpinBox;
};

#endif // IMAGELISTSETTINGSEDITOR_H
