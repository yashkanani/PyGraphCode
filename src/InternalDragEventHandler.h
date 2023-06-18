#ifndef INTERNALDRAGEVENTHANDLER_H
#define INTERNALDRAGEVENTHANDLER_H

#include <QObject>
#include <QEvent>

class InternalDragEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit InternalDragEventHandler(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

};

#endif // INTERNALDRAGEVENTHANDLER_H