#include "BaseTest.h"
#include "TestManager.h"



BaseTest::BaseTest()
{
   TestManager::getInstance().addTest(static_cast<BaseTest *>(this));
}