#ifndef ELEMENTUSERINPUTS_H
#define ELEMENTUSERINPUTS_H

#include <map>
#include <variant>
#include <QString>
#include <memory>

class BuilderContainer;
class ElementUserInputs {
public:
    void addContainer(const std::string& key, std::shared_ptr<BuilderContainer> container);
    void addString(const std::string& key, const QString& value);
    std::shared_ptr<BuilderContainer> getContainer(const std::string& key) const;
    QString getString(const std::string& key) const;
    const std::map<std::string, std::variant<std::shared_ptr<BuilderContainer>, QString>>& getAllUserInputs() const;

private:
    std::map<std::string, std::variant<std::shared_ptr<BuilderContainer>, QString>> dataMap;
};

#endif // ELEMENTUSERINPUTS_H
