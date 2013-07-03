#include "sqlitepp/statement.hpp"

using namespace sqlitepp;

statement::statement(database * db, const ::std::string & query)
	: db_(db)
	, query_(query)
	, stmt_(NULL)
	, last_result_(-1)
	, read_column_index_(-1)
{
	assert(db_);
	int result;
	if ((result = ::sqlite3_prepare_v2(db_->db_, query.c_str(), query.size(), &stmt_, NULL)) != SQLITE_OK)
	{
		::std::string message = ::sqlite3_errmsg(db_->db_);
		throw std::runtime_error(message);
	}
}

statement::~statement()
{
	if (stmt_)
	{
		::sqlite3_finalize(stmt_);
		stmt_ = NULL;
	}
}

bool statement::exec()
{
	assert(db_->db_);
	int result = ::sqlite3_step(stmt_);
	if (result == SQLITE_ERROR)
	{
		std::string error = ::sqlite3_errmsg(db_->db_);
		throw std::runtime_error(error);
	}
	else
	{
		// TODO: handle SQLITE_BUSY internally
		if (result == SQLITE_DONE)
		{
			if (last_result_ == SQLITE_ROW)
			{
				return false;
			}
			else
			{
				last_result_ = result;
				read_column_index_ = 0;
				return true;
			}
		}
		else if (result == SQLITE_ROW)
		{
			last_result_ = result;
			read_column_index_ = 0;
			return true;
		}
		else
		{
			assert(0 && "Not implemented yet");
		}
	}
}

int statement::get_int(int index)
{
	assert(db_->db_);
	assert(stmt_);
	assert(last_result_ == SQLITE_ROW);
	return ::sqlite3_column_int(stmt_, index);
}

std::string statement::get_string(int index)
{
	assert(db_->db_);
	assert(stmt_);
	assert(last_result_ == SQLITE_ROW);
	const unsigned char * text = ::sqlite3_column_text(stmt_, index);
	const char * c_string = reinterpret_cast<const char *>(text);
	return c_string;
}

statement & statement::operator>>(int & output)
{
	assert(read_column_index_ >= 0);
	output = this->get_int(read_column_index_++);
	return *this;
}

statement & statement::operator>>(std::string & output)
{
	assert(read_column_index_ >= 0);
	output = this->get_string(read_column_index_++);
	return *this;
}