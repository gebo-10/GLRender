#ifndef _DB_HPP
#define _DB_HPP
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