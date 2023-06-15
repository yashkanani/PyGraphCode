#include "CodeText.h"

CodeText::CodeText() : indentLevel(0)
{
    // Default constructor implementation
}
CodeText::CodeText(int _indentLevel)
    : indentLevel(_indentLevel)
{
    // Default constructor implementation
}

void CodeText::addToHeader(const QString& content)
{
    // Add the specified content to the header
    // You can implement the desired logic here, such as appending the content to the header QStringList
    header.append(content);
}

void CodeText::addToBody(const QString& content)
{
    // Add the specified content to the body with the current indentation level
    body.append(QString(indentLevel, ' ') + content);
}

void CodeText::increaseIndentOfBody()
{
    // Increase the indent level by space (4)
    indentLevel += space;
}

void CodeText::removeIndentOfBody()
{
    // Decrease the indent level by space (4) if it's greater than or equal to space (4)
    if (indentLevel >= space) {
        indentLevel -= space;
    }
}
int CodeText::getCurrentIndentOfBody() const
{
    return indentLevel;
}

void CodeText::append(const CodeText& other)
{
    // Append the header and body of the other CodeText instance to the current instance
    header.append(other.header);
    body.append(other.body);
}

QString CodeText::getResult() const
{
    QString result;

    // Append the header
    for (const QString& line : header) {
        result += line + "\n";
    }

    // Append the body
    result += body;

    return result;
}

QStringList CodeText::getHeader() const
{
    // Return a copy of the header
    return header;
}

QString CodeText::getBody() const
{
    // Return the body
    return body;
}