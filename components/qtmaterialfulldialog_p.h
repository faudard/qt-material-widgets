#ifndef QTMATERIALFULLDIALOG_P_H
#define QTMATERIALFULLDIALOG_P_H

#include <QColor>
#include <QString>

class QVBoxLayout;
class QWidget;

class QtMaterialFullScreenDialogPrivate
{
public:
    QtMaterialFullScreenDialogPrivate();

    bool useThemeColors;
    bool dismissOnOverlayClick;
    QColor backgroundColor;
    QColor overlayColor;
    QColor titleColor;
    QString title;
    QWidget *surface;
    QWidget *header;
    QWidget *content;
    QVBoxLayout *surfaceLayout;
    QVBoxLayout *contentLayout;
};

#endif // QTMATERIALFULLDIALOG_P_H
