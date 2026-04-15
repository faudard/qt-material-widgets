#ifndef CAROUSELSETTINGSEDITOR_H
#define CAROUSELSETTINGSEDITOR_H

#include <QWidget>

class QtMaterialCarousel;
class QCheckBox;
class QSpinBox;

class CarouselSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CarouselSettingsEditor(QWidget *parent = 0);

private slots:
    void updateWidget();

private:
    QtMaterialCarousel *m_carousel;
    QCheckBox *m_autoPlayCheckBox;
    QCheckBox *m_wrapCheckBox;
    QCheckBox *m_indicatorsCheckBox;
    QSpinBox *m_intervalSpinBox;
};

#endif // CAROUSELSETTINGSEDITOR_H
