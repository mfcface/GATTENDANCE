#pragma once
#include "sqlite3.h"
class SQL
{
private:
    sqlite3* db;
public:
    BOOL executeQuery(const char* query);

public:
    SQL();
    SQL(const char* dbFile);
    ~SQL();
    void setDB(const char* dbFile);
   //建议仅在历史记录数据库中使用
    void createTable(const char* tableName);

    void dropTable(const char* tableName);
    //==========================
    
    bool havethis(const char* table, const char* columns, const char* condition);

    void insertData(const char* table, const char* data); 

    void deleteData(const char* table, const char* condition); 

    void updateData(const char* table, const char* setValues, const char* condition); 

    std::vector<std::string> selectData(const char* table, const char* columns, const char* condition);

};

