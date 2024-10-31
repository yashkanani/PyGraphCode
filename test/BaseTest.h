#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>

class BaseTest : public QObject
{
public:
	BaseTest();
	virtual void initTestCase() = 0;
	virtual void cleanupTestCase() = 0;
	virtual void init() = 0;
	virtual void cleanup() = 0;
};
#endif // BASETEST_H