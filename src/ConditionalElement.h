#ifndef CONDITIONAL_ELEMENT_H
#define CONDITIONAL_ELEMENT_H

#include "AbstractElement.h"

class WriteVariableElement;
class QComboBox;
class ConditionalElement : public AbstractElement {
public:
    ConditionalElement();
    std::shared_ptr<AbstractElement> clone() const override;
    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;


private:
   

    WriteVariableElement* firstVariableElement;
    QComboBox* conditionComboBox;
    WriteVariableElement* secondVariableElement;
};

#endif // CONDITIONAL_ELEMENT_H