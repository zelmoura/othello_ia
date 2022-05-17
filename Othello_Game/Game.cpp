#include"Game.hpp"
#include"Help.hpp"
#include"Start.hpp"

Game::Game(int board_t)
{
stringstream coordinates;
  player = -1; // sets to black player

  board_type=board_t;
  blackScore=2;
  whiteScore=2;
    set_title("OTHELLO");
    set_default_size(814,550);
    set_resizable(false);
    set_icon_from_file("img/icon_image.jpg");
    set_position(Gtk::WIN_POS_CENTER);


    Return=Gtk::manage(new Gtk::Button("Return"));
    Restart=Gtk::manage(new Gtk::Button("Restart"));
    Start=Gtk::manage(new Gtk::Button("Start"));

    if(board_type==2)
    {
      W_score=new Gtk::Image("img/Score/b_ScoreW.jpeg");
      B_score=new Gtk::Image("img/Score/b_ScoreB.jpeg");
    }
    else
    {
      W_score=new Gtk::Image("img/Score/g_ScoreW.jpeg");
      B_score=new Gtk::Image("img/Score/g_ScoreB.jpeg");
    }

     Return->signal_clicked().connect(sigc::ptr_fun(Gtk::Main::quit));
     Restart->signal_clicked().connect(sigc::mem_fun(*this,&Game::On_Relancer_Clicked));
     Start->signal_clicked().connect(sigc::mem_fun(*this,&Game::Ord_Vs_Ord));

    boxV_all=new Gtk::VBox(false,0);
    boxV_top=new Gtk::VBox(false,0);
    vBox=new Gtk::VBox(false,0);

    boiteBoutonsH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 30);
    boiteBoutonsV=new Gtk::VButtonBox(Gtk::BUTTONBOX_CENTER, 30);

    hBox1=new Gtk::HBox(false,0);
    hBox2=new Gtk::HBox(false,0);

   l_whiteScore=new Gtk::Label("02");
   l_blackScore=new Gtk::Label("02");

    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data
           ("label { color: DarkOliveGreen;\
                     font-size: 30px;\
                     border-width: 5px;\
                     border-radius: 30px;\
                     font-family: sans-serif;\
                     font-weight:bold;\
                     background-color: black;}");

    l_whiteScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    l_blackScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

   table=Gtk::manage(new Gtk::Table(8,8, true));
   if(board_type==2) board=new Board(3);
   else  board=new Board();

   temp1=new Board;
   temp2=new Board;
    /*************************************BOARD CREATION*************************************/

  for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{

	   table->attach( *board->GetTilePicture(i,j), i, i+1, j, j+1 );
	}
    }

    hBox1->pack_start(*W_score);
    hBox1->pack_start(*l_whiteScore);
    hBox2->pack_start(*B_score);
    hBox2->pack_start(*l_blackScore);

    boiteBoutonsV->pack_start(*Restart);
    boiteBoutonsV->pack_start(*Return);
    boiteBoutonsV->pack_start(*Start);

    boxV_top->pack_start(*hBox1);
    boxV_top->pack_start(*hBox2);

    boxV_all->pack_start(*boxV_top);
    boxV_all->pack_start(*boiteBoutonsV);

    boiteBoutonsH->pack_start(*table);
    boiteBoutonsH->pack_start(*boxV_all);

    vBox->pack_start(*boiteBoutonsH);

    add(*vBox);

 show_all_children();
}
void Game::Ord_Vs_Ord()
{

     Start->activate();
  stringstream blackStream, whiteStream;
  //_sleep(200);

    int player=1,opp=-1; int i=0,j=0;
        int x=0,y=0;
        while(player==1)
       {
            player=1;
             x=0;y=0;
            if(board->CheckIfAnyValidMoves(player)==false)  break;
             iterativeDeepening(board,8,1,x,y);
            ChangeTiles(board,x,y,1,false);
            this->show_all_children();
            player=-1;
       }
       while(opp==-1)
       {
             opp=-1;
            if(board->CheckIfAnyValidMoves(opp)==false) break;
            minimax(board,5,-1,x,y);
            ChangeTiles(board,x,y,-1,false);
            this->show_all_children();
             opp=1;
       }
      blackScore=board->Score(-1);
      whiteScore=board->Score(1);

      hBox1->remove(*l_whiteScore);
      hBox2->remove(*l_blackScore);

      delete l_whiteScore;
      delete l_blackScore;

      if( blackScore < 10 )
	blackStream << 0 << blackScore;
      else
	blackStream << blackScore;

      if( whiteScore < 10 )
	whiteStream << 0 << whiteScore;
      else
	whiteStream << whiteScore;

    l_whiteScore = new Gtk::Label(Glib::locale_to_utf8( whiteStream.str()));
    l_blackScore = new Gtk::Label(Glib::locale_to_utf8( blackStream.str()));

	Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data
           ("label { color: DarkOliveGreen;\
                     font-size: 30px;\
                     border-width: 5px;\
                     border-radius: 30px;\
                     font-family: sans-serif;\
                     font-weight:bold;\
                     background-color: black;}");

    l_whiteScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    l_blackScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

      hBox1->pack_start(*l_whiteScore);
      hBox2->pack_start(*l_blackScore);

      if( board->gameOver())
	{
	   Gtk::Dialog *gameOverDialog;
	  Gtk::Label *l_gameOver ;
       l_gameOver=new Gtk::Label();
	  Glib::ustring winner;

	  if(whiteScore > blackScore)
        l_gameOver->set_markup("<b>\tGame Over : White Player Wins! </b>");
	  else if (whiteScore < blackScore)
        l_gameOver->set_markup("<b>\tGame Over : Black Player Wins! </b>");
	 	  else
	   l_gameOver->set_markup("<b>\tGame Over : Black and White Tied! </b>");

      gameOverDialog = new Gtk::Dialog();
      gameOverDialog->set_title("\tGame Over ");
      gameOverDialog->set_default_size(350,150);
      gameOverDialog->set_position(Gtk::WIN_POS_CENTER);
	  gameOverDialog->get_vbox()->pack_start(*l_gameOver, false, false, 0);
	  gameOverDialog->add_button(" OK ",1);
	  gameOverDialog->set_default_response(1);
	  gameOverDialog->show_all_children();

	  show_all_children();

	  gameOverDialog->run();
	  delete gameOverDialog;
	}

  show_all_children();
}

