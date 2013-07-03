CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (sqlitepp)

FIND_PACKAGE (Threads REQUIRED)

ADD_SUBDIRECTORY (deps)

INCLUDE_DIRECTORIES (
	${CMAKE_CURRENT_BINARY_DIR}
	include/
	deps/sqlite/
)

ADD_LIBRARY (sqlitepp
	src/database.cpp
	src/statement.cpp
)
TARGET_LINK_LIBRARIES (sqlitepp
	sqlite3
)

ENABLE_TESTING ()
ADD_SUBDIRECTORY (tests)
