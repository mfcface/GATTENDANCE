#include "pch.h"
#include "SQL.h"
#include "sqlite3.h"

BOOL SQL::executeQuery(const char* query)
{
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

SQL::SQL() : db(nullptr) {}

SQL::SQL(const char* dbFile) : db(nullptr)
{
    setDB(dbFile);
}

SQL::~SQL()
{
    if (db) {
        sqlite3_close(db);
    }
}

void SQL::setDB(const char* dbFile)
{
    if (sqlite3_open(dbFile, &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
}

void SQL::createTable(const char* tableName)
{
    char query[100];
    snprintf(query, sizeof(query), "CREATE TABLE IF NOT EXISTS %s (id INTEGER PRIMARY KEY, name TEXT)", tableName);
    executeQuery(query);
}

void SQL::dropTable(const char* tableName)
{
    char query[50];
    snprintf(query, sizeof(query), "DROP TABLE IF EXISTS %s", tableName);
    executeQuery(query);
}

bool SQL::havethis(const char* table, const char* columns, const char* condition)
{
    char query[100];
    snprintf(query, sizeof(query), "SELECT %s FROM %s WHERE %s", columns, table, condition);
    return executeQuery(query);
}

void SQL::insertData(const char* table, const char* data)
{
    char query[100];
    snprintf(query, sizeof(query), "INSERT INTO %s VALUES (%s)", table, data);
    executeQuery(query);
}

void SQL::deleteData(const char* table, const char* condition)
{
    char query[100];
    snprintf(query, sizeof(query), "DELETE FROM %s WHERE %s", table, condition);
    executeQuery(query);
}

void SQL::updateData(const char* table, const char* setValues, const char* condition)
{
    char query[100];
    snprintf(query, sizeof(query), "UPDATE %s SET %s WHERE %s", table, setValues, condition);
    executeQuery(query);
}

std::vector<std::string> SQL::selectData(const char* table, const char* columns, const char* condition)
{
    std::vector<std::string> result;
    char query[100];
    snprintf(query, sizeof(query), "SELECT %s FROM %s WHERE %s", columns, table, condition);

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int numColumns = sqlite3_column_count(stmt);
        for (int i = 0; i < numColumns; ++i) {
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            result.push_back(value);
        }
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return result;
}