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

void performSimpleTest() {
    // 1. Parse a JSON string into DOM.
    const char* jsonString = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document document;
    document.Parse(jsonString);

    // 2. Modify it by DOM.
    rapidjson::Value& stars = document["stars"];
    stars.SetInt(stars.GetInt() + 1);

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
}

int main() {
    const char* jsonString = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document document;
    document.Parse(jsonString);

    printDocumentMembers(document);
    return 0;
}