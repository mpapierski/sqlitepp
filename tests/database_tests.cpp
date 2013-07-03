#define BOOST_TEST_MODULE database

#include <boost/test/included/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <sqlitepp/sqlitepp.hpp>

namespace fs = boost::filesystem;

struct Config
{
	Config()
	{
		sqlitepp::database::initialize();
	}
	~Config()
	{
		sqlitepp::database::shutdown();
	}
};

BOOST_GLOBAL_FIXTURE (Config)

struct F
{
	fs::path temp_dir;
	F()
		: temp_dir(boost::filesystem::unique_path())
	{
		fs::create_directories(temp_dir);
	}
	~F()
	{
		boost::system::error_code errcode;
		fs::remove_all(temp_dir);
	}
};

BOOST_FIXTURE_TEST_SUITE (database_suite, F)

BOOST_AUTO_TEST_CASE (test_file_database_is_open)
{
	std::string filename = "test.db";
	fs::path p = temp_dir / filename;
	boost::filesystem::path temp = temp_dir / filename;
	sqlitepp::database db(temp.native());
	BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(temp), "Unable to open database at: " << temp);
	fs::remove(temp);
}

BOOST_AUTO_TEST_CASE (test_unable_to_open_database)
{
	BOOST_REQUIRE_MESSAGE(!fs::exists("unknown/path/will/fail"), "You should cleanup your test environment!");
	BOOST_REQUIRE_THROW(sqlitepp::database("unknown/path/will/fai/database.sqlite"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE (test_in_memory_database_is_open)
{
	sqlitepp::database db("");
}

BOOST_AUTO_TEST_CASE (test_in_memory_database_is_open_2)
{
	sqlitepp::database db(":memory:");
}

BOOST_AUTO_TEST_SUITE_END ()
