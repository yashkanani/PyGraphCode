#include "ForLoopElement.h"
#include "BuilderContainer.h"
#include "CodeText.h"
#include "PlaceHolder.h"
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qwidget.h>

ForLoopElement::ForLoopElement()
{
    name = "For Loop";
    image = QPixmap(":/resource/For_loop.png");
    type = BasicElementType::FOR_LOOP;

    endCondition = nullptr;
    variableContainer = nullptr;
    startContainer = nullptr;
    incrementContainer = nullptr;
    bodyContainer = nullptr;
}

std::shared_ptr<AbstractElement> ForLoopElement::clone() const
{
    return std::make_shared<ForLoopElement>();
}

std::shared_ptr<CodeText> ForLoopElement::getText(int indentLevel) const
{
    std::shared_ptr<CodeText> ret = std::make_shared<CodeText>(indentLevel);
    

    if (endCondition && variableContainer) {
        switch (endCondition->currentIndex()) {

        case 0: {
            ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1):").arg(endContainer->getText(0)->getResult()));
            ret->addToBody("\n");
        } break;
        case 1: {
            if (startContainer) {
                ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1, %2):").arg(startContainer->getText(0)->getResult()).arg(endContainer->getText(0)->getResult()));
                ret->addToBody("\n");
            }
        } break;
        case 2: {
            if (startContainer && incrementContainer) {
                ret->addToBody("for " + variableContainer->getText(0)->getResult() + QString(" in range(%1, %2, %3):").arg(startContainer->getText(0)->getResult()).arg(endContainer->getText(0)->getResult()).arg(incrementContainer->getText(0)->getResult()));
                ret->addToBody("\n");
            }
        } break;

        default:
            break;
        }
    }

    if (bodyContainer) {
        ret->increaseIndentOfBody();
        ret->append(*(bodyContainer->getText(ret->getCurrentIndentOfBody())));
        ret->removeIndentOfBody();
    }

    return ret;
}

QWidget* ForLoopElement::getViewWidget(QWidget* parent)
{
    QGroupBox* wdg = new QGroupBox("For Loop", parent);
    wdg->setObjectName("ForLoopGroupBox");

    // Set the style sheet to customize the appearance
    wdg->setStyleSheet(
        "QGroupBox#ForLoopGroupBox {"
        "   border: 1px solid #888888;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 10px;"
        "   background-color: white;"
        "}"
        "QGroupBox#ForLoopGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"
        "   padding: 5px;"
        "}");

    QGridLayout* wdgLayout = new QGridLayout(wdg);
    wdgLayout->setContentsMargins(0, 0, 0, 0);
    wdg->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGroupBox* variableGroup = new QGroupBox("", wdg);
    QVBoxLayout* variableLay = new QVBoxLayout(variableGroup);

    bool subContainer = true;
    variableContainer = new BuilderContainer(wdg, subContainer);
    QObject::connect(variableContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    variableLay->addWidget(variableContainer);

    wdgLayout->addWidget(variableGroup, 0, 0);

    QGroupBox* endGroup = new QGroupBox("", wdg);
    QHBoxLayout* endVariableLay = new QHBoxLayout(endGroup);

    endCondition = new QComboBox(wdg);
    endCondition->addItem("Static");
    endCondition->addItem("Dynamic");
    endCondition->addItem("yash");
    endCondition->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    endVariableLay->addWidget(endCondition, Qt::AlignLeft | Qt::AlignTop);

    QList<BasicElementType> acceptedTypes = { BasicElementType::CONSTANT_DECIMAL, BasicElementType::READ_VARIABLE };
    
    startContainer = new BuilderContainer(wdg, subContainer);
    startContainer->setAcceptedTypes(acceptedTypes);
    startContainer->setMaxElements(1);
    QObject::connect(startContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    endVariableLay->addWidget(startContainer);

    endContainer = new BuilderContainer(wdg, subContainer);
    endContainer->setAcceptedTypes(acceptedTypes);
    endContainer->setMaxElements(1);
    QObject::connect(endContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    endVariableLay->addWidget(endContainer);

    incrementContainer = new BuilderContainer(wdg, subContainer);
    incrementContainer->setAcceptedTypes(acceptedTypes);
    incrementContainer->setMaxElements(1);
    QObject::connect(incrementContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    endVariableLay->addWidget(incrementContainer);

    wdgLayout->addWidget(endGroup, 0, 1);

    bodyContainer = new BuilderContainer(wdg, subContainer);
    QObject::connect(bodyContainer, &BuilderContainer::updateResultedTextView, this, &AbstractElement::childValueChanged);
    wdgLayout->addWidget(bodyContainer, 1, 0, 1, 2);

    // Connect the combo box signals to slots or functions
    QObject::connect(endCondition, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        switch (index) {

        case 0: {
            startContainer->hide();
            endContainer->show();
            incrementContainer->hide();
        } break;
        case 1: {
            startContainer->show();
            endContainer->show();
            incrementContainer->hide();
        } break;
        case 2: {
            startContainer->show();
            endContainer->show();
            incrementContainer->show();
        } break;

        default:
            endContainer->show();
            break;
        }
    });

    startContainer->hide();
    endContainer->show();
    incrementContainer->hide();

    return wdg;
}
