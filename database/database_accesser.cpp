#include <string>
#include <iostream>
#include <cstdio>
#include <mysql.h>
#include <functional>
#include "json.h"
#include "database_accesser.h"

DatabaseAccesser::DatabaseAccesser(std::string config_file_name) {
    loadConfig(config_file_name);
}
DatabaseAccesser::DatabaseAccesser() {
    // loadConfig(config_file_name);
}
bool DatabaseAccesser::loadConfig(std::string config_file_name){
    JsonReader reader(config_file_name);
    JsonNode root = reader.getRootNode();
    host = root.getNodeStringValue("host");
    user = root.getNodeStringValue("user");
    password = root.getNodeStringValue("password");
    database = root.getNodeStringValue("database");
    port = root.getNodeIntegerValue("port");
}
bool DatabaseAccesser::initConnect() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host.c_str(),
            user.c_str(), password.c_str(), database.c_str(), port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
        return false;
    }
    return true;
}
bool DatabaseAccesser::performInsert(const char * sql) const {
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return false;
    }
    mysql_affected_rows(conn);
    return true;
}
bool DatabaseAccesser::performQuery(const char * sql, std::function<void (MYSQL_ROW)> callback) const {
    std::vector<MYSQL_ROW> rows;
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return false;
    }
    MYSQL_RES *res = mysql_use_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != NULL) {
        callback(row);
    }
    mysql_free_result(res);
    return true;
}
void DatabaseAccesser::closeConnect() {
    if (conn) {
        mysql_close(conn);
        conn = NULL;
    }
}
DatabaseAccesser::~DatabaseAccesser() {
    if (conn) {
        closeConnect();
    }
}