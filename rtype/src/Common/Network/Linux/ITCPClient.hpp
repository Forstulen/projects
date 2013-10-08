#ifndef		ITCPCLIENT_HPP
#define		ITCPCLIENT_HPP

namespace	Network
{
  class			ITCPClient
  {

  public:

    virtual		~ITCPClient(){}

    virtual bool	connectToServer() = 0;
  };

};

#endif
