#include <iostream>
#include "json.cpp"
int main() {
    std::string config_name = "config.json";
    JsonReader reader(config_name);
    JsonNode node = reader.getRootNode();
    std::cout << node.getNodeStringValue("host") << std::endl;
    std::cout << node.getNodeIntegerValue("port") << std::endl;
    std::cout << node.getNodeStringValue("user") << std::endl;
    std::cout << node.getNodeStringValue("password") << std::endl;
    std::cout << node.getNodeStringValue("database") << std::endl;
    
    // char * buffer = new char[10000];  

    
    
    // You can also read into a particular sub-value.
    // Get the value of the member of root named 'encoding',
    // and return 'UTF-8' if there is no such member.
    
    // Get the value of the member of root named 'plug-ins'; return a 'null' value if
    // there is no such member.
    // const Json::Value plugins = root["plug-ins"];
    // // Iterate over the sequence elements.
    // for ( int index = 0; index < plugins.size(); ++index )
    // std::cout << ( plugins[index].asString() );
    
    // // Try other datatypes. Some are auto-convertible to others.
    // std::cout << ( root["indent"].get("length", 3).asInt() );
    // std::cout << ( root["indent"].get("use_space", true).asBool() );
    // // Since Json::Value has an implicit constructor for all value types, it is not
    // // necessary to explicitly construct the Json::Value object.
    // // root["encoding"] = foo::getCurrentEncoding();
    // // root["indent"]["length"] = foo::getCurrentIndentLength();
    // // root["indent"]["use_space"] = foo::getCurrentIndentUseSpace();
    // // If you like the defaults, you can insert directly into a stream.
    // std::cout << root;
    // // Of course, you can write to `std::ostringstream` if you prefer.
    // // If desired, remember to add a linefeed and flush.
    // std::cout << std::endl;
    return 0;
}