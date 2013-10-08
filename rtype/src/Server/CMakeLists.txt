cmake_minimum_required		(VERSION	2.6)

#		Project Name

project				(Server)

#		Set variable for the path of sub folder

set				(SFML		../../resource/SFML-1.6/lib/)
set				(ROOM		Room/)

#		Common: Including files in common.
#			(See common_macors.cmake to add files from the Common folder)

include				(../Common/common_macros.cmake)

#		Server's Sources

set				(SRCS		${COMMON_SRCS}
						${ROOM}RoomManager.cpp
						${ROOM}Room.cpp
						AuthManager.cpp
						Player.cpp
						Level.cpp
						Game.cpp
						GameHandler.cpp
						Core.cpp
						main.cpp)


#		Server's Headers

set				(HDRS		${COMMON_HDRS}
						${ROOM}RoomManager.hpp
						${ROOM}Room.hpp
						AuthManager.hpp
						QuadTree.hpp
						Player.hpp
						Level.hpp
						GameHandler.hpp
						Game.hpp
						Core.hpp)

#		Set here the include directories for the Server

include_directories		(Parser		${COMMON_INC}
						${ROOM}
						.)

IF				(WIN32)

	#	inform cmake for the include folders SFML 
	include_directories	(../../resource/SFML-1.6/include)

ENDIF				()

#		Creation of the executable (If you want to add sources or header,
#		use the above)

set				(EXECUTABLE_OUTPUT_PATH
						../Server/)

add_executable			(server		${SRCS}
						${HDRS})

#		Link libraries with the server
IF				(WIN32)

	target_link_libraries	(server		Ws2_32)
	target_link_libraries	(server		optimized	${SFML}sfml-system-s
						debug		${SFML}sfml-system-s-d
						${COMMON_LIB})

ELSEIF				(UNIX)

	target_link_libraries	(server		${COMMON_LIB}
						dl)
	find_package		(SFML REQUIRED)
	target_link_libraries	(server		sfml-system)

ENDIF()

#		For the arborescence of files in Visual Studio (Windows). Please add it here.

