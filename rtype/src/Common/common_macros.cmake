#		Set variable for the path of sub folder

set				(COMMON		../Common/)
set				(NETWORK	${COMMON}Network/)
set				(CONVERSIONS	${COMMON}Conversions/)
set				(TOOLS		${COMMON}Tools/)
set				(PARSER		${COMMON}Parser/)
set				(RTDB		${COMMON}RTDB/)
set				(THREAD		${COMMON}Thread/)
set				(LOADER		${COMMON}Loader/)
set				(ASSETS		${COMMON}Assets/)
set				(GAMEOBJECT	${COMMON}GameObject/)

#		Adapts the designing on which the program will be compile

IF				(WIN32)

	set			(COMMON_ARCH	/Windows/)

ELSEIF				(UNIX)

	set			(COMMON_ARCH	/Linux/)

ENDIF				()

#		If we are on UNIX side, we set this variable to link pthread Library

IF				(UNIX)

	set			(COMMON_LIB	pthread)

ENDIF				()

#		Include directories: Listing of include folder in common

set				(COMMON_INC	${NETWORK}
						${THREAD}
						${NETWORK}${COMMON_ARCH}
						${THREAD}${COMMON_ARCH}
						${PARSER}
						${RTDB}
						${GAMEOBJECT}
						${CONVERSIONS}
						${ASSETS}
						${ASSETS}${PROJECT_TYPE}
						${TOOLS}
						${TOOLS}${COMMON_ARCH}
						${LOADER})

#		Common sources: Listing of sources in common between the server and the client

set				(NETWORK_SRCS	${NETWORK}${COMMON_ARCH}UDPSocket.cpp
						${NETWORK}${COMMON_ARCH}SocketLibrary.cpp
						${NETWORK}${COMMON_ARCH}TCPServer.cpp
						${NETWORK}${COMMON_ARCH}TCPClient.cpp
						${NETWORK}${COMMON_ARCH}TCPSocket.cpp
						${NETWORK}ObserverSocket.cpp
						${NETWORK}ErrnoExcept.cpp
						${NETWORK}FileSender.cpp
						${NETWORK}CodeExcept.cpp
						${NETWORK}Packet.cpp)

set				(TOOLS_SRCS	${TOOLS}Timer.cpp
						${TOOLS}${COMMON_ARCH}Sleep.cpp
						${TOOLS}Exception.cpp)

set				(CONVERSIONS_SRCS
						${CONVERSIONS}Conversions.cpp)

set				(RTDB_SRCS	${RTDB}Database.cpp
						${RTDB}DatabaseParser.cpp
						${RTDB}Table.cpp)

set				(THREAD_SCRS	${THREAD}${COMMON_ARCH}Mutex.cpp)
						#${COMMON}Thread/SafeSTDStream.cpp
						#${COMMON}Thread/testStream.cpp

set				(PARSER_SRCS	${PARSER}ConsumerParser.cpp
						${PARSER}ParserXPM.cpp
						${PARSER}ParserMap.cpp)

set				(ASSETS_SRCS	${ASSETS}AGameObject.cpp
						${ASSETS}${PROJECT_TYPE}/AssetManager.cpp
						${ASSETS}MapManager.cpp)

set				(LOADER_SRCS	${LOADER}${COMMON_ARCH}DynamicLibraryLoader.cpp
						${LOADER}${COMMON_ARCH}LoaderManager.cpp)

#		Common headers: Listing of headers in common between the server and the client

set				(NETWORK_HDRS	${NETWORK}${COMMON_ARCH}TCPSocket.hpp
						${NETWORK}${COMMON_ARCH}UDPSocket.hpp
						${NETWORK}${COMMON_ARCH}SocketLibrary.hpp
						${NETWORK}${COMMON_ARCH}TCPServer.hpp
						${NETWORK}${COMMON_ARCH}TCPClient.hpp
						${NETWORK}Packet.hpp
						${NETWORK}Protocol.hpp
						${NETWORK}ITCPServer.hpp
						${NETWORK}ObserverSocket.hpp
						${NETWORK}IObserver.hpp
						${NETWORK}IListener.hpp
						${NETWORK}ISocket.hpp
						${NETWORK}Except.hpp
						${NETWORK}CodeExcept.hpp
						${NETWORK}ErrnoExcept.hpp
						${NETWORK}FileReceiver.hpp)
						#${NETWORK}/FileSender.hpp)

