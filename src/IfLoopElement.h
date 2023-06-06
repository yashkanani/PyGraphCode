#ifndef IF_LOOP_ELEMENT_H
#define IF_LOOP_ELEMENT_H

#include "AbstractElement.h"

class IfLoopElement : public AbstractElement {
public:
    IfLoopElement();
    std::shared_ptr<AbstractElement> clone() const override;
    QString getName() const override;
    QPixmap getImage() const override;
    std::shared_ptr<CodeText> getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;

private:
    QString name;
    QPixmap image;
};

#endif // IF_LOOP_ELEMENT_H