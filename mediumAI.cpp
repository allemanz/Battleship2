#include "mediumAI.h"
#include <iostream>

mediumAI::mediumAI()
{
  gameBoard = new char *[8];
  for (int i = 0; i < 8; i++)
  {
    gameBoard[i] = new char[8];
  }
  /// Creating the 2D array.
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      gameBoard[i][j] = '#';
    }
  }

  for(int x = 0; x < m_rows; x++)
  {
    for(int y = 0; y < m_cols; y++)
    {
      firedSpot[x][y] = false; //marked as not hit
    }
  }

  for (int i = 0; i < 2; i++) {
    prevHitSpot[i] = -1;
  }

  for (int i = 0; i < 2; i++) {
    originalHitSpot[i] = -1;
  }

  roundsLeftToShoot = 0;
}

mediumAI::~mediumAI() {
  for (int i = 0; i < 8; i++)
  {
    delete gameBoard[i];
  }
  delete gameBoard;   
}

void mediumAI::printBoard()
{
  std::cout << "  A B C D E F G H"; //COLUMN LABELS

  for(int x = 0; x < m_rows; x++)
  {
    std::cout << "\n" << (x + 1) << " ";

    for(int y = 0; y < m_cols; y++)
    {
      std::cout << gameBoard[x][y] << " ";
    }
  }
  std::cout << "\n";
}

void mediumAI::printAttackBoard()
{
  std::cout << "  A B C D E F G H"; //COLUMN LABELS

  for(int x = 0; x < m_rows; x++)
  {
    std::cout << "\n" << (x + 1) << " ";

    for(int y = 0; y < m_cols; y++)
    {
      if(gameBoard[x][y] != ('#' || 'M' || 'X'))
      {
        std::cout << "# ";
      }
      else
      {
        std::cout << gameBoard[x][y] << " ";
      }
    }
  }
  std::cout << "\n";
}

void mediumAI::incomingShot(std::string coords)
{
  int row = convertCoordinate(coords[0]);///Convert Coordinates to array indeces.
  int col = convertCoordinate(coords[1]);
  if(gameBoard[col][row] == '#')///Check if hits empty water, a miss.
  {
    std::cout << "You missed.\n";
    gameBoard[col][row] = 'M';///Mark the miss on the map.
  }
  else if(gameBoard[col][row] == ('M' || 'X'))
  {
    std::string newCoords = "";
    std::cout << "You already fired here. Try another position.\n";
    std::cin >> newCoords;
    while(!validCoordinates(newCoords))
    {
      std::cout << "Please input valid coordinates.\n";
      std::cin >> newCoords;
    }
    incomingShot(newCoords);
  }
  else
  {
    char shipType = gameBoard[col][row];
    gameBoard[col][row] = 'X';
    std::cout << "\n\nHit!\n\n";
    if(isShipSunk(shipType))
    {
      if(shipType == 'T')
      {
        std::cout << "You sunk my Tugboat!\n\n";
      }
      else if(shipType == 'S')
      {
        std::cout << "You sunk my Submarine!\n\n";
      }
      else if(shipType == 'D')
      {
        std::cout << "You sunk my Destroyer!\n\n";
      }
      else if(shipType == 'B')
      {
        std::cout << "You sunk my BattleShip!\n\n";
      }
      else
      {
        std::cout << "You sunk my Carrier!\n\n";
      }
    }
  }
}

