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
	~statement();
	bool exec();
	int get_int(int index);
	std::string get_string(int index);
	statement & operator>>(int & output);
	statement & operator>>(std::string & output);
private:
	database * db_;
	std::string query_;
	::sqlite3_stmt * stmt_;
	int last_result_;
	// Used in operator>> for counting internally
	int read_column_index_;
	statement(const statement &);
	statement & operator=(const statement &);
};

} /* /sqlitepp */

#endif /* SQLITEPP_STATEMENT_HPP_INCLUDED_ */