#include "qcoreapplication.h"
#include <QTest>
#include "TestManager.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setAttribute(Qt::AA_Use96Dpi, true);

	TestManager::getInstance().runTests(argc, argv);
    return app.exec();
}