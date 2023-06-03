#ifndef FOR_LOOP_ELEMENT_H
#define FOR_LOOP_ELEMENT_H

#include "AbstractElement.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>

class PlaceHolder;
class ForLoopElement : public AbstractElement {
public:
    ForLoopElement();

    QString getName() const override;
    QPixmap getImage() const override;
    QString getText() const override;
    QWidget* getViewWidget(QWidget* parent = nullptr) override;
  

private:
    QString name;
    QPixmap image;

    std::shared_ptr<PlaceHolder> startLoop;
    std::shared_ptr<PlaceHolder> endLoop;
    std::shared_ptr<PlaceHolder> body;
    std::shared_ptr<PlaceHolder> condition;

    
};

#endif // FOR_LOOP_ELEMENT_H