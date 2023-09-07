#include "TestSearchBarWidget.h"
#include "MainWindow.h"
#include "MainWindowManager.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qtest.h"
#include "qtreeview.h"

TestSearchBarWidget::TestSearchBarWidget()
{
    // Constructor logic here if needed.
}

void TestSearchBarWidget::initTestCase()
{
    // Initialization logic before running the test case.
}

void TestSearchBarWidget::cleanupTestCase()
{
    // Cleanup logic after running the test case.
}

void TestSearchBarWidget::init()
{
    // Initialization logic before each individual test.
}

void TestSearchBarWidget::cleanup()
{
    // Cleanup logic after each individual test.
}



void TestSearchBarWidget::testSearchBarInitialization()
{
    // Get access to the MainAppWindow and searchBarWidget
    MainAppWindow* mainWindow = MainWindowManager::getAppManage().getMainAppWindow();
    QWidget* searchBarWidget = mainWindow->findChild<QWidget*>("searchBarWidget");
    QWidget* tabDataWidget = mainWindow->findChild<QWidget*>("prebuiltElementsList");

    // Check if searchBarWidget is not null
    QVERIFY(searchBarWidget != nullptr);
    QVERIFY(tabDataWidget != nullptr);

    QLineEdit* searchLineEdit = searchBarWidget->findChild<QLineEdit*>("searchLineEdit");
    QTreeView* elementsListWidget = tabDataWidget->findChild<QTreeView*>("ElementsListWidget");

    // Check if searchLineEdit is not null
    QVERIFY(searchBarWidget != nullptr);
    QVERIFY(elementsListWidget != nullptr);

    // Perform specific assertions or tests on the searchBarWidget
    QVERIFY(searchBarWidget->isEnabled()); //  Check if the search bar is enabled by default
    QVERIFY(searchLineEdit->text().isEmpty() == true); // Check if the text is empty initially
    QCOMPARE(searchLineEdit->placeholderText(), QString("Search"));

    
}

void TestSearchBarWidget::testSearchBarText_data() {
    
    // Define your test data here
    QTest::addColumn<QString>("testText");

    // Add test cases with different data values
    QTest::newRow("Test1 : Search simple word") << "Read";
    QTest::newRow("Test2 : Search simple word ") << "Wirte";
    QTest::newRow("Test3 : Search simple word") << "Variable";
    QTest::newRow("Test4 : Search empty space") << " ";
    QTest::newRow("Test5 : Search number") << "123";
    QTest::newRow("Test6 : Search single latter") << "R";
    QTest::newRow("Test7 : Search blank") << "";
}

void TestSearchBarWidget::testSearchBarText()
{
    // Get access to the MainAppWindow and searchBarWidget
    MainAppWindow* mainWindow = MainWindowManager::getAppManage().getMainAppWindow();
    QWidget* searchBarWidget = mainWindow->findChild<QWidget*>("searchBarWidget");
    QWidget* tabDataWidget = mainWindow->findChild<QWidget*>("prebuiltElementsList");

    // Check if searchBarWidget is not null
    QVERIFY(searchBarWidget != nullptr);
    QVERIFY(tabDataWidget != nullptr);

    QLineEdit* searchLineEdit = searchBarWidget->findChild<QLineEdit*>("searchLineEdit");
    QTreeView* elementsListWidget = tabDataWidget->findChild<QTreeView*>("ElementsListWidget");

    // Check if searchLineEdit is not null
    QVERIFY(searchBarWidget != nullptr);
    QVERIFY(elementsListWidget != nullptr);


    QFETCH(QString, testText);
    searchLineEdit->setText(testText);

    // Get the model associated with the tree view
    QAbstractItemModel* model = elementsListWidget->model();

    // Check if the model is not null
    QVERIFY(model != nullptr);

    // Get the root index of the model (top-level items)
    QModelIndex rootIndex = QModelIndex();

    // Get the text from the searchLineEdit
    QString searchText = searchLineEdit->text();

    for (int row = 0; row < model->rowCount(); ++row) {

        // Iterate through columns
        for (int column = 0; column < model->columnCount(); ++column) {
            // Create an index for the current row and column
            QModelIndex currentIndex = model->index(row, column);

            // Check if the index is valid (it should be)
            QVERIFY(currentIndex.isValid());

            // Accessing a QLabel by object name within the current index
            QLabel* nameLabel = elementsListWidget->indexWidget(currentIndex)->findChild<QLabel*>("elementNameLabel");

            // Check if the QLabel with object name "elementNameLabel" exists
            if (nameLabel != nullptr) {
                // Get the text from nameLabel
                QString labeltext = nameLabel->text();

                // Check if nameLabel contains the searchText
                QVERIFY(labeltext.contains(searchText, Qt::CaseInsensitive)); // You can use CaseInsensitive or CaseSensitive comparison as needed.
            }
        }
    }
}

const static TestSearchBarWidget testSearchBarWidget;