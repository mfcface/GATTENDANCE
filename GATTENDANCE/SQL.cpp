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

std::string SQL::ConvertUnicodeToUTF8(const CString& unicodeStr)
{

    int unicodeLength = unicodeStr.GetLength();
    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, unicodeStr, unicodeLength, nullptr, 0, nullptr, nullptr);
    char* utf8Buffer = new char[utf8Length + 1];
    WideCharToMultiByte(CP_UTF8, 0, unicodeStr, unicodeLength, utf8Buffer, utf8Length, nullptr, nullptr);
    std::string utf8Str(utf8Buffer, utf8Length);
    delete[] utf8Buffer;
    return utf8Str;
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

std::vector<SQL::info> SQL::selectData(const char* table, const char* columns, const char* condition)
{
    std::vector<SQL::info> result;

    char* errMsg = nullptr;
    char query[100];
    snprintf(query, sizeof(query), "SELECT %s FROM %s WHERE %s", columns, table, condition);

    
    int rc = sqlite3_exec(db, query, [](void* data, int argc, char** argv, char** azColName) 
        {
            std::vector<info>* result = static_cast<std::vector<info>*>(data);


            info rowInfo;
            for (int i = 0; i < argc; ++i)
            {
                if (std::string(azColName[i]) == "ID") {
                    rowInfo.ID = argv[i] ? std::string(argv[i]) : "NULL";
                }
                else if (std::string(azColName[i]) == "name") {
                    rowInfo.name = argv[i] ? std::string(argv[i]) : "NULL";
                }
                else if (std::string(azColName[i]) == "gender") {
                    rowInfo.gender = argv[i] ? std::string(argv[i]) : "NULL";
                }
                else if (std::string(azColName[i]) == "major") {
                    rowInfo.major = argv[i] ? std::string(argv[i]) : "NULL";
                }
            }

            result->push_back(rowInfo);

            return 0;
        }, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL´íÎó: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return result;
}