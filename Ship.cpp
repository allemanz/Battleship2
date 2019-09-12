#include "Ship.h"
#include <algorithm>
#include <utility>
#include<vector>


Ship::Ship(int length)
{
  m_shipLength = length;
  std::vector<std::pair<int, int>> m_pairs;
}

int Ship::getLength()
{
  return m_shipLength;
}

void Ship::addCoordinate(int row, int col)
{
  std::pair<int,int> newPair;
  newPair.first = row;
  newPair.second = col;
  m_pairs.push_back(newPair);
  m_shipLength++;
}

bool Ship::checkForHit(int row, int col)
{
  std::pair<int,int> checkPair;
  checkPair.first = row;
  checkPair.second = col;
  if(std::find(m_pairs.begin(), m_pairs.end(), checkPair) != m_pairs.end()) {
    //will enter this if statement if the pair is in the ships
    //we do NOT need to remove the specific element from the vector because this checkForHit function will
    //only be called if the space is 'S' and the space will be changed to '#' in Player.cpp right after this function finishes
    m_shipLength--;
    return true;
  }
  else {
    return false;
  }
}
