#ifndef TESTSEARCHBARWIDGET_H
#define TESTSEARCHBARWIDGET_H

#include "BaseTest.h"

class TestSearchBarWidget : public BaseTest {
    Q_OBJECT

public:
    TestSearchBarWidget();

private slots:

    void initTestCase() override;
    void cleanupTestCase() override;
    void init() override;
    void cleanup() override;

   
    void testSearchBarInitialization();

    void testSearchBarText_data();
    void testSearchBarText();

};

#endif // TESTSEARCHBARWIDGET_H
