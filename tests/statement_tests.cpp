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

BOOST_AUTO_TEST_CASE (test_execute_simple_statement)
{
	sqlitepp::statement stmt(&db, "CREATE TABLE test (col1, col2, col3)");
	bool result = stmt.exec();
	BOOST_REQUIRE(result);
}

BOOST_AUTO_TEST_CASE (test_execute_simple_statement_with_data)
{
	sqlitepp::statement stmt(&db, "SELECT 1");
	bool result = stmt.exec();
	BOOST_REQUIRE(result);
	int col1 = stmt.get_int(0);
	BOOST_CHECK_EQUAL(col1, 1);
	result = stmt.exec();
	BOOST_REQUIRE(!result);
}

BOOST_AUTO_TEST_CASE (test_execute_simple_statement_with_multicolumn_data)
{
	sqlitepp::statement stmt(&db, "SELECT 1, 2, 3");
	bool result = stmt.exec();
	BOOST_REQUIRE(result);
	int col1 = stmt.get_int(0);
	int col2 = stmt.get_int(1);
	int col3 = stmt.get_int(2);
	BOOST_CHECK_EQUAL(col1, 1);
	BOOST_CHECK_EQUAL(col2, 2);
	BOOST_CHECK_EQUAL(col3, 3);
}

BOOST_AUTO_TEST_CASE (test_execute_simple_statement_with_multicolumn_data_shift_operator)
{
	sqlitepp::statement stmt(&db, "SELECT 1, 2, 3, 'hello world', 4, 5");
	bool result = stmt.exec();
	BOOST_REQUIRE(result);
	int col1, col2, col3;
	std::string col4;
	int col5, col6;
	stmt >> col1 >> col2 >> col3 >> col4 >> col5 >> col6;

	BOOST_CHECK_EQUAL(col1, 1);
	BOOST_CHECK_EQUAL(col2, 2);
	BOOST_CHECK_EQUAL(col3, 3);
	BOOST_CHECK_EQUAL(col4, "hello world");
	BOOST_CHECK_EQUAL(col5, 4);
	BOOST_CHECK_EQUAL(col6, 5);
	result = stmt.exec();
	BOOST_REQUIRE(!result);
}

BOOST_AUTO_TEST_SUITE_END ()