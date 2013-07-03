#define BOOST_TEST_MODULE statement

#include <boost/test/included/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <sqlitepp/sqlitepp.hpp>

struct F
{
	sqlitepp::database db;
	F()	: db(":memory:") {}
	~F() {}
};

BOOST_FIXTURE_TEST_SUITE(statement_suite, F)

BOOST_AUTO_TEST_CASE (test_simple_statement)
{
	sqlitepp::statement stmt(&db, "SELECT 1, 2, 3");
}

BOOST_AUTO_TEST_CASE (test_failed_statement)
{
	BOOST_REQUIRE_THROW(sqlitepp::statement(&db, "SELECT hello from \"world\""), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END ()