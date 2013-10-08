//
// testStream.cpp for  in /home/renaud_j//Desktop/RType/Thread
//
// Made by johannick renaud
// Login   <renaud_j@epitech.net>
//
// Started on  Fri Jul  8 20:01:57 2011 johannick renaud
// Last update Sat Jul 16 10:09:47 2011 johannick renaud
//

#include					"SafeSTDStream.hpp"

typedef Thread::Mutex				Mutex;
typedef Stream::SafeSTDStream<Mutex>		Safe;
typedef Thread::Thread				ThreadL;

int			doAction(Safe *stream)
{
  for (unsigned int i = 0; i < 1000; ++i)
    *stream << "Hello " << i;
  return (0);
}

int			main()
{
  const unsigned int	nb = 100;
  ThreadL		*threads[nb];
  Safe			stream;

  for (unsigned int i = 0; i < nb; ++i)
    threads[i] = new ThreadL(&doAction, &stream);
  for (unsigned int i = 0; i < nb; ++i)
    threads[i]->joinThread();
  for (unsigned int i = 0; i < nb; ++i)
    delete threads[i];
  return (0);
}
