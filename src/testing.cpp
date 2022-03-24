#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
int indent = 0;

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

std::string getIndent(int numSpaces) {
    std::string toReturn = "";
    for (int i = 0; i < numSpaces*2; i++) {
        toReturn = toReturn + " ";
    }
    return toReturn;
}

void printObject(rapidjson::Value& objectToPrint) {
    for (auto& m : objectToPrint.GetObject()) {
        std::string name = m.name.GetString();
        std::string type = kTypeNames[m.value.GetType()];

        std::cout << getIndent(indent) << name << std::endl;

        if (type == "Object") {
            indent++;
            auto& foundObject = objectToPrint[name.c_str()];
            printObject(foundObject);
            indent--;
        }
    }
}

void printDocument(rapidjson::Document& document) {
    for (auto& m : document.GetObject()) {
        std::string name = m.name.GetString();
        std::string type = kTypeNames[m.value.GetType()];

        std::cout << name << std::endl;

        if (type == "Object") {
            indent++;
            auto& object = document[name.c_str()];
            printObject(object);
            indent--;
        }
    }
}

// END OF HELPER METHODS ==================================================

/**
 * Get a pre-defined document for testing purposes.
 */
rapidjson::Document getTestDocument() {
    const char* jsonString = "{\"name\":\"Alex\",\"age\":24,\"subjects\":{\"s1\":\"C++\",\"s2\":\"software engineering\",\"s3\":\"Data Science\"}}";
    return getDocument(jsonString);
}

int main() {
    log("Executing program");

    rapidjson::Document document = getTestDocument();
    printDocument(document);
    
    log("Program finished executing");
    return 0;
}