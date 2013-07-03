#if !defined(SQLITEPP_DATABASE_HPP_INCLUDED_)
#define SQLITEPP_DATABASE_HPP_INCLUDED_

#include <string>
#include <stdexcept>
#include <sstream>
#include "sqlite3.h"

namespace sqlitepp {

/**
 * This is a simple wrapper around SQLite connection.
 * You do not have to explicitly close connection.
 */
class database
{
public:
	/**
	 * Create new database connection.
	 * @param address Database name (like "db.sqlite")
	 */
	database(const ::std::string & address); // throws
	~database();
	static void initialize();
	static void shutdown();
private:
	/**
	 * Connection pointer
	 */
	::sqlite3 * db_;
};

} /* /sqlitepp */

#endif /* SQLITEPP_DATABASE_HPP_INCLUDED_ */