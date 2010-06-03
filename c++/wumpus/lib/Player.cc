#include "Player.hh"

Player *Player::player;

Player::Player()
{
  player = this;
}

Player::~Player()
{

}

void Player::reset()
{
  perceptList.clear();
  actionList.clear();
}

void Player::linkToAgent ( Agent *agentPtr )
{
  agent = agentPtr;
}

const Action Player::think ( const Percept &percept )
{
  preProcess ( percept );
  const Action action = process ( percept );
  postProcess ( action );
  return action;
}

void Player::done()
{
}

void Player::preProcess ( const Percept &percept )
{
  perceptList.append ( percept );
}

void Player::postProcess ( Action action )
{
  actionList.append ( action );
}

ActorState Player::getState() const
{
  return agent->getState();
}

int Player::numGold() const
{
  return agent->numGold();
}

int Player::numArrows() const
{
  return agent->numArrows();
}

int Player::getScore() const
{
  return agent->getScore();
}

