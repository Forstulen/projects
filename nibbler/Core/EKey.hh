//
// EKey.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Mar 10 14:29:53 2011 chanh allaux
// Last update Sat Mar 12 15:47:51 2011 chanh allaux
//

#ifndef			__KEY_HH_
# define		__KEY_HH_

namespace		KeyGame
{
  typedef enum		KeyCode
    {
      NONE,		// snake: continue
      LEFT,		// snake: left
      RIGHT,		// snake: right
      UP,		// snake: up
      DOWN,		// snake: down
      ESCAPE,		// snake: close
      SPACE,		// snake: boost
      PAUSE,		// snake: pause "p"
      OTHER1,
      OTHER2,
      OTHER3,
      OTHER4,
      OTHER5
    }			eKeyCode;

  typedef enum		Type
    {
      ELEM0,		// snake: empty
      ELEM1,		// snake: wall
      ELEM2,		// snake: food
      ELEM3,		// snake: bonus
      ELEM4,		// snake: malus
      ELEM5,		// snake: body up
      ELEM6,		// snake: body down
      ELEM7,		// snake: body right
      ELEM8,		// snake: body left
      ELEM9,		// snake: head up
      ELEM10,		// snake: head down
      ELEM11,		// snake: head right
      ELEM12,		// snake: head left
      ELEM13,		// snake: tail up
      ELEM14,		// snake: tail down
      ELEM15,		// snake: tail right
      ELEM16,		// snake: tail left
      ELEM17,		// snake
      ELEM18,		// snake
      ELEM19,		// snake
      ELEM20		// snake
    }			eType;
}

#endif
