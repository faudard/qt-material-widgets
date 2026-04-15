#ifndef SKELETONSETTINGSEDITOR_H
#define SKELETONSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialCheckBox;
class QtMaterialRaisedButton;
class QtMaterialSkeleton;
class QComboBox;
class QSlider;

class SkeletonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit SkeletonSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialSkeleton *m_blockSkeleton;
    QtMaterialSkeleton *m_textSkeleton;
    QtMaterialSkeleton *m_avatarSkeleton;
    QtMaterialSkeleton *m_avatarTextSkeleton;
    QtMaterialCheckBox *m_animationCheckBox;
    QtMaterialCheckBox *m_themeColorsCheckBox;
    QtMaterialCheckBox *m_circularCheckBox;
    QComboBox *m_modeComboBox;
    QSlider *m_linesSlider;
    QSlider *m_radiusSlider;
};

#endif // SKELETONSETTINGSEDITOR_H
