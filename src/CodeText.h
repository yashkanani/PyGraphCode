#ifndef CODETEXT_H
#define CODETEXT_H

#include <QString>
#include <QStringList>

class CodeText {
public:
    CodeText(); // Default constructor
    void addToHeader(const QString& content);
    void addToBody(const QString& content);
    void increaseIndentOfBody();
    void removeIndentOfBody();
    void append(const CodeText& other);
    QString getResult() const;
    QStringList getHeader() const;
    QString getBody() const;

private:
    QStringList header;
    QString body;
    int indentLevel;
    static const int space = 4;
};

#endif // CODETEXT_H