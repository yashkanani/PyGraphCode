#ifndef FOR_LOOP_ELEMENT_H
#define FOR_LOOP_ELEMENT_H

#include "AbstractElement.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>


class ForLoopElement : public AbstractElement {
public:
    ForLoopElement();
    std::shared_ptr<AbstractElement> clone() const override;

    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

};

#endif // FOR_LOOP_ELEMENT_H