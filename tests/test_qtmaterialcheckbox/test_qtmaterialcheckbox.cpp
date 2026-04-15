#include <QtTest/QtTest>
#include <QSignalSpy>

#include "qtmaterialcheckbox.h"

class test_qtmaterialcheckbox : public QObject
{
    Q_OBJECT

private slots:
    void property_roundtrip();
    void click_emits_signals_and_changes_state();
};

void test_qtmaterialcheckbox::property_roundtrip()
{
    QtMaterialCheckBox box;

    box.setUseThemeColors(false);
    box.setLabelPosition(QtMaterialCheckable::LabelPositionLeft);
    box.setCheckedColor(QColor("#111111"));
    box.setUncheckedColor(QColor("#222222"));
    box.setTextColor(QColor("#333333"));
    box.setDisabledColor(QColor("#444444"));

    QVERIFY(!box.useThemeColors());
    QCOMPARE(box.labelPosition(), QtMaterialCheckable::LabelPositionLeft);
    QCOMPARE(box.checkedColor(), QColor("#111111"));
    QCOMPARE(box.uncheckedColor(), QColor("#222222"));
    QCOMPARE(box.textColor(), QColor("#333333"));
    QCOMPARE(box.disabledColor(), QColor("#444444"));
}

void test_qtmaterialcheckbox::click_emits_signals_and_changes_state()
{
    QtMaterialCheckBox box;
    box.setChecked(false);

    QSignalSpy clickedSpy(&box, SIGNAL(clicked(bool)));
    QSignalSpy toggledSpy(&box, SIGNAL(toggled(bool)));

    box.click();

    QVERIFY(box.isChecked());
    QCOMPARE(clickedSpy.count(), 1);
    QCOMPARE(toggledSpy.count(), 1);

    const QList<QVariant> args = toggledSpy.takeFirst();
    QCOMPARE(args.at(0).toBool(), true);
}

QTEST_MAIN(test_qtmaterialcheckbox)
#include "test_qtmaterialcheckbox.moc"
