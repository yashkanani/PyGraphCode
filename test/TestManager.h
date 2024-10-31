#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QSharedPointer>
#include <QVector>


class BaseTest;

class TestManager final {
public:
    static int runTests(int argc, char* arvg[]);
    static void addTest(QObject* test);
    static TestManager& getInstance();
    ~TestManager();

private:
    
    TestManager() = default;
    QVector<QObject*> mTests;
};

#endif // TESTMANAGER_H