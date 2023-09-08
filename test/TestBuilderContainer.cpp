#include "TestBuilderContainer.h"
#include "MainWindow.h"
#include "BuilderContainer.h"
#include "MainWindowManager.h"
#include "qtreeview.h"
#include "qtest.h"
#include "qlabel.h"
#include "qtimer.h"
#include "qdrag.h"

void TestBuilderContainer::initTestCase() {
    // Initialization code before running the test cases
}

void TestBuilderContainer::cleanupTestCase() {
    // Cleanup code after running all test cases
}

void TestBuilderContainer::init() {
    // Initialization code before each test case
    QTest::qWait(1000);
}

void TestBuilderContainer::cleanup() {
    // Cleanup code after each test case
}

void TestBuilderContainer::testDropToBuilderContainer()
{
    MainAppWindow* mainWindow = MainWindowManager::getAppManage().getMainAppWindow();
    QVERIFY(mainWindow != nullptr);

    QWidget* tabDataWidget = mainWindow->findChild<QWidget*>("prebuiltElementsList");
    QTreeView* elementsListWidget = tabDataWidget->findChild<QTreeView*>("ElementsListWidget");
    QVERIFY(elementsListWidget != nullptr);

    BuilderContainer* builderContainer = mainWindow->findChild<BuilderContainer*>("BuilderContainer");
    QVERIFY(builderContainer != nullptr);
    
    // Get the model associated with the tree view
    QAbstractItemModel* model = elementsListWidget->model();
    QVERIFY(model != nullptr);


    QVERIFY(QTest::qWaitForWindowExposed(builderContainer));
    QVERIFY(QTest::qWaitForWindowActive(builderContainer));


    for (int row = 0; row < model->rowCount(); ++row) {
        
        // Iterate through columns
        for (int column = 0; column < model->columnCount(); ++column) {

            QTest::qWait(100); // Wait for a moment to ensure the drag is initiated
            
   
            // Create an index for the current row and column
            QModelIndex currentIndex = model->index(row, column);

            // Check if the index is valid (it should be)
            QVERIFY(currentIndex.isValid());

            // Accessing a QLabel by object name within the current index
            QLabel* elementIconLabel = elementsListWidget->indexWidget(currentIndex)->findChild<QLabel*>("elementIconLabel");

            // Check if the QLabel with object name "elementNameLabel" exists
            if (elementIconLabel != nullptr) {
               
                // Calculate the center position of elementIconLabel
                QPoint elementCenter = elementIconLabel->rect().center();

                // Map the center position to global coordinates
                QPoint globalElementCenter = elementIconLabel->mapToGlobal(elementCenter);

                // Simulate a mouse press event at the center of elementIconLabel
                QTest::mousePress(elementIconLabel, Qt::LeftButton, Qt::NoModifier, globalElementCenter);
                QTest::qWait(100);

                // Simulate the drag event
                // QTest::mouseMove(elementsListWidget);
                
                // Calculate the center position of the builderContainer
                QPoint builderContainerCenter = builderContainer->rect().center();
                QTest::mouseMove(builderContainer, builderContainerCenter);
                QTest::qWait(100);

                QTest::mouseRelease(builderContainer, Qt::LeftButton, Qt::NoModifier, builderContainerCenter);
                QTest::qWait(100);

                
            }
        }
    }

}

const static TestBuilderContainer testBuilderContainer;

