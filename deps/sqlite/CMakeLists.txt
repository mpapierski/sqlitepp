CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

FIND_PACKAGE (Threads REQUIRED)
FIND_LIBRARY (DL_LIBRARY dl)

# Add sqlite3 source as static library
ADD_LIBRARY (sqlite3
	sqlite3.c
)
TARGET_LINK_LIBRARIES (sqlite3
	${CMAKE_THREAD_LIBS_INIT}
	${DL_LIBRARY}
)
# Add shell executable for databases
ADD_EXECUTABLE (shell
	shell.c
)
TARGET_LINK_LIBRARIES (shell
	sqlite3
)
