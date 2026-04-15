#include <QtTest/QtTest>

#include "qtmaterialtextfield.h"

class test_qtmaterialtextfield : public QObject
{
    Q_OBJECT

private slots:
    void property_roundtrip();
    void text_roundtrip();
};

void test_qtmaterialtextfield::property_roundtrip()
{
    QtMaterialTextField field;

    field.setUseThemeColors(false);
    field.setShowLabel(false);
    field.setLabel("Name");
    field.setLabelFontSize(qreal(11.5));
    field.setTextColor(QColor("#111111"));
    field.setLabelColor(QColor("#222222"));
    field.setInkColor(QColor("#333333"));
    field.setInputLineColor(QColor("#444444"));
    field.setShowInputLine(false);

    QVERIFY(!field.useThemeColors());
    QVERIFY(field.hasLabel());
    QCOMPARE(field.label(), QString("Name"));
    QCOMPARE(field.labelFontSize(), qreal(11.5));
    QCOMPARE(field.textColor(), QColor("#111111"));
    QCOMPARE(field.labelColor(), QColor("#222222"));
    QCOMPARE(field.inkColor(), QColor("#333333"));
    QCOMPARE(field.inputLineColor(), QColor("#444444"));
    QVERIFY(!field.hasInputLine());
}

void test_qtmaterialtextfield::text_roundtrip()
{
    QtMaterialTextField field;

    field.setText("hello");
    QCOMPARE(field.text(), QString("hello"));

    field.clear();
    QVERIFY(field.text().isEmpty());
}

QTEST_MAIN(test_qtmaterialtextfield)
#include "test_qtmaterialtextfield.moc"
