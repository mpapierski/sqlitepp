#include "sqlitepp/database.hpp"

using namespace sqlitepp;

void database::initialize()
{
	int result;
	if ((result = ::sqlite3_initialize()) != SQLITE_OK)
	{
		std::ostringstream os;
		os << "Unable to initialize SQLite engine. Error code: " << result;
		throw std::runtime_error(os.str());
	}
}

void database::shutdown()
{
	int result;
	if ((result = ::sqlite3_shutdown()) != SQLITE_OK)
	{
		std::ostringstream os;
		os << "Unable to shutdown SQLite engine. Error code: " << result;
		throw std::runtime_error(os.str());
	}
}

database::database(const std::string & database)
	: db_(NULL)
{
	int result;
	if ((result = ::sqlite3_open(database.c_str(), &db_)) != SQLITE_OK)
	{
		if (!db_)
		{
			// SQLite was unable to allocate memory
			throw std::bad_alloc();
		}
		// Create a copy of error message
		std::string error_str = ::sqlite3_errmsg(db_);
		throw std::runtime_error(error_str);
	}
}

database::~database()
{
	if (db_)
	{
		::sqlite3_close(db_);
		db_ = NULL;
	}
}
