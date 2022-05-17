#include"Board.hpp"
#include"Options.hpp"

Board::Board()
{
       Glib::RefPtr<Gdk::Pixbuf>  whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/White.jpeg");
       Glib::RefPtr<Gdk::Pixbuf>  blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Black.jpeg");
       Glib::RefPtr<Gdk::Pixbuf>  blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_green.jpeg");

    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  if( (i==3 && j==3) || (i==4 && j==4) )
	    {
	      tileSpaces[i][j] = new Gtk::Image( whiteImage);
	      tiles[i][j] = 1;
	    }
	  else if( (i==4 && j==3) || (i==3 && j==4) )
	    {
	    tileSpaces[i][j] = new Gtk::Image( blackImage );
	    tiles[i][j] = -1;
	    }
	  else
	    {
	    tileSpaces[i][j] = new Gtk::Image( blankImage );
	    tiles[i][j] = 0;
	    }
	}
    }
    board_type=1;
}
Board::Board(int i)
{
         Glib::RefPtr<Gdk::Pixbuf>  whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Blanc.jpeg");
         Glib::RefPtr<Gdk::Pixbuf>  blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Noir.jpeg");
         Glib::RefPtr<Gdk::Pixbuf>  blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_beige.jpeg");

    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  if( (i==3 && j==3) || (i==4 && j==4) )
	    {
	      tileSpaces[i][j] = new Gtk::Image( whiteImage);
	      tiles[i][j] = 1;
	    }
	  else if( (i==4 && j==3) || (i==3 && j==4) )
	    {
	    tileSpaces[i][j] = new Gtk::Image( blackImage );
	    tiles[i][j] = -1;
	    }
	  else
	    {
	    tileSpaces[i][j] = new Gtk::Image( blankImage );
	    tiles[i][j] = 0;
	    }
	}
    }
    board_type=2;
}
Board::~Board()
{
    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  delete tileSpaces[i][j];
	}
    }
}
void Board::setTiles(int board[][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            this->SetTileStatus(i,j,board[i][j]);
        }
    }
}

int Board::Score(int piece)
{
	int total = 0;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			if (this->tiles[x][y]== piece)
				total++;
		}
	return total;
}
void Board::setBoard_type(int type_b)
{
    board_type=type_b;
}
int Board::getBoard_type()
{
    return board_type;
}

Gtk::Image* Board::GetTilePicture(int x, int y)
{
  return tileSpaces[x][y];
}

int Board::GetTileStatus(int x, int y)
{
  return tiles[x][y];
}

void Board::SetTileStatus(int x, int y,int val)
{
  tiles[x][y]=val;
}

void Board::SetTilePicture(Gtk::Image* pic, int x, int y)
{
  delete tileSpaces[x][y];
  tileSpaces[x][y] = pic;
}

bool Board::checkFlip( int x, int y, int deltaX, int deltaY,int myPiece, int opponentPiece)
{
	if (this->tiles[x][y] == opponentPiece)
	{
		while ((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
		{
			if ((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
			{
				if ( this->tiles[x][y]  == 0)
					return false;
				if ( this->tiles[x][y]  == myPiece)
					return true;
				else
				{
					// It is an opponent piece, just keep scanning in our direction
				}
			}

			x += deltaX;
			y += deltaY;
		}
	}
	return false; // Either no consecutive opponent pieces or hit the edge of the board
}
bool Board::CheckIfAnyValidMoves(int player)
{
  for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  if( this->tiles[i][j] == 0 )
	    {
	      if( validMove(i,j, player) == true )
	      {
		     return true;
	      }
	    }
	}
    }
  return false;
}

bool Board::validMove(int x, int y, int piece)
{
    if (this->tiles[x][y] != 0)
		return false;

	// Figure out the character of the opponent's piece
	int opponent = 1;
	if (piece == 1)
		opponent = -1;

	// If we can flip in any direction, it is valid
	// Check to the left
	if (checkFlip( x - 1, y, -1, 0, piece, opponent))
		return true;
	// Check to the right
	if (checkFlip(  x + 1, y, 1, 0, piece, opponent))
		return true;
	// Check down
	if (checkFlip( x, y - 1, 0, -1, piece, opponent))
		return true;
	// Check up
	if (checkFlip( x, y + 1, 0, 1, piece, opponent))
		return true;
	// Check down-left
	if (checkFlip( x - 1, y - 1, -1, -1, piece, opponent))
		return true;
	// Check down-right
	if (checkFlip( x + 1, y - 1, 1, -1, piece, opponent))
		return true;
	// Check up-left
	if (checkFlip( x - 1, y + 1, -1, 1, piece, opponent))
		return true;
	// Check up-right
	if (checkFlip( x + 1, y + 1, 1, 1, piece, opponent))
		return true;

	return false;
}

void Board::flipPieces(int x, int y, int deltaX, int deltaY, int myPiece, int opponentPiece)
{
	while (this->tiles[x][y]  == opponentPiece)
	{
	    this->tiles[x][y]=myPiece;
		x += deltaX;
		y += deltaY;
	}
}

bool Board::gameOver()
{
    if(CheckIfAnyValidMoves(1)==false && CheckIfAnyValidMoves(-1)==false)
    {
        return true;
    }
    return false;
}
