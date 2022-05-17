#ifndef _GAMEWIDGET_
#define _GAMEWIDGET_

#include"headers.hpp"
#include"Board.hpp"

class  Game: public Gtk::Window
{
public :
    Game(int Type_game,int levelType,int board_type);
    Game(int);
    ~Game();

    bool SpaceClicked(GdkEventButton* ,string);
    void RandomFindMove(int &,int & ,int);
    void NewBoard(bool);

    void DoMove(Board *board, int x, int y, int piece);
    void copyBoard(Board *src,int dest[][8] );
    void getMoveList(Board *board, int moveX[], int moveY[], int &numMoves, int player  );

    void ChangeTiles(Board *board, int x, int y, int piece,bool status);
    void flipTiles(Board *board, int x, int y, int deltaX, int deltaY, int myPiece, int opponentPiece,bool status);
    void Ord_Vs_Ord( );

    int heuristic(Board *board, int whoseTurn);

    int minimax(Board *board, int depth,int player,int &x,int &y);
    int alpha_beta(Board *board,int depth,bool maxPlayer,int &x,int &y,int alpha,int beta );
    void iterativeDeepening(Board *board,int depth,int maxPlayer,int &x,int &y);

  void On_Annuler_Clicked();
  void On_Relancer_Clicked();
  void On_Return_Clicked();
  void Menu_Quit();
  void Menu_About();
  void Menu_Principal();

private:
  Board *board,*temp1,*temp2;
  Gtk::Table *table;
  Gtk::EventBox *clickCatch[8][8];

  Gtk::Button *Cancel,*Restart,*Return;

  Gtk::VBox *boxV_top,*boxV_all,*vBox;
  Gtk::HBox *hBox1, *hBox2,*hBox3;
  Gtk::VButtonBox *boiteBoutonsV;
  Gtk::HButtonBox *boiteBoutonsH;

  Gtk::MenuBar *menubar;
  Gtk::Menu *game, *setting, *help;
  Gtk::MenuItem *gItem, *hItem;

  Gtk::Label *l_whiteScore, *l_blackScore, *time_label;
  Gtk::Image *W_score,*B_score, *timer_pic;

  Gtk::Dialog *quitDialog;
  Gtk::Dialog *aboutDialog;
  Gtk::Dialog *gameOverDialog;
  Gtk::Button *Start;

  int player;
  int gameType,level_Type,board_type;
  int whiteScore, blackScore;

};

#endif // _GAMEWIDGET_
