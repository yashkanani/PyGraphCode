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
    void setUserInput(std::shared_ptr<ElementUserInputs> userInput) override;
    std::shared_ptr<ElementUserInputs> getUserInput() override;
    void updateParameterWidgets(ParameterUIBuilder* const parameterUIBuilder) override;

private:
    std::shared_ptr<BuilderContainer> variableContainer;
    QString comboSelection;
    std::shared_ptr<BuilderContainer> startContainer;
    std::shared_ptr<BuilderContainer> endContainer;
    std::shared_ptr<BuilderContainer> incrementContainer;
    std::shared_ptr<BuilderContainer> bodyContainer;

};

#endif // FOR_LOOP_ELEMENT_H