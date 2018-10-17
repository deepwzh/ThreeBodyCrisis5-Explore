#pragma once
#ifndef JSON_H
#define JSON_H


#include <string>
#include <vector>
#include <json/json.h>
class JsonNode {
private:
    Json::Value node;
public:
    JsonNode(Json::Value value);
    JsonNode();
    int size() const;
    JsonNode operator[] (std::string key) const;
    JsonNode operator[] (int index) const;
    std::string asString() const;
    bool asBool() const;
    int asInt() const;
    int getNodeIntegerValue(const std::string &key) const;
    bool getNodeBoolValue(const std::string &key) const;
    JsonNode getNodeValue(const std::string &key) const;
    std::string getNodeStringValue(const std::string &key) const;
    std::vector<int> getNodeChildIntegerValues(const std::string &key) const;
    std::vector<std::string> getNodeChildStringValues(const std::string &key) const;
    std::vector<bool> getNodeChildBoolValues(const std::string &key) const;
    
};

class JsonReader{
private:
    std::string filename;
    JsonNode root;
public:
    JsonReader(std::string filename);
    JsonNode getRootNode() const;
};



#endif //JSON_H