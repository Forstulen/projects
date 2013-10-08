cmake_minimum_required		(VERSION 2.6)

set				(CMAKE_MODULE_PATH	"${CMAKE_SOURCE_DIR}/cmake_modules")
set				(CMAKE_BUILD_TYPE	Debug)

#				Common: To add files in common in Server's and Client's
#					side see the dot cmake in the folder Common

#				Build: Server (see CMakeLists.txt in Server folder)

set				(PROJECT_TYPE		Server)
add_subdirectory		(Server)

#				Build: Client (see CMakeLists.txt in Client folder)

set				(PROJECT_TYPE		Client)
add_subdirectory		(Client)

#				Build: Libraries (see CMakeLists.txt in Common folder)

set				(PROJECT_TYPE		Libraries)
add_subdirectory		(Common)

#				Build: rtype-editor (see CMakeLists.txt in Editor folder)

set				(PROJECT_TYPE		Editor)
add_subdirectory		(Editor)
