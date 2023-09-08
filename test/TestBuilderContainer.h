#ifndef TESTBUILDERCONTAINER_H
#define TESTBUILDERCONTAINER_H

#include "BaseTest.h"

class TestBuilderContainer : public BaseTest {
    Q_OBJECT

private slots:
    void initTestCase() override;
    void cleanupTestCase() override;
    void init() override;
    void cleanup() override;

    void testDropToBuilderContainer();
    
};

#endif //TESTBUILDERCONTAINER_H