std::string mediumAI::fireOnPlayer(Player& player)
{
  char** playerGameBoard = player.getGameBoard();
  int row;
  int col;
  if (prevHitSpot[0] == -1 && prevHitSpot[1] == -1 && roundsLeftToShoot == 0) {
    do {
      row = rand() % 8;
      col = rand() % 8;
    } while (firedSpot[row][col] != false);
    firedSpot[row][col] = true;

    if (playerGameBoard[row][col] == 'T') {
      prevHitSpot[0] = -1;
      prevHitSpot[1] = -1;
      originalHitSpot[0] = -1;
      originalHitSpot[1] = -1;
      roundsLeftToShoot = 0;
    }

    if (playerGameBoard[row][col] == 'S') {
      prevHitSpot[0] = row;
      prevHitSpot[1] = col;
      originalHitSpot[0] = row;
      originalHitSpot[1] = col;
      roundsLeftToShoot = 1;
    }

    if (playerGameBoard[row][col] == 'D') {
      prevHitSpot[0] = row;
      prevHitSpot[1] = col;
      originalHitSpot[0] = row;
      originalHitSpot[1] = col;
      roundsLeftToShoot = 2;
    }

    if (playerGameBoard[row][col] == 'B') {
      prevHitSpot[0] = row;
      prevHitSpot[1] = col;
      originalHitSpot[0] = row;
      originalHitSpot[1] = col;
      roundsLeftToShoot = 3;
    }

    if (playerGameBoard[row][col] == 'C') {
      prevHitSpot[0] = row;
      prevHitSpot[1] = col;
      originalHitSpot[0] = row;
      originalHitSpot[1] = col;
      roundsLeftToShoot = 4;
    }
  } else {
    char previousShipType = playerGameBoard[prevHitSpot[0]][prevHitSpot[1]];
    // determine direction 'up', 'down', 'left', 'right' that could find the next spot up the current ship
    if (prevHitSpot[0] - 1 >= 0 && playerGameBoard[prevHitSpot[0] - 1][prevHitSpot[1]] == previousShipType) {
      roundsLeftToShoot--;
      prevHitSpot[0] = prevHitSpot[0] - 1;
      row = prevHitSpot[0];
      col = prevHitSpot[1];
    } else if (prevHitSpot[0] + 1 < 8 && playerGameBoard[prevHitSpot[0] + 1][prevHitSpot[1]] == previousShipType) {
      roundsLeftToShoot--;
      prevHitSpot[0] = prevHitSpot[0] + 1;
      row = prevHitSpot[0];
      col = prevHitSpot[1];
    } else if (prevHitSpot[1] - 1 >= 0 && playerGameBoard[prevHitSpot[0]][prevHitSpot[1] - 1] == previousShipType) {
      roundsLeftToShoot--;
      prevHitSpot[1] = prevHitSpot[1] - 1;
      row = prevHitSpot[0];
      col = prevHitSpot[1];
    } else if (prevHitSpot[1] + 1 < 8 && playerGameBoard[prevHitSpot[0]][prevHitSpot[1] + 1] == previousShipType) {
      roundsLeftToShoot--;
      prevHitSpot[1] = prevHitSpot[1] + 1;
      row = prevHitSpot[0];
      col = prevHitSpot[1];
    } else { // still has rounds left to shoot, but can't find a spot. Then go back to the original hit spot, and try the opposite direction.
      prevHitSpot[0] = originalHitSpot[0];
      prevHitSpot[1] = originalHitSpot[1];
      return fireOnPlayer(player);
    }
  }

  
  char rowArr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  return rowArr[row] + std::to_string(col+1);
}

void mediumAI::addShips(int numbShips)
{
  //needs implementation
}

bool mediumAI::validCoordinates(std::string& coords)
{
  if(coords.length() != 2)///Checks coordinate set is exactly a column and row with length.
  {
    return false;
  }
  if(coords[0] == 'a' || coords[0] == 'b' || coords[0] == 'c' || coords[0] == 'd' || coords[0] == 'e' || coords[0] == 'f' || coords[0] == 'g' || coords[0] == 'h')///Uppercases first coordinate if necessary.
  {
    coords[0] = toupper(coords[0]);
  }
  if((coords[0] == 'A' || coords[0] == 'B' || coords[0] == 'C' || coords[0] == 'D' || coords[0] == 'E' || coords[0] == 'F' || coords[0] == 'G' || coords[0] == 'H') &&
  (coords[1] == '1' || coords[1] == '2' || coords[1] == '3' || coords[1] == '4' || coords[1] == '5' || coords[1] == '6' || coords[1] == '7' || coords[1] == '8'))///Checks first is A-H, second is 1-8.
  {
    return true;
  }
  else
  {
    return false;
  }
}

int mediumAI::convertCoordinate(char coord)
{
  if(coord == 'A' || coord == 'B' || coord == 'C' || coord == 'D' || coord == 'E' || coord == 'F' || coord == 'G' || coord == 'H')
  {
    return(coord - 65);
  }
  if(coord == '1' || coord == '2' || coord == '3' || coord == '4' || coord == '5' || coord == '6' || coord == '7' || coord == '8')
  {
    return(coord - 49);
  }
  return 0;
}

bool mediumAI::gameOver()
{
  bool over = true;///Iterates through map, simply setting over to false if it sees a ship marker.
  for(int x = 0; x < m_rows; x++)
  {
    for(int y = 0; y < m_cols; y++)
    {
      if(gameBoard[x][y] != '#' || 'M' || 'X')
      {
        over = false;
      }
    }
  }
  return over;
}

bool mediumAI::isShipSunk(char shipType)
{
  bool isSunk = true;///Iterates through map, simply setting isSunk to false if it sees the specified ship marker.
  for(int x = 0; x < m_rows; x++)
  {
    for(int y = 0; y < m_cols; y++)
    {
      if(gameBoard[x][y] == shipType)
      {
        isSunk = false;
      }
    }
  }
  return isSunk;
}
