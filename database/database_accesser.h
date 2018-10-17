#pragma once
#ifndef DATABASE_ACCESSER_H
#define DATABASE_ACCESSER_H


#include <string>
#include <mysql.h>
#include <functional>

class DatabaseAccesser {
private:
    std::string host;
    std::string user;
    std::string password;
    std::string database;
    MYSQL *conn;
    int port;
public:
    DatabaseAccesser(std::string config_file_name);
    DatabaseAccesser();
    bool loadConfig(std::string config_file_name);
    bool initConnect();
    bool performInsert(const char * sql) const;
    bool performQuery(const char * sql, std::function<void (MYSQL_ROW)> callback) const;
    void closeConnect();
    ~DatabaseAccesser();
};

#endif // DATABASE_ACCESSER_H