IF				(WIN32)

	SOURCE_GROUP		(Common\\Network FILES
						${NETWORK}Packet.hpp
						${NETWORK}Packet.cpp
						${NETWORK}Protocol.hpp
						${NETWORK}CodeExcept.hpp
						${NETWORK}CodeExcept.cpp
						${NETWORK}ErrnoExcept.hpp
						${NETWORK}ErrnoExcept.cpp
						${NETWORK}Except.hpp
						${NETWORK}FileSender.hpp
						${NETWORK}FileSender.cpp
						${NETWORK}FileReceiver.hpp
						${NETWORK}${COMMON_ARCH}SocketLibrary.hpp
						${NETWORK}${COMMON_ARCH}SocketLibrary.cpp
						${NETWORK}${COMMON_ARCH}TCPSocket.hpp
						${NETWORK}${COMMON_ARCH}TCPSocket.cpp
						${NETWORK}${COMMON_ARCH}TCPClient.cpp
						${NETWORK}${COMMON_ARCH}TCPClient.hpp
						${NETWORK}${COMMON_ARCH}TCPServer.hpp
						${NETWORK}${COMMON_ARCH}TCPServer.cpp
						${NETWORK}${COMMON_ARCH}UDPSocket.hpp
						${NETWORK}${COMMON_ARCH}UDPSocket.cpp
						${NETWORK}IListener.hpp
						${NETWORK}ObserverSocket.hpp
						${NETWORK}ObserverSocket.cpp
						${NETWORK}IObserver.hpp
						${NETWORK}ISocket.hpp
						${NETWORK}ITCPServer.hpp
						${NETWORK}IUDPSocket.hpp)

	SOURCE_GROUP		(Common\\Conversions FILES
						${CONVERSIONS}Conversions.hpp
						${CONVERSIONS}Conversions.cpp)

	SOURCE_GROUP		(Common\\Tools	FILES
						${TOOLS}Timer.hpp
						${TOOLS}Timer.cpp
						${TOOLS}TimerException.hpp
						${TOOLS}Exception.hpp
						${TOOLS}Singleton.hpp
						${TOOLS}Functor.hpp
						${TOOLS}Singleton.hpp)

	SOURCE_GROUP		(Common\\Loader FILES
						${LOADER}${COMMON_ARCH}DynamicLibraryLoader.hpp
						${LOADER}${COMMON_ARCH}DynamicLibraryLoader.cpp
						${LOADER}${COMMON_ARCH}LoaderManager.cpp
						${LOADER}LoaderManager.hpp
						${LOADER}DynamicLibraryLoader.hpp
						${LOADER}DynamicLibraryLoader.cpp)

	SOURCE_GROUP		(Common\\Assets FILES
						${ASSETS}AGameObject.cpp
						${ASSETS}AGameObject.hpp
						${ASSETS}Server/AssetManager.cpp
						${ASSETS}Server/AssetManager.hpp
						${ASSETS}AssetManager.cpp
						${ASSETS}AssetInformation.hpp
						${ASSETS}AssetImageInformation.hpp
						${ASSETS}AssetImageInformation.cpp
						${ASSETS}AssetSoundInformation.hpp
						${ASSETS}AssetSoundInformation.cpp)
						
	SOURCE_GROUP		(Common\\Parser FILES
						${PARSER}ConsumerParser.hpp
						${PARSER}ConsumerParser.cpp
						${PARSER}ParserXPM.hpp
						${PARSER}ParserXPM.cpp)

	SOURCE_GROUP		(Common\\GameObject FILES
						${GAMEOBJECT}WallObject1.cpp
						${GAMEOBJECT}WallObject1.hpp
						${GAMEOBJECT}MonsterObject1.cpp
						${GAMEOBJECT}MonsterObject1.hpp
						${GAMEOBJECT}MonsterObject2.hpp
						${GAMEOBJECT}MonsterObject2.cpp
						${GAMEOBJECT}PlayerObject1.hpp
						${GAMEOBJECT}PlayerObject1.cpp
						)
						
	SOURCE_GROUP		(Common\\RTDB	FILES
						${RTDB}Database.hpp
						${RTDB}Database.cpp
						${RTDB}DatabaseParser.hpp
						${RTDB}DatabaseParser.cpp
						${RTDB}Table.hpp
						${RTDB}Table.cpp)

	SOURCE_GROUP		(Common\\Thread FILES
						${THREAD}CondVarLinux.hpp
						${THREAD}CondVarLinux.cpp
						${THREAD}ICondVar.hpp
						${THREAD}${COMMON_ARCH}IMutex.hpp
						${THREAD}ISafeQueue.hpp
						${THREAD}${COMMON_ARCH}IThread.hpp
						${THREAD}${COMMON_ARCH}Mutex.hpp
						${THREAD}${COMMON_ARCH}Mutex.cpp
						${THREAD}${COMMON_ARCH}Thread.hpp
						${THREAD}SafeQueue.hpp
						${THREAD}SafeSTDStream.hpp
						${THREAD}SafeSTDStream.cpp
						${THREAD}ScopedLock.hpp
						${THREAD}ThreadLinux.hpp
						${THREAD}ThreadWindows.hpp)
      
	SOURCE_GROUP		(Common\\Thread FILES
						AuthManager.cpp
						AuthManager.hpp)

	SOURCE_GROUP		(Sources\\Room	FILES
						${ROOM}RoomManager.hpp
						${ROOM}RoomManager.cpp
						${ROOM}Room.hpp
						${ROOM}Room.cpp)

	SOURCE_GROUP		(Sources	FILES
						main.cpp
						Core.cpp
						Core.hpp
						Level.hpp
						Level.cpp
						Player.cpp
						Player.hpp
						Game.cpp
						Game.hpp
						QuadTree.hpp
						QuadTree.cpp)

ENDIF						()
