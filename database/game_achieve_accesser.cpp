#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "game_achieve_accesser.h"
#include "database_accesser.h"
#include <json/json.h>

Record::Record(char * user_id, int level, int lv, int hp, int exp, char* snapshot, char * config, int is_public, int save_time) {
    parse(user_id, level, lv, hp, exp, snapshot, config, is_public, save_time);
}
Record::Record() {}
void Record::parse(char * user_id, int level, int lv, int hp, int exp, char* snapshot, char * config, int is_public, int save_time) {
    this->user_id = (char*)malloc(strlen(user_id));
    strcpy(this->user_id, user_id);
    this->level = level;
    this->lv = lv;
    this->hp = hp;
    this->exp = exp;
    this->snapshot = (char*)malloc(strlen(snapshot));
    strcpy(this->snapshot, snapshot);
    this->config = (char*)malloc(strlen(config));
    strcpy(this->config, config);
    this->is_public = is_public;
    this->save_time = save_time;
}
void Record::parse(MYSQL_ROW row) {
    // sprintf(sql, "select id, user_id, level, lv, hp, exp, snapshot, config, is_public, save_time from archives where user_id = '%s'",
    parse(row[1], atoi(row[2]), atoi(row[3]), atoi(row[4]), atoi(row[5]), row[6], row[7], atoi(row[8]), atoi(row[9]));
}

bool GameAchieveAccesser::downloadGameAchieve(std::vector<Record> &records, std::string user_id) {
    std::string config_name = "config.json";
    DatabaseAccesser db;
    db.loadConfig(config_name);
    db.initConnect();
    std::function<void (MYSQL_ROW)> add_record = [&](MYSQL_ROW row) { Record record;record.parse(row);return records.push_back(record); };
    char sql[1000];
    //TODO: sql数组大小不一定合适
    sprintf(sql, "select id, user_id, level, lv, hp, exp, snapshot, config, is_public, save_time from archives where user_id = '%s'",
            user_id.c_str());
    std::cout << sql;
    bool is_success = db.performQuery(sql, add_record);        
    db.closeConnect();
    if (is_success) {
        std::cout << "成功" << std::endl;
        return true;
    }
    return false;
}
bool GameAchieveAccesser::saveGameAchieveLocal(Record * record, std::string filename) {
    Json::Value value;
    value["user_id"] = record->user_id;
    value["level"] = record->level;
    value["lv"] = record->lv;
    value["hp"] = record->hp;
    value["exp"] = record->exp;

    Json::Reader reader;
    Json::Value snapshot, config;
    reader.parse(record->snapshot, snapshot);
    value["snapshot"] = snapshot;
    reader.parse(record->config, config);
    value["config"] = config;
    value["is_public"] = record->is_public;
    value["save_time"] = record->save_time;
    
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cout << "Error opening file";
        exit (1);
    }
    std::stringstream buffer;
    buffer << value;
    out << buffer.str();
    out.close();
    // std::string s = buffer.str();
    // Json::Reader reader;  
    // Json::Value root;
    // reader.parse(s, root);
    // this->root = JsonNode(root);
}
bool GameAchieveAccesser::uploadGameAchieve(const Record * record) {
    DatabaseAccesser db("config.json");
    db.initConnect();
    char sql[1000];
    //TODO: sql数组大小不一定合适
    sprintf(sql, "INSERT INTO `three_body_crisis`.`archives` (`user_id`, `level`, `lv`, `hp`, `exp`, `snapshot`, `config`, `is_public`, `save_time`) "
        "VALUES ('%s', '%d', '%d', '%d', '%d', '%s', '%s', '%d', '%d');", record->user_id, record->level, record->lv, record->hp, record->exp, record->snapshot, record->config, record->is_public, record->save_time);
    std::cout << sql;
    const bool is_success = db.performInsert(sql);        
    db.closeConnect();
    if (is_success) {
        std::cout << "上传成功" << std::endl;
        return true;
    }
    return false;
}