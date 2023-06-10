#ifndef WRITE_VARIABLE_ELEMENT_H
#define WRITE_VARIABLE_ELEMENT_H

#include "AbstractElement.h"

class QLineEdit;
class QComboBox;
class BuilderContainer;

class WriteVariableElement : public AbstractElement {
public:
    WriteVariableElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
   

private:


    QComboBox* methodSelectcomboBox;
    QLineEdit* staticValueLineEdit;
    BuilderContainer* dynamicValueContainer;
};

#endif // WRITE_VARIABLE_ELEMENT_H