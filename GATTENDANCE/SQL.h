#pragma once
#include "sqlite3.h"

class SQL
{
private:
    sqlite3* db;
public:
    BOOL executeQuery(const char* query);
    static struct info {
        std::string ID;
        std::string name;
        std::string gender;
        std::string major;
    };
    

    static std::string ConvertUnicodeToUTF8(const CString& unicodeStr);
    static CString Utf8ToCString(const std::string& utf8String) {
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wstr, len);
        CString cstr(wstr);
        delete[] wstr;
        return cstr;
    }
public:
    SQL();
    SQL(const char* dbFile);
    ~SQL();
    void setDB(const char* dbFile);
   //建议仅在历史记录数据库中使用
    void createTable(const char* tableName);

    void dropTable(const char* tableName);
    //==========================
    
 
    void insertData(const char* table, const char* data); 

    void deleteData(const char* table, const char* condition); 

    void updateData(const char* table, const char* setValues, const char* condition);
    
    std::vector<SQL::info> selectData(const char* table, const char* columns, const char* condition);


};

