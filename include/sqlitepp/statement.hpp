#if !defined(SQLITEPP_STATEMENT_HPP_INCLUDED_)
#define SQLITEPP_STATEMENT_HPP_INCLUDED_

#include <string>
#include <stdexcept>
#include <cassert>
#include "sqlitepp/database.hpp"
#include "sqlite3.h"

namespace sqlitepp {

class statement
{
public:
	statement(database * db, const ::std::string & query);
private:
	database * db_;
	std::string query_;
	::sqlite3_stmt * stmt_;
	void prepare();
};

} /* /sqlitepp */

#endif /* SQLITEPP_STATEMENT_HPP_INCLUDED_ */