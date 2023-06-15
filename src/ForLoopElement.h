#ifndef FOR_LOOP_ELEMENT_H
#define FOR_LOOP_ELEMENT_H

#include "AbstractElement.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>

class BuilderContainer;
class ForLoopElement : public AbstractElement {
public:
    ForLoopElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    BuilderContainer* variableContainer;
    QComboBox* endCondition;
    BuilderContainer* startContainer;
    BuilderContainer* endContainer;
    BuilderContainer* incrementContainer;
    BuilderContainer* bodyContainer;

};

#endif // FOR_LOOP_ELEMENT_H