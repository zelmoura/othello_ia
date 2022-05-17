
#ifndef BOARD_HPP
#define BOARD_HPP

#include "headers.hpp"

class Board
{
 public:
  Board();
  Board(int);
  ~Board();
  Gtk::Image* GetTilePicture(int, int);
  void SetTilePicture(Gtk::Image*, int, int);
  void setBoard_type(int);
  int getBoard_type();
  int Score(int);
  bool checkFlip( int, int, int, int,int, int);
  bool CheckIfAnyValidMoves(int);
  bool validMove(int, int, int);
  void flipPieces(int, int, int, int, int, int );
  bool gameOver();

  int  GetTileStatus(int, int);
  void SetTileStatus(int, int, int);
  void setTiles(int board[][8]);

 private:
  Gtk::Image *tileSpaces[8][8];
  int tiles[8][8];
  int board_type=1;

};

#endif // BOARD_HPP

