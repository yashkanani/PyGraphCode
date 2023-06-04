#ifndef RESULTEDTEXTVIEW_H
#define RESULTEDTEXTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include "BuilderContainer.h"

class ResultedTextView : public QWidget {
    Q_OBJECT
public:
    ResultedTextView(QWidget* parent = nullptr, BuilderContainer* builderContainer = nullptr);

private slots:
    void updateText();

signals:
    void updateResultedTextView();

private:
    BuilderContainer* m_builderContainer;
    QLabel* m_resultedTextLabel;
};

#endif // RESULTEDTEXTVIEW_H