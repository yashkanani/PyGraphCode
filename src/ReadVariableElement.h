#ifndef VARIABLE_ELEMENT_H
#define VARIABLE_ELEMENT_H

#include "AbstractElement.h"

class QLineEdit;
class QComboBox;
class BuilderContainer;

class ReadVariableElement : public AbstractElement {
public:
    ReadVariableElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
   

private:


    QComboBox* methodSelectcomboBox;
    QLineEdit* staticValueLineEdit;
    BuilderContainer* dynamicValueContainer;
};

#endif // VARIABLE_ELEMENT_H