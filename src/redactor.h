#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

/**
 * @brief A tool for redacting members of rapidjson::Document objects
 * 
 * @author Daniel McCoy Stephenson
 */
class Redactor {
    public:
        Redactor();
        void redactMemberByName(rapidjson::Value& value, std::string member, bool& success);
        void redactMemberByPath(rapidjson::Value& value, std::string path, bool& success);
        void searchForMemberByName(rapidjson::Value& value, std::string member, bool& success);
        void searchForMemberByPath(rapidjson::Value& value, std::string path, bool& success);

        void printValue(rapidjson::Value& valueToPrint);
        void printDocument(rapidjson::Document& document);
        rapidjson::Document getDocumentFromString(std::string jsonString);
        std::string stringifyDocument(rapidjson::Document& document);
    private:
        int indent;
        bool debugFlag;

        std::string getIndent(int numSpaces);
        std::string getTopLevelFromPath(std::string& path);
        void removeTopLevelFromPath(std::string& path);
};