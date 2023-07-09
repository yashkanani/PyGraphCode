#ifndef PARAMETERUIBUILDER_H
#define PARAMETERUIBUILDER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QList>

class BuilderContainer;
class ParameterUIBuilder : public QWidget {
    Q_OBJECT
public:
    explicit ParameterUIBuilder(BuilderContainer* builderContainer, QWidget* parent = nullptr);

private slots:
    void updateParameterList(QWidget* element, bool addWidget, QString label = "");
    
   

private:
    void addToUI(QString label, QWidget* widget);
    void removeFromUI(QWidget* widget);
    void clearWidgets();

    QVBoxLayout* mainLayout;
    QList<QWidget*> widgetList;
    BuilderContainer* m_builderContainer;
};

#endif // PARAMETERUIBUILDER_H
