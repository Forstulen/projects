//
// NamedPipe.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/namedpipe
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 12:21:52 2011 soufien benramdhane
// Last update Sun Apr 17 16:59:20 2011 romain tholimet
//

#include		<iostream>
#include		<sys/types.h>
#include		<sys/stat.h>
#include		<cstdio>
#include		<unistd.h>
#include		<fcntl.h>

#include		"systemError.hh"
#include		"ScopedLock.hpp"
#include		"NamedPipe.hh"
#include		"Serializer.hh"
#include		"Kitchen.hh"

NamedPipe::NamedPipe(std::string const & name)
  : _name(name)
{
  try
    {
      if (mkfifo(name.c_str(), 00755) == -1)
	throw exceptionPlazza::systemError(exceptionPlazza::MKFIFO);
      if ((this->_fd = open(name.c_str(), O_RDWR)) == -1)
	throw exceptionPlazza::systemError(exceptionPlazza::FOPEN);
      this->_mutex = new Mutex();
      this->_mutexRead = new Mutex();
    }
  catch (const exceptionPlazza::systemError & e)
    {
      std::cerr << e.getMessage() << std::endl;
      throw;
    }
}

NamedPipe::~NamedPipe()
{
  if (close(this->_fd) == -1)
    std::cerr << "Warning: Close Failed" << std::endl;;
  if (remove(this->_name.c_str()) == -1)
    std::cerr << "Warning: Failed by removing" << this->_name.c_str() << std::endl;
  delete (this->_mutex);
}

/*******************************************************/

void			NamedPipe::send(int serial)
{
  ScopedLock		lock(this->_mutex);

  if (write(this->_fd, &serial, sizeof(serial)) == -1)
    throw exceptionPlazza::systemError(exceptionPlazza::SEND);
}

void			NamedPipe::send(int serial, const Kitchen::u_infoSerial& info)
{
  ScopedLock		lock(this->_mutex);
  int			ret;

  if (write(this->_fd, &serial, sizeof(serial)) == -1)
    throw exceptionPlazza::systemError(exceptionPlazza::SEND);
  if ((ret = write(this->_fd, info.serial, sizeof(info.serial))) == -1)
    throw exceptionPlazza::systemError(exceptionPlazza::SEND);
}

int			NamedPipe::receive(void)
{
  ScopedLock		lock(this->_mutexRead);
  int			ret;

  if (read(this->_fd, &ret, sizeof(ret)) == -1)
    throw exceptionPlazza::systemError(exceptionPlazza::RECEIVE);
  return (ret);
}

void			NamedPipe::receive(Kitchen::u_infoSerial& data)
{
  ScopedLock		lock(this->_mutexRead);
  int			nb;

  if ((nb = read(this->_fd, data.serial, sizeof(data.serial))) == -1)
    throw exceptionPlazza::systemError(exceptionPlazza::RECEIVE);
}

std::string const &	NamedPipe::getName(void) const
{
  return (this->_name);
}
