cmake_minimum_required		(VERSION	2.6)

#		Project Name

project				(Client)

#		Set variable for the path of sub folder

set				(SFML		../../resource/SFML-1.6/lib/)
set				(MENU		Menu/)
set				(ANIMATION	Animation/)
set				(SOUND		Sound/)
set				(APP		App/)

#		Common: Including files in common.
#			(See common_macors.cmake to add files from the Common folder)

include				(../Common/common_macros.cmake)

#		Server's Sources

set				(SRCS		main.cpp
						IDrawableObject.hpp
						${APP}CoreRTYPE.cpp
						${APP}StateManager.cpp
						${APP}GameClient.cpp
						${APP}GameHandle.cpp
						${APP}StarFieldManager.cpp
						${APP}HUDManager.cpp
						${APP}EventManager.cpp
						${APP}Transition.cpp
						${APP}LoadingState.cpp
						${APP}ConfigFile.cpp
						${APP}AState.cpp
						${MENU}AMenu.cpp
						${MENU}ConnectionMenu.cpp
						${MENU}RoomListMenu.cpp
						${MENU}GameOverState.cpp
						${MENU}RoomMenu.cpp
						${MENU}Cursor.cpp
						${MENU}Label.cpp
						${SOUND}SoundManager.cpp
						${ANIMATION}AnimationManager.cpp)

#		Server's Headers

set				(HDRS		${APP}ICore.hpp
						${APP}CoreRTYPE.hpp
						${APP}AState.hpp
						${APP}StateManager.hpp
						${APP}GameClient.hpp
						${APP}GameHandle.hpp
						${APP}StarFieldManager.hpp
						${APP}HUDManager.hpp
						${APP}EventManager.hpp
						${APP}Transition.hpp
						${APP}LoadingState.hpp
						${APP}ConfigFile.hpp
						${MENU}IWidget.hpp
						${MENU}AMenu.hpp
						${MENU}Button.hpp
						${MENU}ConnectionMenu.hpp
						${MENU}RoomListMenu.hpp
						${MENU}GameOverState.hpp
						${MENU}RoomMenu.hpp
						${MENU}Cursor.hpp
						${MENU}Label.hpp
						${SOUND}SoundManager.hpp
						${ANIMATION}AnimationManager.hpp)

#		Set here the include directories for the Server

include_directories		(App		${MENU}
						${COMMON_INC}
						.)

IF				(WIN32)

	#	inform cmake for the include folders SFML 
	include_directories	(../../resource/SFML-1.6/include)

ENDIF				()

#		Creation of the executable (If you want to add sources or header,
#		use the above)

set				(EXECUTABLE_OUTPUT_PATH
						../Client/)

add_executable			(client		${SRCS}
						${HDRS}
						${COMMON_HDRS}
						${COMMON_SRCS})

#		Link libraries with the client

IF				(WIN32)

	target_link_libraries	(client		Ws2_32)
	target_link_libraries	(client		optimized	${SFML}sfml-system-s
						optimized	${SFML}sfml-window-s
						optimized	${SFML}sfml-graphics-s
						optimized	${SFML}sfml-audio-s
						debug		${SFML}sfml-system-s-d
						debug		${SFML}sfml-window-s-d
						debug		${SFML}sfml-graphics-s-d
						debug		${SFML}sfml-audio-s-d
						${COMMON_LIB})

ELSEIF				(UNIX)

	find_package		(SFML REQUIRED)
	target_link_libraries	(client		sfml-system
						sfml-window
						sfml-graphics
						sfml-audio
						dl
						${COMMON_LIB})

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
					${NETWORK}${COMMON_ARCH}TCPClient.hpp
					${NETWORK}${COMMON_ARCH}TCPClient.cpp
					${NETWORK}${COMMON_ARCH}TCPServer.hpp
					${NETWORK}${COMMON_ARCH}TCPServer.cpp
					${NETWORK}${COMMON_ARCH}UDPSocket.hpp
					${NETWORK}${COMMON_ARCH}UDPSocket.cpp
					${NETWORK}ObserverSocket.hpp
					${NETWORK}ObserverSocket.cpp
					${NETWORK}IObserver.hpp
					${NETWORK}IListener.hpp
					${NETWORK}ISocket.hpp
					${NETWORK}ITCPServer.hpp
					${NETWORK}IUDPSocket.hpp)

	SOURCE_GROUP		(Common\\Conversions FILES
					${CONVERSIONS}Conversions.hpp
					${CONVERSIONS}Conversions.cpp)

	SOURCE_GROUP		(Common\\Tools FILES
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
					${ASSETS}Client/AssetManager.cpp
					${ASSETS}Client/AssetManager.hpp
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
					${PARSER}ParserXPM.cpp
					${PARSER}ParserMap.hpp
					${PARSER}ParserMap.cpp)

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

	SOURCE_GROUP		(Common\\RTDB FILES
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

	SOURCE_GROUP		(Sources\\Menu FILES
 					${MENU}IWidget.hpp
					${MENU}AMenu.hpp
					${MENU}Button.hpp
					${MENU}ConnectionMenu.hpp
					${MENU}Cursor.hpp
					${MENU}Label.hpp
					${MENU}AMenu.cpp
					${MENU}ConnectionMenu.cpp
					${MENU}Cursor.cpp
					${MENU}Label.cpp
					${MENU}RoomListMenu.hpp
					${MENU}RoomListMenu.cpp
					${MENU}GameOverState.cpp
					${MENU}GameOverState.hpp
					${MENU}RoomMenu.hpp
					${MENU}RoomMenu.cpp)

	SOURCE_GROUP		(Sources\\Animation FILES
 					${ANIMATION}AnimationManager.hpp
					${ANIMATION}AnimationManager.cpp)

	SOURCE_GROUP		(Sources\\Sound FILES
 					${SOUND}SoundManager.hpp
					${SOUND}SoundManager.cpp)

	SOURCE_GROUP		(Sources\\App FILES
					${APP}CoreRTYPE.cpp
					${APP}StateManager.cpp
					${APP}ICore.hpp
					${APP}CoreRTYPE.hpp
					${APP}AState.hpp
					${APP}AState.cpp
					${APP}StateManager.hpp
					${APP}StarFieldManager.hpp
					${APP}StarFieldManager.cpp
					${APP}HUDManager.cpp
					${APP}HUDManager.hpp
					${APP}GameClient.hpp
					${APP}GameClient.cpp
					${APP}GameHandle.cpp
					${APP}GameHandle.hpp
					${APP}MapManager.hpp
					${APP}MapManager.cpp
					${APP}EventManager.hpp
					${APP}EventManager.cpp
					${APP}Transition.hpp
					${APP}Transition.cpp
					${APP}LoadingState.hpp
					${APP}LoadingState.cpp
					${APP}ConfigFile.hpp
					${APP}ConfigFile.cpp)

	SOURCE_GROUP		(Sources FILES
					IDrawableObject.hpp
					main.cpp)

ENDIF					()