Game::Game(int Type_game,int levelType,int board_t)
{
  stringstream coordinates;
  player = -1; // sets to black player
  gameType = Type_game;
  level_Type=levelType;
  board_type=board_t;
  blackScore=2;
  whiteScore=2;
    set_title("OTHELLO");
    set_default_size(814,550);
    set_resizable(false);
    set_icon_from_file("img/icon_image.jpg");
    set_position(Gtk::WIN_POS_CENTER);

    /**************************************MENU CREATION**************************************/

    Cancel=Gtk::manage(new Gtk::Button("Cancel"));
    Restart=Gtk::manage(new Gtk::Button("Restart"));

    if(board_type==2)
    {
      W_score=new Gtk::Image("img/Score/b_ScoreW.jpeg");
      B_score=new Gtk::Image("img/Score/b_ScoreB.jpeg");
    }
    else
    {
      W_score=new Gtk::Image("img/Score/g_ScoreW.jpeg");
      B_score=new Gtk::Image("img/Score/g_ScoreB.jpeg");
    }

     Cancel->signal_clicked().connect(sigc::mem_fun(*this,&Game::On_Annuler_Clicked));
    Restart->signal_clicked().connect(sigc::mem_fun(*this,&Game::On_Relancer_Clicked));

    boxV_all=new Gtk::VBox(false,0);
    boxV_top=new Gtk::VBox(false,0);
    vBox=new Gtk::VBox(false,0);

    boiteBoutonsH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 30);
    boiteBoutonsV=new Gtk::VButtonBox(Gtk::BUTTONBOX_CENTER, 30);

    hBox1=new Gtk::HBox(false,0);
    hBox2=new Gtk::HBox(false,0);
    hBox3=new Gtk::HBox(false,0);

    menubar = Gtk::manage(new Gtk::MenuBar());
    gItem = Gtk::manage(new Gtk::MenuItem("Game"));
    menubar->append(*gItem);
    game = Gtk::manage(new Gtk::Menu());
    gItem->set_submenu(*game);

    Gtk::MenuItem *cancel= Gtk::manage(new Gtk::MenuItem("Cancel"));
    cancel->signal_activate().connect(sigc::mem_fun(*this,&Game::On_Annuler_Clicked));
    game->append(*cancel);
    Gtk::MenuItem *restart= Gtk::manage(new Gtk::MenuItem("Restart"));
    restart->signal_activate().connect(sigc::mem_fun(*this,&Game::On_Relancer_Clicked));
    game->append(*restart);
    Gtk::MenuItem *stop= Gtk::manage(new Gtk::MenuItem("Stop"));

    Gtk::SeparatorMenuItem *sep2= Gtk::manage(new Gtk::SeparatorMenuItem);
    game->append(*sep2);

    Gtk::MenuItem *Menu_Principal= Gtk::manage(new Gtk::MenuItem("Main Menu"));
    Menu_Principal->signal_activate().connect(sigc::mem_fun(*this,&Game::Menu_Principal));
    game->append(*Menu_Principal);

    Gtk::MenuItem *Quitter= Gtk::manage(new Gtk::MenuItem("Quit"));
    Quitter->signal_activate().connect(sigc::mem_fun(*this,&Game::Menu_Quit));
    game->append(*Quitter);

    hItem=Gtk::manage(new Gtk::MenuItem("About"));
    menubar->append(*hItem);
    help=Gtk::manage(new Gtk::Menu());
    hItem->set_submenu(*help);

    Gtk::MenuItem *about= Gtk::manage(new Gtk::MenuItem("About"));
    about->signal_activate().connect(sigc::mem_fun(*this,&Game::Menu_About));
    help->append(*about);

   l_whiteScore=new Gtk::Label("02");
   l_blackScore=new Gtk::Label("02");

    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data
           ("label { color: DarkOliveGreen;\
                     font-size: 30px;\
                     border-width: 5px;\
                     border-radius: 30px;\
                     font-family: sans-serif;\
                     font-weight:bold;\
                     background-color: black;}");

    l_whiteScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    l_blackScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);


   table=Gtk::manage(new Gtk::Table(8,8, true));
   if(board_type==2) board=new Board(3);
   else  board=new Board();
   temp1=new Board;
   temp2=new Board;
    /*************************************BOARD CREATION*************************************/

   for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  stringstream coordinates;

	   clickCatch[i][j] =Gtk::manage( new Gtk::EventBox );

	  (*clickCatch[i][j]).add( *(*board).GetTilePicture(i,j) );
	   (*clickCatch[i][j]).set_events( Gdk::BUTTON_PRESS_MASK );

	  coordinates << i << j;

       (*clickCatch[i][j]).signal_button_press_event().connect(
             sigc::bind<string>( sigc::mem_fun(*this, &Game::SpaceClicked),coordinates.str() ));


	   table->attach( (*clickCatch[i][j]), i, i+1, j, j+1 );
	}
    }

    hBox1->pack_start(*W_score);
    hBox1->pack_start(*l_whiteScore);
    hBox2->pack_start(*B_score);
    hBox2->pack_start(*l_blackScore);

    boiteBoutonsV->pack_start(*Cancel);
    boiteBoutonsV->pack_start(*Restart);

    boxV_top->pack_start(*hBox1);
    boxV_top->pack_start(*hBox2);
    boxV_top->pack_start(*hBox3);

    boxV_all->pack_start(*boxV_top);
    boxV_all->pack_start(*boiteBoutonsV);

    boiteBoutonsH->pack_start(*table);
    boiteBoutonsH->pack_start(*boxV_all);

    vBox->pack_start(*menubar);
    vBox->pack_start(*boiteBoutonsH);

    add(*vBox);
  show_all_children();
}
Game::~Game()
{
  delete vBox;
  delete board;
  delete temp1;
  delete temp2;
}
 bool Game::SpaceClicked(GdkEventButton *event,string coordinates)
{
  int opp=1;
  stringstream blackStream, whiteStream;

   int x = atoi( coordinates.substr(0,1).c_str() );

   int y =atoi( coordinates.substr(1,1).c_str() );

 if(gameType == 1)
    player == -1;

  if( player == -1 )
    opp = 1;
  else
    opp = -1;

    if(gameType==2)
      {
	        if(board->validMove(x,y,player))
            {
	        ChangeTiles(board,x ,y ,player,true);
	        player=player*(-1);
	        }
	    if(!board->CheckIfAnyValidMoves(player)) player=player*(-1);
      }
   if(gameType==1) {
         if(board->validMove(x ,y ,player))
            {
          ChangeTiles(board,x ,y ,player,true);
                  if(level_Type==1)
                  {
                        RandomFindMove(x,y,1);
                        ChangeTiles(board,x,y,1,true);
                  }
              else if(level_Type==2)
              {
                    iterativeDeepening(board,8,1,x,y); //*****************
                  ChangeTiles(board,x,y,1,true);
              }
              else if(level_Type==3)
              {
                  minimax(board,5,1,x,y);
                    ChangeTiles(board,x,y,1,true);

              }

              while(board->CheckIfAnyValidMoves(-1)==false && board->gameOver()==false)
              {
                    if(level_Type==1)
                  {      cout<<"1"<<endl;
                        // RandomFindMove(x,y,1);
                        // ChangeTiles(board,x,y,1);
                  }
                  else if(level_Type==2)
                  {cout<<"2"<<endl;
                        //minimaxDecision(board,1,x,y);
                        iterativeDeepening(board,8,1,x,y);
                        ChangeTiles(board,x,y,1,true);

                  }
                  else if(level_Type==3)
                  {
                        minimax(board,5,1,x,y);
                        ChangeTiles(board,x,y,1,true);
                  }
              }
      }
    }

      blackScore=board->Score( -1);
      whiteScore=board->Score( 1);

      hBox1->remove(*l_whiteScore);
      hBox2->remove(*l_blackScore);

      delete l_whiteScore;
      delete l_blackScore;

      if( blackScore < 10 )
	blackStream << 0 << blackScore;
      else
	blackStream << blackScore;

      if( whiteScore < 10 )
	whiteStream << 0 << whiteScore;
      else
	whiteStream << whiteScore;

      l_whiteScore = new Gtk::Label(Glib::locale_to_utf8( whiteStream.str()));
      l_blackScore = new Gtk::Label(Glib::locale_to_utf8( blackStream.str()));

      Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
      css_provider->load_from_data
           ("label { color: DarkOliveGreen;\
                     font-size: 30px;\
                     border-width: 5px;\
                     border-radius: 30px;\
                     font-family: sans-serif;\
                     font-weight:bold;\
                     background-color: black;}");

    l_whiteScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    l_blackScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

      hBox1->pack_start(*l_whiteScore);
      hBox2->pack_start(*l_blackScore);


      /***********************CHECK IF GAME IS OVER******************************/
    if( board->gameOver())
	{
	   Gtk::Dialog *gameOverDialog;
	  Gtk::Label *l_gameOver ;
       l_gameOver=new Gtk::Label();
	  Glib::ustring winner;

	  if(whiteScore > blackScore)
        l_gameOver->set_markup("<b>\tGame Over : White Player Wins! </b>");
	  else if (whiteScore < blackScore)
        l_gameOver->set_markup("<b>\tGame Over : Black Player Wins! </b>");
	 	  else
	   l_gameOver->set_markup("<b>\tGame Over : Black and White Tied! </b>");

      gameOverDialog = new Gtk::Dialog();
      gameOverDialog->set_title("\tGame Over ");
      gameOverDialog->set_default_size(350,150);
      gameOverDialog->set_position(Gtk::WIN_POS_CENTER);
	  gameOverDialog->get_vbox()->pack_start(*l_gameOver, false, false, 0);
	  gameOverDialog->add_button(" OK ",1);
	  gameOverDialog->set_default_response(1);
	  gameOverDialog->show_all_children();

	  show_all_children();

	  gameOverDialog->run();
	  delete gameOverDialog;

	}

  show_all_children();

  return true;
}

