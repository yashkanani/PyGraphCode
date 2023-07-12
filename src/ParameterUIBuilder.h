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

private slots:
    void updateParameterList(QWidget* element, bool addWidget, QString label = "");

private:
    void addToUI(QString label, QWidget* widget);
    void removeFromUI(QWidget* widget);
    void clearWidgets();

    QVBoxLayout* mainLayout;
    QHash<QWidget*, QLabel*> widgetLabelMap;
    BuilderContainer* m_builderContainer;
};

#endif // PARAMETERUIBUILDER_H
