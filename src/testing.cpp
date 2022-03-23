#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

/**
 * Log a message to the console.
 */
void log(std::string message) {
    std::cout << "[LOG] " << message << std::endl;
}

/**
 * Print immediate child members of document.
 */
void printDocumentMembers(rapidjson::Document& document) {
    for (auto& m : document.GetObject()) {
        printf("Type of member '%s' is %s\n", m.name.GetString(), kTypeNames[m.value.GetType()]);
    }
}

/**
 * Convert a string into a document.
 */
rapidjson::Document getDocument(std::string jsonString) {
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    return document;
}

/**
 * Get a pre-defined document for testing purposes.
 */
rapidjson::Document getTestDocument() {
    const char* jsonString = "{\"project\":\"rapidjson\",\"stars\":10}";
    return getDocument(jsonString);
}

/**
 * Convert a document into a string.
 */
std::string stringifyDocument(rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

// tests ==========

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

// end of tests ==========

int main() {
    log("Executing program");

    performSimpleTest1();
    performSimpleTest2();

    log ("Program finished executing.");
    return 0;
}