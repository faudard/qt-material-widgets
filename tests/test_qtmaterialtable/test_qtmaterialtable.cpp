#include <QtTest/QtTest>
#include <QStandardItemModel>

#include "qtmaterialtable.h"

class test_qtmaterialtable : public QObject
{
    Q_OBJECT

private slots:
    void property_roundtrip();
    void accepts_model();
    void hovered_row_is_invalid_by_default();
};

void test_qtmaterialtable::property_roundtrip()
{
    QtMaterialTable table;

    table.setUseThemeColors(false);
    table.setDense(true);
    table.setHeaderColor(QColor("#111111"));
    table.setTextColor(QColor("#222222"));
    table.setBackgroundColor(QColor("#333333"));
    table.setAlternateBackgroundColor(QColor("#444444"));
    table.setGridColor(QColor("#555555"));
    table.setSelectedRowColor(QColor("#666666"));
    table.setHoverRowColor(QColor("#777777"));

    QVERIFY(!table.useThemeColors());
    QVERIFY(table.isDense());
    QCOMPARE(table.headerColor(), QColor("#111111"));
    QCOMPARE(table.textColor(), QColor("#222222"));
    QCOMPARE(table.backgroundColor(), QColor("#333333"));
    QCOMPARE(table.alternateBackgroundColor(), QColor("#444444"));
    QCOMPARE(table.gridColor(), QColor("#555555"));
    QCOMPARE(table.selectedRowColor(), QColor("#666666"));
    QCOMPARE(table.hoverRowColor(), QColor("#777777"));
}

void test_qtmaterialtable::accepts_model()
{
    QtMaterialTable table;
    QStandardItemModel model(2, 2);

    model.setItem(0, 0, new QStandardItem("A"));
    model.setItem(0, 1, new QStandardItem("B"));
    model.setItem(1, 0, new QStandardItem("C"));
    model.setItem(1, 1, new QStandardItem("D"));

    table.setModel(&model);
    QCOMPARE(table.model(), &model);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.columnCount(), 2);
}

void test_qtmaterialtable::hovered_row_is_invalid_by_default()