void Game::RandomFindMove(int &x, int &y,int player )
{
  srand(time(0));

   do
    {   x = rand() % 8;
        y=rand() % 8;
    }while( !board->validMove(x,y,player) );

}

void Game:: getMoveList(Board *board, int moveX[], int moveY[], int &numMoves, int piece)
{
	numMoves = 0;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			if (board->validMove(x, y, piece))
			{
				moveX[numMoves] = x;
				moveY[numMoves] = y;
				numMoves++;
			}
		}
}
void Game::copyBoard(Board *src,int dest[][8] )
{
  for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            dest[i][j]=src->GetTileStatus(i,j);
        }
    }
}

int Game::heuristic(Board *board, int whoseTurn)
{
    int opponent = 1;
	if (whoseTurn == 1)
		opponent = -1;
	int ourScore = board->Score(whoseTurn);
	int opponentScore = board->Score(opponent);
	return (ourScore - opponentScore);

}
void Game::ChangeTiles(Board *board, int x, int y, int piece,bool status)
{
	board->SetTileStatus(x,y, piece);

	// Figure out the character of the opponent's piece
	int opponent = 1;
	if (piece == 1)
		opponent = -1;

	// Check to the left
	if (board->checkFlip( x - 1, y, -1, 0, piece, opponent))
		flipTiles(board, x   , y,  -1, 0, piece, opponent,status);
	// Check to the right
	if (board->checkFlip( x + 1, y, 1, 0, piece, opponent))
		flipTiles(board, x  , y, 1, 0, piece, opponent,status);
	// Check down
	if (board->checkFlip( x, y-1, 0, -1, piece, opponent))
		flipTiles(board, x, y , 0, -1, piece, opponent,status);
	// Check up
	if (board->checkFlip( x, y + 1, 0, 1, piece, opponent))
		flipTiles(board, x, y  , 0, 1, piece, opponent,status);
	// Check down-left
	if (board->checkFlip(x-1, y - 1, -1, -1, piece, opponent))
		flipTiles(board, x , y  , -1, -1, piece, opponent,status);
	// Check down-right
	if (board->checkFlip( x + 1, y - 1, 1, -1, piece, opponent))
		flipTiles(board, x  , y  , 1, -1, piece, opponent,status);
	// Check up-left
	if (board->checkFlip( x - 1, y + 1, -1, 1, piece, opponent))
		flipTiles(board, x  , y  , -1, 1, piece, opponent,status);
	// Check up-right
	if (board->checkFlip(x + 1, y + 1, 1, 1, piece, opponent))
		flipTiles(board, x  , y  , 1, 1, piece, opponent,status);
}

