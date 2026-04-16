#ifndef APPBARSTATELAYSETTINGSEDITOR_H
#define APPBARSTATELAYSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialAppBarStateLayer;
class QSlider;
class QCheckBox;

class AppBarStateLayerSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AppBarStateLayerSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialAppBarStateLayer *m_layer;
    QSlider *m_progressSlider;
    QCheckBox *m_liftOnScroll;
};

#endif // APPBARSTATELAYSETTINGSEDITOR_H
