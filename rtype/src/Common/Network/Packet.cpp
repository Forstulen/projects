#include	<iostream>
#include	"Packet.hpp"

/**
 * \file	Packet.cpp
 * \author	RENAUD. J.
 * \date	July 14, 2011
 * \version	1.0
 * \namespace	Network
 */

Network::Packet::Packet(Content &content)
  : content_(content)
{
}

Network::Packet::~Packet()
{
}

/**************************************GETTER*************************************/

Network::Content const& Network::Packet::getContent() const
{
  return this->content_;
}

unsigned int			Network::Packet::getType() const
{
  return this->content_.head.type;
}

unsigned int			Network::Packet::getSubType() const
{
  return this->content_.head.sType;
}

unsigned int			Network::Packet::getTransactionType() const
{
  return this->content_.head.tType;
}

unsigned int			Network::Packet::getSize() const
{
  return this->content_.head.size + sizeof(Network::Header);
}

/****************************************SETTER***********************************/

void				Network::Packet::setType(Protocol::eType const size)
{
  this->content_.head.type = size;
}

void				Network::Packet::setSubType(Protocol::eSubType const subType)
{
  this->content_.head.sType = subType;
}

void				Network::Packet::setTransactionType(Protocol::eTransactionType const tType)
{
  this->content_.head.tType = tType;
}

void Network::Packet::setHeader(short header)
{
  this->content_.head.size = header >> 8;
  this->content_.head.type = (header >> 6) & 0x03;
  this->content_.head.tType = (header >> 4) & 0x03;
  this->content_.head.sType = header & 0x0f;
}

short Network::Packet::headerToShort() const
{
  short header = 0;
  short tmp;
  header |= this->content_.head.size;
  header <<= 8;
  tmp = 0;
  tmp = this->content_.head.type;
  tmp <<= 6;
  header |= tmp;
  tmp = 0;
  tmp = this->content_.head.tType;
  tmp <<= 4;
  header |= tmp;
  header |= this->content_.head.sType;
  return header;
}
