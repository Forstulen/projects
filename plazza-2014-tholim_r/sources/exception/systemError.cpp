//
// systemError.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/exception
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 21:07:45 2011 soufien benramdhane
// Last update Sun Apr 17 22:35:52 2011 romain tholimet
//

#include	<string>

#include	"systemError.hh"

exceptionPlazza::systemError::systemError(errorCode errCode)
  : _errCode(errCode)
{
  this->msgType[exceptionPlazza::MKFIFO] = "Error: Named Pipe not initialized.";
  this->msgType[exceptionPlazza::FOPEN] = "Error: Fail to access to NamedPipe.";
  this->msgType[exceptionPlazza::SEND] = "Error: Fail to send Pizza! Sorry Sir! :'(";
  this->msgType[exceptionPlazza::RECEIVE] = "Error: Fail to receive your Command! Sorry Sir.";
  this->msgType[exceptionPlazza::POP] = "Error: Pop: Can't pop another value, the queue is empty.";
  this->msgType[exceptionPlazza::BADING] = "Error: Plazza closed because of bad ingredient using.";
  this->msgType[exceptionPlazza::CLOCK] = "Error: clock_gettime: Plazza has his clock broken...";
  this->msgType[exceptionPlazza::FORK] = "Error: fork: Kitchen couldn't open kitchen.";
  this->msgType[exceptionPlazza::CONDINIT] = "Error: CondVar: Cannot init Cond Var.";
  this->msgType[exceptionPlazza::CONDDEST] = "Error: CondVar: Cannot destroy Cond Var.";
  this->msgType[exceptionPlazza::CONDWAIT] = "Error: CondVar: Cannot wait the signal.";
  this->msgType[exceptionPlazza::CONDSIG] = "Error: CondVar: Cannot send the signal.";
  this->msgType[exceptionPlazza::MUTINIT] = "Error: Mutex: Cannot create a mutex.";
  this->msgType[exceptionPlazza::MUTDEST] = "Error: Mutex: Cannot destroy mutex.";
  this->msgType[exceptionPlazza::MUTLOCK] = "Error: Mutex: Cannot lock the mutex.";
  this->msgType[exceptionPlazza::MUTUNLOCK] = "Error: Mutex: Cannot unlock the mutex.";
  this->msgType[exceptionPlazza::CREATTHR] = "Error: Thread: Cannot create a thread.";
  this->msgType[exceptionPlazza::JOINTHR] = "Error: Thread: Cannot join a thread.";
  this->msgType[exceptionPlazza::BADARG] = "Error: Argument: Wrong format of an argument.";
  this->msgType[exceptionPlazza::BADLIB] = "Error: Library : Can't get the library.";
  this->msgType[exceptionPlazza::NOTLOG] = "Error: Log : Can't create log file.";
  this->msgType[exceptionPlazza::KITCHERR] = "Error: Kitchen throw an exception, Reception cannot continue.";
  this->msg = justMsg(errCode);
}

exceptionPlazza::systemError::systemError(std::string const & str)
{
  this->msg = str;
}

/************************************************************/

std::string				exceptionPlazza::systemError::justMsg(errorCode errCode)
{
  return (this->msgType[errCode]);
}

exceptionPlazza::errorCode		exceptionPlazza::systemError::getType()
{
  return (this->_errCode);
}
