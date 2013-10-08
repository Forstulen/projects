/*
** header.c for Project in /home/berbeg_m/
** 
** Made by mathieu berbegal
** Login   <berbeg_m@epitech.net>
** 
** Started on  Tue Feb  1 10:33:05 2011 mathieu berbegal
** Last update Tue Feb  1 10:33:09 2011 mathieu berbegal
*/
#ifndef		PACKET_HPP
#define		PACKET_HPP

/**
 * \file	Packet.hpp
 * \author	RENAUD. J.
 * \date	July 14, 2011
 * \version	1.0
 * \namespace	Network
 */

#include "Protocol.hpp"

//namespace Protocol
//{
//  enum eSubType;
//  enum eType;
//  enum eTransactionType;
//}

namespace	Network
{

  /**
   * \class		Header
   * \brief		Struct which describes the Header of a Packet
   */

  struct		Header
  {
    unsigned char size;
    unsigned char type;
    unsigned char tType;
    unsigned char sType;
  };

  /**
   * \class		Content
   * \brief		Struct which will be send threw the Network
   */

  struct		Content
  {
    Header		head;
    char		data[254];
  };

  /**
   * \class		Packet
   */

  class			Packet
  {

    Content		content_;

  public:

    Packet()
    {}
    Packet(Content &);

    template		<typename T>
    Packet(T const &data,
	   unsigned char size,
	   Protocol::eType type,
	   Protocol::eTransactionType tType,
	   unsigned char sType)
    {
      this->content_.head.size = size;
      this->content_.head.type = type;
      this->content_.head.tType = tType;
      this->content_.head.sType = sType;

      char const *tmp = reinterpret_cast<char const *>(data);
      for (unsigned int i = 0; i < size; ++i)
        this->content_.data[i] = tmp[i];
    }

    template		<typename T>
    T			getData() const
    {
      return reinterpret_cast<T>(this->content_.data);
    }

    ~Packet();

    Content const&              getContent() const;
    unsigned int		getType() const;
    unsigned int		getSubType() const;
    unsigned int		getTransactionType() const;
    unsigned int		getSize() const;
    short                       headerToShort() const;

    void                        setHeader(short header);
    void			setType(Protocol::eType const);
    void			setSubType(Protocol::eSubType const);
    void			setTransactionType(Protocol::eTransactionType const);
    template			<typename T>
    void			setData(T const & data, unsigned char size)
    {
      char const *tmp = reinterpret_cast<char const *>(data);
      for (unsigned int i = 0; i < size; ++i)
        this->content_.data[i] = tmp[i];
      this->content_.head.size = size;
    }
  };

  const unsigned short		maxData = 256;

};

#endif
