#ifndef VARIABLE_ELEMENT_H
#define VARIABLE_ELEMENT_H

#include "AbstractElement.h"

class QLineEdit;
class QComboBox;
class BuilderContainer;

class VariableElement : public AbstractElement {
public:
    VariableElement();
    std::shared_ptr<AbstractElement> clone() const override;
    QString getName() const override;
    QPixmap getImage() const override;
    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    QString name;
    QPixmap image;

    QComboBox* methodSelectcomboBox;
    QLineEdit* staticValueLineEdit;
    BuilderContainer* dynamicValueContainer;
};

#endif // VARIABLE_ELEMENT_H