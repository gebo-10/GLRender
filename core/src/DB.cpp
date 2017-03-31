#include <DB.h>
DB::DB()
{
	db = NULL;
}

DB::~DB()
{

}

bool DB::Init(char * db_file)
{
	
	int nRes = sqlite3_open(db_file, &db);
	if (nRes != SQLITE_OK)
	{
		LOG(ERROR) << "Open database fail: " << sqlite3_errmsg(db);
		return false;
	}
	LOG(INFO) << "Open database success"<<endl;
	return true;
}

