#include "redactor.h"

Redactor::Redactor() {
    indent = 0;
    debugFlag = false;
}

void Redactor::redactAllInstancesOfMemberByName(rapidjson::Value& value, std::string member, bool& success) {
    if (value.IsObject()) {
        while (value.HasMember(member.c_str())) {
            value.RemoveMember(member.c_str());
            success = true;
        }
        for (auto& m : value.GetObject()) {
            std::string type = kTypeNames[m.value.GetType()];
            if (type == "Object" || type == "Array") {
                std::string name = m.name.GetString();
                auto& v = value[name.c_str()];
                redactAllInstancesOfMemberByName(v, member, success);
            }
        }
    }
    else if (value.IsArray()) {
        for (auto& m : value.GetArray()) {
            std::string type = kTypeNames[m.GetType()];
            if (type == "Object" || type == "Array") {
                redactAllInstancesOfMemberByName(m, member, success);
            }
        }
    }
}

void Redactor::redactMemberByPath(rapidjson::Value& value, std::string path, bool& success) {
    std::string topLevel = getTopLevelFromPath(path);
    if (value.IsObject()) {
        if (value.HasMember(topLevel.c_str())) {
            value.RemoveMember(topLevel.c_str());
            success = true;
        }
        for (auto& m : value.GetObject()) {
            std::string type = kTypeNames[m.value.GetType()];
            if (type == "Object" || type == "Array") {
                std::string name = m.name.GetString();
                auto& v = value[name.c_str()];
                removeTopLevelFromPath(path);
                redactMemberByPath(v, path, success);
            }
        }
    }
    else if (value.IsArray()) {
        for (auto& m : value.GetArray()) {
            std::string type = kTypeNames[m.GetType()];
            if (type == "Object" || type == "Array") {
                removeTopLevelFromPath(path);
                redactMemberByPath(m, path, success);
            }
        }
    }
}

void Redactor::searchForMemberByName(rapidjson::Value& value, std::string member, bool& success) {
    if (success) {
        // return if search has already succeeded
        return;
    }
    if (value.IsObject()) {
        if (value.HasMember(member.c_str())) {
            success = true;
        }
        for (auto& m : value.GetObject()) {
            std::string type = kTypeNames[m.value.GetType()];
            if (type == "Object" || type == "Array") {
                std::string name = m.name.GetString();
                auto& v = value[name.c_str()];
                searchForMemberByName(v, member, success);
            }
        }
    }
    else if (value.IsArray()) {
        for (auto& m : value.GetArray()) {
            std::string type = kTypeNames[m.GetType()];
            if (type == "Object" || type == "Array") {
                searchForMemberByName(m, member, success);
            }
        }
    }
}

void Redactor::searchForMemberByPath(rapidjson::Value& value, std::string path, bool& success) {
    if (success) {
        // return if search has already succeeded
        return;
    }
    std::string topLevel = getTopLevelFromPath(path);
    if (value.IsObject()) {
        if (value.HasMember(topLevel.c_str())) {
            success = true;
        }
        for (auto& m : value.GetObject()) {
            std::string type = kTypeNames[m.value.GetType()];
            if (type == "Object" || type == "Array") {
                std::string name = m.name.GetString();
                auto& v = value[name.c_str()];
                removeTopLevelFromPath(path);
                searchForMemberByPath(v, path, success);
            }
        }
    }
    else if (value.IsArray()) {
        for (auto& m : value.GetArray()) {
            std::string type = kTypeNames[m.GetType()];
            if (type == "Object" || type == "Array") {
                removeTopLevelFromPath(path);
                searchForMemberByPath(m, path, success);
            }
        }
    }
}

void Redactor::printValue(rapidjson::Value& valueToPrint) {
    if (valueToPrint.IsObject()) {
        for (auto& m : valueToPrint.GetObject()) {
            std::string name = m.name.GetString();
            std::string type = kTypeNames[m.value.GetType()];
            std::cout << getIndent(indent) << name  << " - " << type << std::endl;
            if (type == "Object" || type == "Array") {
                indent++;
                auto& value = valueToPrint[name.c_str()];
                printValue(value);
                indent--;
            }
        }
    }
    else if (valueToPrint.IsArray()) {
        for (auto& m : valueToPrint.GetArray()) {
            std::string type = kTypeNames[m.GetType()];
            if (type == "Object" || type == "Array") {
                indent++;
                printValue(m);
                indent--;
            }
        }
    }
}

void Redactor::printDocument(rapidjson::Document& document) {
    printValue(document);
}

/**
 * Convert a string into a document.
 */
rapidjson::Document Redactor::getDocumentFromString(std::string jsonString) {
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    return document;
}

/**
 * Convert a document into a string.
 */
std::string Redactor::stringifyDocument(rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

std::string Redactor::getIndent(int numSpaces) {
    std::string toReturn = "";
    for (int i = 0; i < numSpaces*2; i++) {
        toReturn = toReturn + " ";
    }
    return toReturn;
}

std::string Redactor::getTopLevelFromPath(std::string& path) {
    int firstDot = path.find(".");
    if (firstDot != std::string::npos) {
        return path.substr(0, firstDot);
    }
    return path;
}

void Redactor::removeTopLevelFromPath(std::string& path) {
    int firstDot = path.find(".");
    if (firstDot != std::string::npos) {
        path = path.substr(firstDot + 1);
    }
}