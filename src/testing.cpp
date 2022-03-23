#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

void log(std::string message) {
    std::cout << "[LOG] " << message << std::endl;
}

void printDocumentMembers(rapidjson::Document& document) {
    for (auto& m : document.GetObject()) {
        printf("Type of member '%s' is %s\n", m.name.GetString(), kTypeNames[m.value.GetType()]);
    }
}

rapidjson::Document getDocument(std::string jsonString) {
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    return document;
}

rapidjson::Document getTestDocument() {
    const char* jsonString = "{\"project\":\"rapidjson\",\"stars\":10}";
    return getDocument(jsonString);
}

std::string stringifyDocument(rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

void performSimpleTest1() {
    // 1. Parse a JSON string into DOM.
    rapidjson::Document document = getTestDocument();

    // 2. Modify it by DOM.
    rapidjson::Value& stars = document["stars"];
    stars.SetInt(stars.GetInt() + 1);

    // 3. Stringify the DOM
    std::string stringifiedDocument = stringifyDocument(document);

    // Output {"project":"rapidjson","stars":11}
    std::cout << stringifiedDocument << std::endl;
}

void performSimpleTest2() {
    rapidjson::Document document = getTestDocument();
    printDocumentMembers(document);
}

int main() {
    log("Executing program");

    performSimpleTest1();
    performSimpleTest2();

    log ("Program finished executing.");
    return 0;
}