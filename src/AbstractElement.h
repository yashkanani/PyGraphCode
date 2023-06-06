#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H

#include <QPixmap>
#include <QString>
#include <qmetatype.h>
#include <qobject.h>

class CodeText;
class AbstractElement : public QObject {
    Q_OBJECT
public:
    virtual ~AbstractElement() { } // Virtual destructor
    virtual std::shared_ptr<AbstractElement> clone() const = 0;
    virtual QString getName() const = 0;
    virtual QPixmap getImage() const = 0;
    virtual std::shared_ptr<CodeText> getText() const = 0;
    virtual QWidget* getViewWidget(QWidget* parent = nullptr) = 0;

signals:
    void childValueChanged();
};
Q_DECLARE_METATYPE(AbstractElement*);
#endif // ABSTRACT_ELEMENT_H