void Game::flipTiles(Board *board, int x, int y, int deltaX, int deltaY, int myPiece, int opponentPiece,bool status)
{
    if(status==true){
     Glib::RefPtr<Gdk::Pixbuf> whiteImage,blackImage,blankImage;
    if(board->getBoard_type()==2)
  {
      whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Blanc.jpeg");
      blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Noir.jpeg");
      blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_beige.jpeg");
  }
  else
  {
       whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/White.jpeg");
       blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Black.jpeg");
       blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_green.jpeg");
  }

  int i=x+deltaX,j=y+deltaY;

   board->SetTileStatus(x ,y ,myPiece);

   if(myPiece==-1)
            board->SetTilePicture(new Gtk::Image( blackImage),x ,y);
       if(myPiece==1)
        board->SetTilePicture(new Gtk::Image( whiteImage),x ,y);

            stringstream coordinates;

	  table->remove(*clickCatch[x][y]);
	  delete clickCatch[x][y];
	  clickCatch[x][y] = new Gtk::EventBox;

	  clickCatch[x][y]->add( *(*board).GetTilePicture(x,y) );
	  clickCatch[x][y]->set_events( Gdk::BUTTON_PRESS_MASK );

	  coordinates << x << y;

	  clickCatch[x][y]->signal_button_press_event().connect( sigc::bind<string>(
			   sigc::mem_fun(*this, &Game::SpaceClicked), coordinates.str() ) );

	  table->attach( (*clickCatch[x][y]), x, x +1, y, y+1 );


    while (board->GetTileStatus(i,j)== opponentPiece)
	{
		board->SetTileStatus(i,j ,myPiece);
          if(myPiece==-1)
            board->SetTilePicture(new Gtk::Image( blackImage),i ,j);
       if(myPiece==1)
        board->SetTilePicture(new Gtk::Image( whiteImage),i ,j);

        if(status == true){
       stringstream coordinates;

	  table->remove(*clickCatch[i][j]);
	  delete clickCatch[i][j];
	  clickCatch[i][j] = new Gtk::EventBox;

	  clickCatch[i][j]->add( *(*board).GetTilePicture(i,j) );
	  clickCatch[i][j]->set_events( Gdk::BUTTON_PRESS_MASK );

	  coordinates << i << j;

	  clickCatch[i][j]->signal_button_press_event().connect( sigc::bind<string>(
			   sigc::mem_fun(*this, &Game::SpaceClicked), coordinates.str() ) );

	  table->attach( (*clickCatch[i][j]), i, i+1, j, j+1 );
        }

		i += deltaX;
		j += deltaY;
	}
    }

	if(status==false)
    {
        Glib::RefPtr<Gdk::Pixbuf> whiteImage,blackImage,blankImage;
    if(board->getBoard_type()==2)
  {
      whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Blanc.jpeg");
      blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Noir.jpeg");
      blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_beige.jpeg");
  }
  else
  {
       whiteImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/White.jpeg");
       blackImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/Black.jpeg");
       blankImage = Gdk::Pixbuf::create_from_file("img/Board_Pion/b_green.jpeg");
  }

  int i=x+deltaX,j=y+deltaY;

   board->SetTileStatus(x ,y ,myPiece);

   if(myPiece==-1)
           {  //board->SetTilePicture(new Gtk::Image( blackImage),x ,y);
               table->remove(*( board)->GetTilePicture(x,y));
               board->SetTilePicture(new Gtk::Image( blackImage),x ,y);
             table->attach(*( board)->GetTilePicture(x,y), x, x+1, y, y+1 );}

       if(myPiece==1)
        {
         table->remove( *board->GetTilePicture(x,y));
         board->SetTilePicture(new Gtk::Image( whiteImage),x ,y);
         table->attach( *board->GetTilePicture(x,y), x, x+1, y, y+1 );
        }
    while (board->GetTileStatus(i,j)== opponentPiece)
	{
		board->SetTileStatus(i,j ,myPiece);
          if(myPiece==-1)
            board->SetTilePicture(new Gtk::Image( blackImage),i ,j);
       if(myPiece==1)
        board->SetTilePicture(new Gtk::Image( whiteImage),i ,j);
        table->remove(*board->GetTilePicture(i,j));
	  table->attach( *board->GetTilePicture(i,j), i, i+1, j, j+1 );
        }

		i += deltaX;
		j += deltaY;
	}
    }
