#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H

#include <QPixmap>
#include <QString>
#include <qmetatype.h>
#include <qobject.h>

#include "BasicElementType.h"

class ElementUserInputs;
class CodeText;
class AbstractElement : public QObject {
    Q_OBJECT
public:
    AbstractElement();
    virtual ~AbstractElement() { } // Virtual destructor
    virtual std::shared_ptr<AbstractElement> clone() const = 0;
    QString getName() const;
    BasicElementType getType() const;
    QPixmap getImage() const;
    void setName(const QString& name);
    virtual std::shared_ptr<CodeText> getText(int indentLevel) const = 0;
    virtual QWidget* getViewWidget(QWidget* parent = nullptr) = 0;
    virtual void setUserInput(std::shared_ptr<ElementUserInputs> userInput) = 0;
    virtual std::shared_ptr<ElementUserInputs> getUserInput() = 0;

signals:
    void childValueChanged();

protected:
    BasicElementType type;
    QString name;
    QPixmap image;
};
Q_DECLARE_METATYPE(AbstractElement*);
#endif // ABSTRACT_ELEMENT_H
