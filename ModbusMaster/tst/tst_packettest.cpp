#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class PacketTest : public QObject
{
    Q_OBJECT

public:
    PacketTest();
    ~PacketTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

PacketTest::PacketTest()
{

}

PacketTest::~PacketTest()
{

}

void PacketTest::initTestCase()
{

}

void PacketTest::cleanupTestCase()
{

}

void PacketTest::test_case1()
{

}

QTEST_MAIN(PacketTest)

#include "tst_packettest.moc"