void Game::Menu_Quit()
{
  quitDialog = new Gtk::Dialog();
  Gtk::Label *l_quit=new Gtk::Label("Do You Really Want To Quit?");
  quitDialog->set_title("Quit?");
  quitDialog->set_icon_from_file("img/icon_image.jpg");
  quitDialog->set_position(Gtk::WIN_POS_CENTER);
  quitDialog->set_default_size(400,150);
  quitDialog->get_vbox()->pack_start(*l_quit, false,0);
  quitDialog->add_button("Yes",0);
  quitDialog->add_button("No ",1);

  quitDialog->show_all_children();

   if(quitDialog->run()==0)
    {
       delete quitDialog;
       this->hide();
    }
    else
      delete quitDialog;
}

void Game::Menu_About()
{
  Glib::RefPtr<Gdk::Pixbuf> about = Gdk::Pixbuf::create_from_file("img/header.jpg");

  Gtk::Image *about_pic = new Gtk::Image(about);
  Gtk::Label *l_author=new Gtk::Label("\tCREATED By ASAKOUR Ihsane  &  N'ANYI Loubna\t");
  Gtk::Label *l_bugs=new Gtk::Label("\tFor more informations ,You may contact us : othello_reversi@gmail.com\t");

  aboutDialog = new Gtk::Dialog();
  aboutDialog->set_title("About");
  aboutDialog->set_icon_from_file("img/icon_image.jpg");
  aboutDialog->set_position(Gtk::WIN_POS_CENTER);
  aboutDialog->set_default_size(500,200);
  aboutDialog->get_vbox()->pack_start(*about_pic, false,10);
  aboutDialog->get_vbox()->pack_start(*l_author, false,0);
  aboutDialog->get_vbox()->pack_start(*l_bugs, false,0);
  aboutDialog->add_button("OK",0);

  aboutDialog->show_all_children();
  aboutDialog->run();

  delete aboutDialog;
}

