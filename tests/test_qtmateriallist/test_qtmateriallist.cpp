#include <QtTest/QtTest>
#include <QStandardItemModel>

#include "qtmateriallist.h"
#include "qtmateriallistitem.h"

class test_qtmateriallist : public QObject
{
    Q_OBJECT

private slots:
    void property_roundtrip();
    void accepts_model();
};

void test_qtmateriallist::property_roundtrip()
{
    QtMaterialList list;

    list.setUseThemeColors(false);
    list.setDense(true);
    list.setShowDivider(true);
    list.setTextColor(QColor("#111111"));
    list.setSecondaryTextColor(QColor("#222222"));
    list.setBackgroundColor(QColor("#333333"));
    list.setDividerColor(QColor("#444444"));
    list.setSelectedColor(QColor("#555555"));
    list.setHoverColor(QColor("#666666"));

    QVERIFY(!list.useThemeColors());
    QVERIFY(list.isDense());
    QVERIFY(list.showDivider());
    QCOMPARE(list.textColor(), QColor("#111111"));
    QCOMPARE(list.secondaryTextColor(), QColor("#222222"));
    QCOMPARE(list.backgroundColor(), QColor("#333333"));
    QCOMPARE(list.dividerColor(), QColor("#444444"));
    QCOMPARE(list.selectedColor(), QColor("#555555"));
    QCOMPARE(list.hoverColor(), QColor("#666666"));
}

void test_qtmateriallist::accepts_model()
{
    QtMaterialList list;
    QStandardItemModel model;

    model.appendRow(new QtMaterialListItem("Item 1", "Secondary 1"));
    model.appendRow(new QtMaterialListItem("Item 2", "Secondary 2"));

    list.setModel(&model);
}


QTEST_MAIN(test_qtmateriallist)
#include "test_qtmateriallist.moc"