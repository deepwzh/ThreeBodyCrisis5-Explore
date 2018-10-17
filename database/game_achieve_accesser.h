#pragma once
#ifndef GAME_ACHIEVE_ACCESSER
#define GAME_ACHIEVE_ACCESSER

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <mysql.h>


struct Record {
    char * user_id;
    int level;
    int lv;
    int hp;
    int exp;
    char *snapshot;
    char *config;
    int save_time;
    int is_public;
    Record(char * user_id, int level, int lv, int hp, int exp, char* snapshot, char * config, int is_public, int save_time);
    Record();
    void parse(char * user_id, int level, int lv, int hp, int exp, char* snapshot, char * config, int is_public, int save_time);
    void parse(MYSQL_ROW row);
};
class GameAchieveAccesser {
public:
    bool static downloadGameAchieve(std::vector<Record> &records, std::string user_id);
    bool static saveGameAchieveLocal(Record * record, std::string filename);
    bool static uploadGameAchieve(const Record * record);
};

#endif //GAME_ACHIEVE_ACCESSER