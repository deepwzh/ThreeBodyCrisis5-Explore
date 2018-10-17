#include "json.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <json/json.h>
int JsonNode::size() const {
    return this->node.size();
}
JsonNode::JsonNode() {

}
JsonNode::JsonNode(Json::Value value) {
    this->node = value;
}
JsonNode JsonNode::operator [] (std::string key) const {
    return this->node[key];
}
JsonNode JsonNode::operator [] (int index) const {
    return this->node[index];
}
JsonReader::JsonReader(std::string filename) {
    this->filename = filename;
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Error opening file";
        exit (1);
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string s = buffer.str();
    Json::Reader reader;  
    Json::Value root;
    buffer >> root;
    reader.parse(s, root);
    this->root = JsonNode(root);
}
JsonNode JsonReader::getRootNode() const {
    return root;
}
std::string JsonNode::asString() const {
    return this->node.asString();
}
bool JsonNode::asBool() const {
    return this->node.asBool();
}
int JsonNode::asInt() const {
    return this->node.asInt();
}
std::string JsonNode::getNodeStringValue(const std::string &key) const {
    std::string value = this->node[key].asString();
    return value;
}
int JsonNode::getNodeIntegerValue(const std::string &key) const {
    int value = this->node[key].asInt();
    return value;
}
bool JsonNode::getNodeBoolValue(const std::string &key) const {
    bool value = this->node[key].asBool();
    return value;
}
JsonNode JsonNode::getNodeValue(const std::string &key) const {
    const Json::Value values = node[key];
    return values;
}
std::vector<int> JsonNode::getNodeChildIntegerValues(const std::string &key) const {
    const JsonNode &cur_node = getNodeValue(key);
    std::vector<int> results;
    for (int index = 0; index < cur_node.size(); index++) {
        results.push_back(cur_node[index].asInt());
    }
}
std::vector<std::string> JsonNode::getNodeChildStringValues(const std::string &key) const {
    const JsonNode &cur_node = getNodeValue(key);
    std::vector<std::string> results;
    for (int index = 0; index < cur_node.size(); index++) {
        results.push_back(cur_node[index].asString());
    }
}
std::vector<bool> JsonNode::getNodeChildBoolValues(const std::string &key) const {
    const JsonNode & cur_node = getNodeValue(key);
    std::vector<bool> results;
    for (int index = 0; index < cur_node.size(); index++) {
        results.push_back(cur_node[index].asBool());
    }
}