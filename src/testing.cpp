#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

void log(std::string message) {
    std::cout << "[LOG] " << message << std::endl;
}

void printDocMembers(rapidjson::Document& document) {
    for (auto& member : document.GetObject()) {
        std::cout << member.name.GetString() << std::endl;
    }
}

void performTest() {
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

    printDocMembers(document);
    return 0;
}