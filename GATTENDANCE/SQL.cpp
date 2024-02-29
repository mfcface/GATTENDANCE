#include "pch.h"
#include "SQL.h"
#include "sqlite3.h"


SQL::SQL(const char* dbFile)
{

    int rc = sqlite3_open(dbFile, &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }
}

SQL::~SQL()
{
	sqlite3_close(db);
}

BOOL SQL::executeQuery(const char* query)
{
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// 历史记录用
void SQL::createTable(const char* tableName) {
    std::string tableSchema = "year TEXT, mouth TEXT, day TEXT, time TEXT, duration TEXT";
    std::string query = "CREATE TABLE IF NOT EXISTS " + std::string(tableName) + " (" + tableSchema + ");";
    executeQuery(query.c_str());
}


void SQL::dropTable(const char* tableName) {
    std::string query = "DROP TABLE IF EXISTS " + std::string(tableName) + ";";
    executeQuery(query.c_str());
}

//==========

void SQL::insertData(const char* table, const char* data)
{
    std::string query = "INSERT INTO " + std::string(table) + " VALUES (" + std::string(data) + ")";
    executeQuery(query.c_str());
}

void SQL::deleteData(const char* table, const char* condition)
{
    std::string query = "DELETE FROM " + std::string(table) + " WHERE " + std::string(condition);
    executeQuery(query.c_str());
}

void SQL::updateData(const char* table, const char* setValues, const char* condition)
{
    std::string query = "UPDATE " + std::string(table) + " SET " + std::string(setValues) + " WHERE " + std::string(condition);
    executeQuery(query.c_str());
}

std::vector<char*> SQL::selectData(const char* table, const char* columns, const char* condition)
{
    
    std::vector<char*> data;

    std::string query = "SELECT " + std::string(columns) + " FROM " + std::string(table);
    if (condition != nullptr) {
        query += " WHERE " + std::string(condition);
    }

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            
            int columnCount = sqlite3_column_count(stmt);
            for (int i = 0; i < columnCount; ++i) {
                const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                data.push_back(_strdup(value));
            }
        }
    }

    sqlite3_finalize(stmt);
    
    return data;
}