void Game::On_Annuler_Clicked()
{
}

void Game::On_Return_Clicked()
{
    this->destroy_();
    Help_b aide;
    aide.show();
}
void Game::On_Relancer_Clicked()
{
    bool status=true;
    if(gameType!=1 && gameType!=2) status=false;
    if( whiteScore != 2 && blackScore != 2)
    {
        NewBoard(status);
    }
}
void Game::NewBoard(bool status)
{
   //delete board;
if(status){
   if(board_type==2) board=new Board(3);
   else  board=new Board();
  for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
	  stringstream coordinates;

	  table->remove(*clickCatch[i][j]);
	  delete clickCatch[i][j];
	  clickCatch[i][j] = new Gtk::EventBox;

	  clickCatch[i][j]->add( *(*board).GetTilePicture(i,j) );
	  clickCatch[i][j]->set_events( Gdk::BUTTON_PRESS_MASK );

	  coordinates << i << j;

	  clickCatch[i][j]->signal_button_press_event().connect( sigc::bind<string>(
			   sigc::mem_fun(*this, &Game::SpaceClicked), coordinates.str() ) );

	  table->attach( (*clickCatch[i][j]), i, i+1, j, j+1 );
	}
    }
}
else{
        delete board;
     board=new Board(3);
      for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
	{
       table->remove(*( board)->GetTilePicture(i,j));
	   table->attach( *board->GetTilePicture(i,j), i, i+1, j, j+1 );
	}
    }
}
   whiteScore = blackScore = 2;

      hBox1->remove(*l_whiteScore);
      hBox2->remove(*l_blackScore);

      delete l_whiteScore;
      delete l_blackScore;

   l_whiteScore= Gtk::manage(new Gtk::Label("02"));
   l_blackScore= Gtk::manage(new Gtk::Label("02"));

    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data
           ("label { color: DarkOliveGreen;\
                     font-size: 30px;\
                     border-width: 5px;\
                     border-radius: 30px;\
                     font-family: sans-serif;\
                     font-weight:bold;\
                     background-color: black;}");

    l_whiteScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    l_blackScore->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

      hBox1->pack_start(*l_whiteScore);
      hBox2->pack_start(*l_blackScore);

  show_all_children();
}
void Game::Menu_Principal()
{
if( (blackScore==2) && (whiteScore ==2))
    {
        this->unrealize();
        Start_b widget(1);
        Gtk::Main::run(widget);
    }
else
    {
        Gtk::Label l_Back;
        l_Back.set_markup("Are You Sure??\n \t You are about to leave the match and loss all progress!");
        Gtk::Dialog *menuPrincipal=new Gtk::Dialog();

        menuPrincipal->set_icon_from_file("img/icon_image.jpg");
        menuPrincipal->set_default_size(200,150);
        menuPrincipal->get_vbox()->pack_start(l_Back,false,0);
        menuPrincipal->add_button("I'm Okey ",0);
        menuPrincipal->add_button("NO !!",1);
        menuPrincipal->set_border_width(10);
        menuPrincipal->set_position(Gtk::WIN_POS_CENTER);
        menuPrincipal->set_default_response(1);

        menuPrincipal->show_all_children();

           if( menuPrincipal->run()==0 )
        {
            delete menuPrincipal;
            this->destroy_();
           Start_b start_menu(board_type);
            Gtk::Main::run(start_menu);
        }
        else
            delete menuPrincipal;
    }
}
void Game::DoMove(Board *board, int x, int y, int piece)
{
    board->SetTileStatus(x,y,piece);

	// Figure out the character of the opponent's piece
	int opponent = 1;
	if (piece == 1)
		opponent = -1;

	// Check to the left
	if (board->checkFlip(x - 1, y, -1, 0, piece, opponent))
		board->flipPieces( x - 1, y, -1, 0, piece, opponent);
	// Check to the right
	if (board->checkFlip( x + 1, y, 1, 0, piece, opponent))
		board->flipPieces( x + 1, y, 1, 0, piece, opponent);
	// Check down
	if (board->checkFlip( x, y-1, 0, -1, piece, opponent))
		board->flipPieces( x, y-1, 0, -1, piece, opponent);
	// Check up
	if (board->checkFlip( x, y + 1, 0, 1, piece, opponent))
		board->flipPieces( x, y + 1, 0, 1, piece, opponent);
	// Check down-left
	if (board->checkFlip( x-1, y - 1, -1, -1, piece, opponent))
		board->flipPieces( x-1, y - 1, -1, -1, piece, opponent);
	// Check down-right
	if (board->checkFlip( x + 1, y - 1, 1, -1, piece, opponent))
		board->flipPieces( x + 1, y - 1, 1, -1, piece, opponent);
	// Check up-left
	if (board->checkFlip(x - 1, y + 1, -1, 1, piece, opponent))
		board->flipPieces( x - 1, y + 1, -1, 1, piece, opponent);
	// Check up-right
	if (board->checkFlip(x + 1, y + 1, 1, 1, piece, opponent))
		board->flipPieces( x + 1, y + 1, 1, 1, piece, opponent);
}

