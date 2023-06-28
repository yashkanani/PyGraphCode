#include "ElementUserInputs.h"
#include "BuilderContainer.h"

void ElementUserInputs::addContainer(const std::string& key, std::shared_ptr<BuilderContainer> container) {
    dataMap[key] = container;
}

void ElementUserInputs::addString(const std::string& key, const QString& value) {
    dataMap[key] = value;
}

std::shared_ptr<BuilderContainer> ElementUserInputs::getContainer(const std::string& key) const {
    auto it = dataMap.find(key);
    if (it != dataMap.end()) {
        if (auto container = std::get_if<std::shared_ptr<BuilderContainer>>(&it->second)) {
            return *container;
        }
    }
    return nullptr; // Return default value if key not found or value type is incorrect
}

QString ElementUserInputs::getString(const std::string& key) const {
    auto it = dataMap.find(key);
    if (it != dataMap.end()) {
        if (auto str = std::get_if<QString>(&it->second)) {
            return *str;
        }
    }
    return QString(); // Return default value if key not found or value type is incorrect
}
