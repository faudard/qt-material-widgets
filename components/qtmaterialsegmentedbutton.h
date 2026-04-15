#ifndef QTMATERIALSEGMENTEDBUTTON_H
#define QTMATERIALSEGMENTEDBUTTON_H

#include <QWidget>
#include <QColor>
#include <QStringList>
#include <QScopedPointer>
#include <qicon.h>

class QtMaterialSegmentedButtonPrivate;
class QtMaterialFlatButton;
class QButtonGroup;
class QHBoxLayout;

class QtMaterialSegmentedButton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors READ useThemeColors WRITE setUseThemeColors)
    Q_PROPERTY(bool exclusive READ isExclusive WRITE setExclusive)
    Q_PROPERTY(bool showIcons READ showIcons WRITE setShowIcons)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor)

public:
    explicit QtMaterialSegmentedButton(QWidget *parent = 0);
    ~QtMaterialSegmentedButton();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setExclusive(bool value);
    bool isExclusive() const;

    void setShowIcons(bool value);
    bool showIcons() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setSelectedColor(const QColor &color);
    QColor selectedColor() const;

    void setSelectedTextColor(const QColor &color);
    QColor selectedTextColor() const;

    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;

    int addSegment(const QString &text, const QIcon &icon = QIcon());
    void clearSegments();
    int count() const;

    void setSegmentText(int index, const QString &text);
    QString segmentText(int index) const;

    void setCurrentIndex(int index);
    int currentIndex() const;

    bool isSegmentChecked(int index) const;
    void setSegmentChecked(int index, bool checked);

signals:
    void currentIndexChanged(int index);
    void segmentClicked(int index);
    void segmentToggled(int index, bool checked);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void handleButtonClicked(int id);
    void handleButtonToggled(int id, bool checked);

private:
    Q_DISABLE_COPY(QtMaterialSegmentedButton)
    Q_DECLARE_PRIVATE(QtMaterialSegmentedButton)
    QScopedPointer<QtMaterialSegmentedButtonPrivate> d_ptr;
};

#endif // QTMATERIALSEGMENTEDBUTTON_H
