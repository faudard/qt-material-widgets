#include <QtTest/QtTest>
#include <QSignalSpy>

#include "qtmaterialtoggle.h"

class test_qtmaterialtoggle : public QObject
{
    Q_OBJECT

private slots:
    void property_roundtrip_and_orientation();
    void click_emits_signals_and_changes_state();
};

void test_qtmaterialtoggle::property_roundtrip_and_orientation()
{
    QtMaterialToggle toggle;

    toggle.setUseThemeColors(false);
    toggle.setDisabledColor(QColor("#111111"));
    toggle.setActiveColor(QColor("#222222"));
    toggle.setInactiveColor(QColor("#333333"));
    toggle.setTrackColor(QColor("#444444"));
    toggle.setOrientation(Qt::Vertical);

    QVERIFY(!toggle.useThemeColors());
    QCOMPARE(toggle.disabledColor(), QColor("#111111"));
    QCOMPARE(toggle.activeColor(), QColor("#222222"));
    QCOMPARE(toggle.inactiveColor(), QColor("#333333"));
    QCOMPARE(toggle.trackColor(), QColor("#444444"));
    QCOMPARE(toggle.orientation(), Qt::Vertical);
    QCOMPARE(toggle.sizeHint(), QSize(48, 64));

    toggle.setOrientation(Qt::Horizontal);
    QCOMPARE(toggle.orientation(), Qt::Horizontal);
    QCOMPARE(toggle.sizeHint(), QSize(64, 48));
}

void test_qtmaterialtoggle::click_emits_signals_and_changes_state()
{
    QtMaterialToggle toggle;

    QVERIFY(toggle.isCheckable());
    QVERIFY(!toggle.isChecked());

    QSignalSpy clickedSpy(&toggle, SIGNAL(clicked(bool)));
    QSignalSpy toggledSpy(&toggle, SIGNAL(toggled(bool)));

    toggle.click();

    QVERIFY(toggle.isChecked());
    QCOMPARE(clickedSpy.count(), 1);
    QCOMPARE(toggledSpy.count(), 1);
}

QTEST_MAIN(test_qtmaterialtoggle)
#include "test_qtmaterialtoggle.moc"
