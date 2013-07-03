#include "sqlitepp/statement.hpp"

using namespace sqlitepp;

statement::statement(database * db, const ::std::string & query)
	: db_(db)
	, query_(query)
	, stmt_(NULL)
{
	assert(db_);
	int result;
	if ((result = ::sqlite3_prepare_v2(db_->db_, query.c_str(), query.size(), &stmt_, NULL)) != SQLITE_OK)
	{
		::std::string message = ::sqlite3_errmsg(db_->db_);
		throw std::runtime_error(message);
	}
}