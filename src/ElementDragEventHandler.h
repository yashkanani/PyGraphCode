#include <qobject.h>

class ElementDragEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit ElementDragEventHandler(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
};

