#ifndef		SAFESTDSTREAM_HPP
# define	SAFESTDSTREAM_HPP


#include	<iostream>
#include	<map>

#include	"ScopedLock.hpp"

/**
 * \file	SafeSTDStream.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Interface for CondVar
 * \namespace	Stream
 */

namespace	Stream
{

  /**
   * \enum	eSafeType
   * \brief	enumeration of global std::stream
   */

  enum		eSafeType
    {
      COUT,
      CERR,
      CLOG,
      CIN
    };

  extern std::map<Stream::eSafeType, std::ostream *>	StreamMap;
  void							load();

  template		<typename Mutex>
  class			SafeSTDStream
  {

    Mutex		_mutex;
    Stream::eSafeType	_type;

  public:

    SafeSTDStream(Stream::eSafeType const&e = Stream::COUT): _type(e)
    {
      Stream::load();
    }

    SafeSTDStream(SafeSTDStream const &s): _type(s._type){}

    template<typename T> std::ostream&		operator << (T const &t)
    {
      Thread::ScopedLock<Mutex>			scope(this->_mutex);

      return *Stream::StreamMap[this->_type] << t << std::endl;
    }

    template<typename T> std::istream&		operator >> (T const &t)
    {
      return std::cin >> t;
    }
  };

};
#endif
