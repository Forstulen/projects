cmake_minimum_required		(VERSION	2.6)

#		Project Name

project				(Editor)

#			Set variable for the path of sub folder

if (WIN32)

	set						(QT_DIR 				C:/Qt/4.7.3/)
	set						(QT_BINARY_DIR			${QT_DIR}bin/)
	set						(QT_INCLUDE_DIR			${QT_DIR}include/)
	set						(QT_HEADERS_DIR			${QT_DIR}include/)
	set						(QT_LIBRARY_DIR			${QT_DIR}lib/)
	set						(QT_LIBRARY_DIR_TMP		${QT_DIR}lib/)
	set						(QT_QMAKE_EXECUTABLE	${QT_BINARY_DIR}qmake.exe)
	INCLUDE_DIRECTORIES		(QT_INCLUDE_DIR)

endif ()

FIND_PACKAGE			(Qt4 REQUIRED)
set				(QT_USE_QTNETWORK	TRUE)
set				(QT_USE_QTXML		TRUE)

INCLUDE				(${QT_USE_FILE})
ADD_DEFINITIONS			(${QT_DEFINITIONS})

#			Common: Including files in common.
#			(See common_macors.cmake to add files from the Common folder)

include (../Common/common_macros.cmake)

  INCLUDE_DIRECTORIES(
			    ${CMAKE_CURRENT_BINARY_DIR}
			    ${CMAKE_CURRENT_SOURCE_DIR}
			    ${COMMON_INC}
      )


QT4_WRAP_UI			(Editor_ui mainwindow.ui)
QT4_WRAP_CPP		(Editor_moc
                      mainwindow.h
                        mapitem.h
                        rtypeitem.h
                        )

#		Editor Sources

set				(SRCS	main.cpp
					mainwindow.cpp
					mapitem.cpp
					rtypeitem.cpp
					${PARSER_SRCS}
					${PARSER_HDRS}
					${RTDB_SRCS}
					${RTDB_HDRS}
					${TOOLS_HDRS}
					${TOOLS_SRCS}
					${CONVERSIONS_SRCS}
					${CONVERSIONS_HDRS}
					 )

#		Editor Headers

set				(HDRS	mainwindow.h rtypeitem.h mapitem.h IDrawableObject.hpp)


#		Creation of the executable (If you want to add sources or header,
#		use the above)

set				(EXECUTABLE_OUTPUT_PATH		../Editor/)

add_executable			(rtype-editor
							${HDRS}
							${RTDB_HDRS}
							${CONVERSIONS_HDRS}
							${SRCS}
							${RTDB_SRCS}
							${CONVERSIONS_SRCS}
							${Editor_moc}
							${Editor_ui})

TARGET_LINK_LIBRARIES		(rtype-editor		${QT_LIBRARIES})

IF				(WIN32)


	SOURCE_GROUP		(Common\\Conversions FILES
					${CONVERSIONS}Conversions.hpp
					${CONVERSIONS}Conversions.cpp)

	SOURCE_GROUP		(Common\\Parser FILES
					${PARSER}ConsumerParser.hpp
					${PARSER}ConsumerParser.cpp
					${PARSER}ParserXPM.hpp
					${PARSER}ParserXPM.cpp
					${PARSER}ParserMap.hpp
					${PARSER}ParserMap.cpp)

	SOURCE_GROUP		(Common\\RTDB FILES
					${RTDB}Database.hpp
					${RTDB}Database.cpp
					${RTDB}DatabaseParser.hpp
					${RTDB}DatabaseParser.cpp
					${RTDB}Table.hpp
					${RTDB}Table.cpp)

	SOURCE_GROUP		(Common\\Tools FILES
					${TOOLS}Timer.hpp
					${TOOLS}Timer.cpp
					${TOOLS}TimerException.hpp
					${TOOLS}Exception.hpp
					${TOOLS}Singleton.hpp
					${TOOLS}Functor.hpp
					${TOOLS}Singleton.hpp)

	SOURCE_GROUP		(Sources FILES
					 main.cpp
					 mainwindow.cpp
					 mapitem.cpp
					 rtypeitem.cpp
					)

ENDIF					()
