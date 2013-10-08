/**
 * \file	SafeSTDStream.cpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \namespace	Stream
 */

#include	"SafeSTDStream.hpp"

std::map<Stream::eSafeType, std::ostream *>		Stream::StreamMap;

void		Stream::load()
{
  Stream::StreamMap[COUT] = &std::cout;
  Stream::StreamMap[CERR] = &std::cerr;
  Stream::StreamMap[CLOG] = &std::clog;
}

