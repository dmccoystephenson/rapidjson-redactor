#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

// HELPER METHODS ====================================================

/**
 * Log a message to the console.
 */
void log(std::string message) {
    std::cout << "[LOG] " << message << std::endl;
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
 * Convert a document into a string.
 */
std::string stringifyDocument(rapidjson::Document& document) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

/**
 * Print immediate child members of document.
 */
void printDocumentMemberTypes(rapidjson::Document& document) {
    for (auto& m : document.GetObject()) {
        printf("Type of member '%s' is %s\n", m.name.GetString(), kTypeNames[m.value.GetType()]);
    }
}

// END OF HELPER METHODS ==================================================

/**
 * Get a pre-defined document for testing purposes.
 */
rapidjson::Document getTestDocument() {
    const char* jsonString = "{\"project\":\"rapidjson\",\"stars\":10}";
    return getDocument(jsonString);
}

void performSimpleTest() {
    // parse a JSON string into DOM
    rapidjson::Document document = getTestDocument();

    // modify it by DOM
    rapidjson::Value& stars = document["stars"];
    stars.SetInt(stars.GetInt() + 1);

    // stringify and print the DOM
    std::string stringifiedDocument = stringifyDocument(document);
    std::cout << stringifiedDocument << std::endl;
}

int main() {
    log("Executing program");

    performSimpleTest();

    log ("Program finished executing.");
    return 0;
}