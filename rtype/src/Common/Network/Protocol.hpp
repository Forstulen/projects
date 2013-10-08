#ifndef				PROTOCOL_HPP
# define			PROTOCOL_HPP

namespace			Protocol
{
  enum eEvent
  {
    RT_EVENT_UP_LEFT = 0,
    RT_EVENT_UP_RIGHT,
    RT_EVENT_DOWN_LEFT,
    RT_EVENT_DOWN_RIGHT,
    RT_EVENT_UP,
    RT_EVENT_DOWN,
    RT_EVENT_LEFT,
    RT_EVENT_RIGHT,
    RT_EVENT_CHARGE,
    RT_EVENT_SHOOT,
    RT_EVENT_MODULE,
    RT_EVENT_NONE
  };

  struct  ObjectData
  {
    float timestamp;
    unsigned int	id;
	unsigned int	parentId;
    float			posX;
    float			posY;
	float			vecX;
	float			vecY;
    bool			direction;
  };

  struct	ScoringData
  {
    unsigned int	id;
    unsigned int	score;
  };

  struct CreationObjectData
  {
    ObjectData data;
    char       filename[100];
  };

  struct CreationBulletData
  {
    ObjectData		data;
    unsigned char	beam;
    char          filename[100];
  };

  struct ModificationBulletData
  {
    ObjectData    data;
    unsigned char beam;
    unsigned int  localId;
  };

  struct PlayerInfo
  {
    unsigned int id;
    unsigned int port;
    char  login[12];
  };

  struct PlayerStatus
  {
    char login[12];
    bool isReady;
  };

  struct PlayerEvent
  {
    float             timestamp;
    int               id;
    float             x;
    float             y;
    eEvent            event;
  };

  enum			eType
  {
    RT_TYPE_CONNECTION = 0,
    RT_TYPE_ROOM = 1,
    RT_TYPE_GAME = 2
  };

  enum			eTransactionType
  {
    RT_TT_REQUEST = 0,
    RT_TT_REPLY = 1,
    RT_TT_ACK = 2,
    RT_TT_ERROR = 3,
    RT_TT_CREATION = 0,
    RT_TT_MODIFICATION = 1,
    RT_TT_DESTRUCTION = 2
  };

  enum			eSubType
  {
    RT_SUB_AUTH = 0,
    RT_SUB_DISC = 1,
    RT_SUB_ALIVE = 2,
    RT_SUB_JOIN = 0,
    RT_SUB_LEAVE = 1,
    RT_SUB_ROOMS = 2,
    RT_SUB_PLAYERS = 3,
    RT_SUB_READY = 4,
    RT_SUB_INFO = 5,
    RT_SUB_START = 6,
    RT_SUB_FILE = 7,
    RT_SUB_EVENT = 0,
    RT_SUB_OBJECT = 1,
    RT_SUB_BULLET = 2,
    RT_SUB_SCORE = 3,
    RT_SUB_GAMEOVER = 4,
    RT_SUB_LEVELOVER = 5
  };

  const unsigned char		maxPacketSize = 254;
}
#endif				/* ! PROTOCOL_HPP */