set				(RTDB_HDRS	${RTDB}Database.hpp
						${RTDB}DatabaseParser.hpp
						${RTDB}Table.hpp)

set				(THREAD_HDRS	${THREAD}${COMMON_ARCH}IMutex.hpp
						${THREAD}ISafeQueue.hpp
						${THREAD}${COMMON_ARCH}IThread.hpp
						${THREAD}${COMMON_ARCH}Mutex.hpp
						${THREAD}${COMMON_ARCH}Thread.hpp
						${THREAD}SafeQueue.hpp
						${THREAD}SafeSTDStream.hpp
						${THREAD}ScopedLock.hpp)

set				(PARSER_HDRS	${PARSER}ConsumerParser.hpp
						${PARSER}ParserXPM.hpp
						${PARSER}ParserMap.hpp)

set				(CONVERSIONS_HDRS
						${CONVERSIONS}Conversions.hpp)

set				(ASSETS_HDRS	${ASSETS}AssetInformation.hpp
						${ASSETS}AGameObject.hpp
						${ASSETS}${PROJECT_TYPE}/AssetManager.hpp
						${ASSETS}MapManager.hpp)

set				(LOADER_HDRS	${LOADER}${COMMON_ARCH}DynamicLibraryLoader.hpp
						${LOADER}LoaderManager.hpp)

set				(TOOLS_HDRS	${TOOLS}Timer.hpp
						${TOOLS}TimerException.hpp
						${TOOLS}Exception.hpp
						${TOOLS}Singleton.hpp
						${TOOLS}Functor.hpp
						${TOOLS}${COMMON_ARCH}Sleep.hpp)

#		Particular case if the project if Client, we add this files

IF				(PROJECT_TYPE	MATCHES Client)

	set			(ASSETS_SRCS	${ASSETS_SRCS}
						${ASSETS}AssetImageInformation.cpp
						${ASSETS}AssetSoundInformation.cpp
						${ASSETS}AGameObject.cpp)

	set			(ASSETS_HDRS	${ASSETS_HDRS}
						${ASSETS}AssetImageInformation.hpp
						${ASSETS}AssetSoundInformation.hpp
						${ASSETS}AGameObject.hpp)

ENDIF				()

#		Listing of all files used in Server and Client.

set				(COMMON_SRCS	${NETWORK_SRCS}
						${TOOLS_SRCS}
						${CONVERSIONS_SRCS}
						${RTDB_SRCS}
						${THREAD_SCRS}
						${PARSER_SRCS}
						${ASSETS_SRCS}
						${LOADER_SRCS})

set				(COMMON_HDRS	${NETWORK_HDRS}
						${RTDB_HDRS}
						${THREAD_HDRS}
						${PARSER_HDRS}
						${CONVERSIONS_HDRS}
						${ASSETS_HDRS}
						${LOADER_HDRS}
						${TOOLS_HDRS})

#		Include Directories set

set				(INCLUDE_DIR	${COMMON}
						${TOOLS}
						${THREADS}
						${ASSETS}
						${NETWORK}
						${PARSER}
						${RTDB}
						${CONVERSIONS})

IF				(PROJECT_TYPE	MATCHES Client)

	set			(INCLUDE_DIR	${INCLUDE_DIR}
						${ASSETS}Client
						${APP})

ELSEIF				(PROJECT_TYPE MATCHES Server)

	set			(INCLUDE_DIR	${INC_DIR}
						${ASSETS}Server)

ENDIF				()

include_directories		(${INCLUDE_DIR})
