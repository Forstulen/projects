#ifndef			__AGAMEOBJECT__
#define			__AGAMEOBJECT__

#include		<string>
#include		<vector>
#include		"Packet.hpp"

#ifdef			_WIN32
#define			EXPORT		extern "C" __declspec(dllexport)
#else
#define			EXPORT		extern "C"
#endif

namespace									Asset
{

	
  struct				Vector2f
  {
    float			x;
    float			y;
  };  

  enum								eGameObjectType
    {
      PLAYER,
      FRIEND,
      MONSTER,
      EXPLOSION,
      BULLET,
      WALL,
      POWER_UP
    };

  enum									eGroupObject
    {
      NOCOLLISION,
      FRIENDS,
      OTHER
    };

  enum									ePowerUpType
    {
      SPEED,
      BEAM2,
	  BEAM3,
	  BEAM4,
	  BEAM5,
	  BEAM6,
      MODULE,
      NO_POWER
    };

  class									AGameObject
  {
  protected:
    std::string			name_;
    int					id_;
    int					parentId_;
    eGameObjectType		type_;
    eGroupObject			group_;
    ePowerUpType			powerType_;
    Vector2f			dim_;
    Vector2f				pos_;
    Vector2f				dirVec_;
    float					speed_;
    unsigned int			currentRect_;
    unsigned int			startIndex_;
    bool					direction_;
    bool					death_;
    std::string			filename_;
    const AGameObject*	parent_;
    float					fireInterval_;
    float					gtimer_;
    Protocol::eEvent		currentEvent_;
    unsigned int          score_;
    int						healthPoint_;

  public:
    virtual ~AGameObject(void);
  public:
    virtual void				initObject(float posX, float posY, float width, float height, unsigned int rect, bool dir, const AGameObject* parent) = 0;
    virtual void				destroyObject() = 0;
    virtual bool				update(float) = 0;
    virtual bool				update(const Network::Packet &) = 0;
    virtual bool				update(float, Protocol::eEvent) = 0;
    virtual bool				isFiring(float) = 0;

    int							getId() const;
    float						getDirVectorX() const;
    float						getDirVectorY() const;
    int							getParentId() const;
    float						getPosX() const;
    float						getPosY() const;
    float						getSpeed() const;
    bool						getDirection() const;
    unsigned int					getCurrentRect() const;
    unsigned int &					getCurrentRectToSet();
    bool &						getDirectionToSet();
    const std::string &					getResourceName() const;
    float						getWidth() const;
    float						getHeight() const;
    eGameObjectType					getGameObjectType() const;
    eGroupObject					getGroup() const;
		ePowerUpType						getPowerType() const;
    std::string const&					getFilename() const;
    bool						getDeath() const;
    unsigned int					getScore() const;
    int							getHealthPoint() const;
    bool						updateStatus(float, float);
    bool						updateHealPoint(int);

    void						setId(const int);
    void						setDirVector(float, float);
    void						setGroup(const eGroupObject);
    void						setParentId(const int);
    void						setPosX(float);
    void						setPosY(float);
    void						setResourceName(const std::string &);
    void						setGameObjectType(const eGameObjectType);
		void						setPowerType(ePowerUpType);
    void						setDeath(bool);
    void						setHealthPoint(int);
    void						setCurrentEvent(Protocol::eEvent);
    void						addScore(int add);
  };
}

#endif		//	__AGAMEOBJECT__
