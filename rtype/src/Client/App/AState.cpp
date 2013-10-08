#include "AState.hpp"

namespace App
{
	void	AState::setNextState(AState* state)
	{
		this->nextState_ = state;
	}

	void	AState::setPrevState(AState* state)
	{
		this->prevState_ = state;
	}
}