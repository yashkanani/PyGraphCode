#include "TestManager.h"
#include <QDebug>
#include <QTest>
#include "MainWindowManager.h"

int TestManager::runTests(int argc, char *argv[])
{
   MainWindowManager::getAppManage();

   QStringList failedTests;
   QString outputFile{"testOutput.txt"};
   /*
   QStringList arguments;
   for (auto i = 0; i < argc; i++) {
           arguments << argv[i];
   }
   arguments << "-o" << QString{ outputFile + ",txt" } << "-v2";
   */
   for (const auto test : getInstance().mTests)
      if (QTest::qExec(test, argc, argv))
         failedTests << test->metaObject()->className();

   if (!failedTests.isEmpty())
   {
      qWarning() << "#######################################";
      qWarning() << "TEST FAILURES DETECTED:";

      for (auto f : failedTests)
         qWarning() << "  - " << f;

      qWarning() << "Results written to: " << outputFile;
      qWarning() << "#######################################";
   }

   return failedTests.count();
}

void TestManager::addTest(QObject *test)
{
   if (test && qobject_cast<QObject *>(test))
      getInstance().mTests.append(qobject_cast<QObject *>(test));
}

TestManager &TestManager::getInstance()
{
   static TestManager INSTANCE;

   return INSTANCE;
}

TestManager::~TestManager() {}