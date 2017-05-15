#ifndef _DB_H
#define _DB_H
#pragma once
#include<Base.hpp>
#include <sqlite3.h>
class DB{
public:
	sqlite3 * db;
	DB();
	~DB();
	bool Init(char * db_file);
};
#endif