#ifndef PARAMETERUIBUILDER_H
#define PARAMETERUIBUILDER_H

#include <QHash>
#include <QVBoxLayout>
#include <QWidget>

class BuilderContainer;
class QLabel;

class ParameterUIBuilder : public QWidget {
    Q_OBJECT
public:
    explicit ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent = nullptr);
    void addToUI(QString label, QWidget* widget);
    void removeFromUI(QWidget* widget);
   

private slots:
    void updateParameterList();

private:
    
    void handleParentDestroyed(QObject* parentObj);
    void clearWidgets();

    QVBoxLayout* parameterLay;
    QHash<QWidget*, QLabel*> widgetLabelMap;
    QHash<QWidget*, QObject*> originalParents;
    BuilderContainer* m_builderContainer;
};

#endif // PARAMETERUIBUILDER_H
