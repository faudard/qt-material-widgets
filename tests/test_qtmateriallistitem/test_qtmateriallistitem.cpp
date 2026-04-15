#include <QtTest/QtTest>
#include <QPixmap>

#include "qtmateriallist.h"
#include "qtmateriallistitem.h"

class test_qtmateriallistitem : public QObject
{
    Q_OBJECT

private slots:
    void stores_text_roles();
    void stores_divider_flags();
    void stores_avatar_data();
};

void test_qtmateriallistitem::stores_text_roles()
{
    QtMaterialListItem item("Primary", "Secondary");

    QCOMPARE(item.primaryText(), QString("Primary"));
    QCOMPARE(item.secondaryText(), QString("Secondary"));

    item.setPrimaryText("Changed");
    item.setSecondaryText("Sub");
    item.setTrailingText("Meta");

    QCOMPARE(item.primaryText(), QString("Changed"));
    QCOMPARE(item.secondaryText(), QString("Sub"));
    QCOMPARE(item.trailingText(), QString("Meta"));
}

void test_qtmateriallistitem::stores_divider_flags()
{
    QtMaterialListItem item;

    item.setDivider(true);
    item.setFullWidthDivider(true);

    QVERIFY(item.divider());
    QVERIFY(item.fullWidthDivider());

    item.setDivider(false);
    item.setFullWidthDivider(false);

    QVERIFY(!item.divider());
    QVERIFY(!item.fullWidthDivider());
}

void test_qtmateriallistitem::stores_avatar_data()
{
    QtMaterialListItem item;

    item.setAvatar("AB", QColor(Qt::red));
    QCOMPARE(item.avatarText(), QString("AB"));
    QCOMPARE(item.avatarColor(), QColor(Qt::red));

    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::black);
    item.setAvatarPixmap(pixmap);
    QVERIFY(!item.avatarPixmap().isNull());
}

QTEST_MAIN(test_qtmateriallistitem)
#include "test_qtmateriallistitem.moc"