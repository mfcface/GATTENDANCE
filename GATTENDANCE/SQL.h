#pragma once
#include "sqlite/sqlite3.h"

class SQL
{
	CString sheetname;
	SQL();
	SQL(CString stname);
	CString find(CString Day ,CString what);
	BOOL Add(CTime T1,CTime T2);

};