int Game::minimax(Board *board, int depth, int player,int &x,int &y) {
    int moveX[60], moveY[60];
    int opp=-1;
    if(player==-1) opp=1;
    int numMoves;
    if (depth == 0 || board->gameOver()) {
        return heuristic(board,player);
    }
    getMoveList(board, moveX, moveY, numMoves, player );
	if (numMoves == 0)
	{
		x = -1;
		y = -1;
	}
   else {

        if (player==1) {
            int bestMoveVal = -99999;
		    int bestX = moveX[0], bestY = moveY[0];
            for (int i = 0; i < numMoves; i++)
		{
                int tempBoard[8][8];
                copyBoard(board,tempBoard);
                temp1->setTiles(tempBoard);
                DoMove(temp1, moveX[i], moveY[i], player);
                int v = minimax(temp1, depth - 1,opp,x,y);
                if (v > bestMoveVal) {
                    bestMoveVal = v;
                    bestX = moveX[i];
				    bestY = moveY[i];
                }
                x = bestX;
	         	y = bestY;
            }
            return bestMoveVal;
        }
        else {
            int bestMoveVal = 99999;
		    int bestX = moveX[0], bestY = moveY[0];
            for (int i = 0; i < numMoves; i++)
		{
                int tempBoard[8][8];
                copyBoard(board,tempBoard);
                temp2->setTiles(tempBoard);
                DoMove(temp2, moveX[i], moveY[i], player);
                int v = minimax(temp2, depth - 1,opp,x,y);
                if (v < bestMoveVal) {
                    bestMoveVal = v;
                    bestX = moveX[i];
				    bestY = moveY[i];
                }
                x = bestX;
	         	y = bestY;
            }
            return bestMoveVal;
        }
   }
}
int  Game::alpha_beta(Board *board,int depth,bool maxPlayer,int &x,int &y,int alpha,int beta )
{
    int moveX[60], moveY[60];
    int numMoves;
    int player;
    if(maxPlayer) player=1;
    else player=-1;

    if (depth == 0 || board->gameOver()) {
        return heuristic(board,player);
    }
    getMoveList(board, moveX, moveY, numMoves, player );
	if (numMoves == 0)
	{
		x = -1;
		y = -1;
	}
   else {

        if (maxPlayer) {
            int bestMoveVal = -99999;
		    int bestX = moveX[0], bestY = moveY[0];
            for (int i = 0; i < numMoves; i++)
		   {
                int tempBoard[8][8];
                copyBoard(board,tempBoard);
                temp1->setTiles(tempBoard);
                DoMove(temp1, moveX[i], moveY[i], player);
                int v = alpha_beta(temp1, depth - 1,false,x,y,alpha,beta);
                if (v > bestMoveVal) {
                    bestMoveVal = v;
                    bestX = moveX[i];
				    bestY = moveY[i];
                }

                x = bestX;
	         	y = bestY;
	         	if( v > alpha )  alpha=v;
                 if(beta <= alpha) break;
            }
            return bestMoveVal;
        }
        else {
            int bestMoveVal = 99999;
		    int bestX = moveX[0], bestY = moveY[0];
            for (int i = 0; i < numMoves; i++)
		{
                int tempBoard[8][8];
                copyBoard(board,tempBoard);
                temp2->setTiles(tempBoard);
                DoMove(temp2, moveX[i], moveY[i], player);
                int v = alpha_beta(temp2, depth - 1,true,x,y,alpha,beta);
                if (v < bestMoveVal) {
                    bestMoveVal = v;
                }
                 if( v < beta ) beta=v;
                 if(beta <= alpha) break;;
            }
            return bestMoveVal;
        }
   }
}
 void Game::iterativeDeepening(Board *board,int depth,int maxPlayer,int &x,int &y)
 {
     int alpha=-99999,beta=99999;
     for(int i=0;i<=depth;i++)
     {
          alpha_beta(board,i,maxPlayer,x,y,alpha,beta);
     }
 }
