#ifndef OPERATIONELEMENT_H
#define OPERATIONELEMENT_H

#include "AbstractElement.h"
class QComboBox;
class BuilderContainer;
class OperationElement : public AbstractElement {
public:
    OperationElement();

    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText(int indentLevel) const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    std::shared_ptr<BuilderContainer> firstVariableContainer;
    std::shared_ptr<BuilderContainer> secondVariableContainer;
    
    QString comboSelection;


};

#endif // OPERATIONELEMENT_H