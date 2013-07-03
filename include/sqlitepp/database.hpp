#if !defined(SQLITEPP_DATABASE_HPP_INCLUDED_)
#define SQLITEPP_DATABASE_HPP_INCLUDED_

#include <string>
#include <stdexcept>
#include <sstream>
#include "sqlite3.h"

namespace sqlitepp {

class statement;

/**
 * This is a simple wrapper around SQLite connection.
 * You do not have to explicitly close connection.
 */
class database
{
public:
	friend class statement;
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
	/**
	 * Copies not allowed
	 */
	database(const database &);
	/**
	 * Assignment not allowed
	 */
	database & operator=(const database &);
};

} /* /sqlitepp */

#endif /* SQLITEPP_DATABASE_HPP_INCLUDED_ */