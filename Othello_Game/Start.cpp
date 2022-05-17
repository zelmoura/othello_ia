#include "Start.hpp"


Start_b::Start_b(int board_type)
{
    board=board_type;
    set_title("OTHELLO");
    set_default_size(814,550);
    set_icon_from_file("img/icon_image.jpg");
    set_resizable(false);
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(100);

    game=new Gtk::Button("Play ");
    Options=new Gtk::Button("Options ");
    howToPlay=new Gtk::Button("Help");
    Quit=new Gtk::Button("Quit");
    boiteBoutonsx=new Gtk::VButtonBox(Gtk::BUTTONBOX_CENTER,20);

    game->set_focus_on_click(false);
    Options->set_focus_on_click(false);
    howToPlay->set_focus_on_click(false);
    Quit->set_focus_on_click(false);

    boiteBoutonsx->pack_start(*game);
    boiteBoutonsx->pack_start(*Options);
    boiteBoutonsx->pack_start(*howToPlay);
    boiteBoutonsx->pack_start(*Quit);
    add(*boiteBoutonsx);

    game->signal_clicked().connect( sigc::mem_fun(*this, &Start_b::On_game_Clicked));
    howToPlay->signal_clicked().connect(sigc::mem_fun(*this, &Start_b::On_howToPlay_Clicked));
    Options->signal_clicked().connect(sigc::mem_fun(*this, &Start_b::On_Options_Clicked));
    Quit->signal_clicked().connect(sigc::ptr_fun(&Gtk::Main::quit));


    boiteBoutonsH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER,20);
    done=new Gtk::Button("Done !");
    vBox1=new Gtk::VBox(false, 0);
    vBox2=new Gtk::VBox(false, 0);
    vBox_top=new Gtk::VBox();
    hBox1=new Gtk::HBox();
    hBox2=new Gtk::HBox();
    Separator1=new Gtk::HSeparator();
    Separator2=new Gtk::HSeparator();
    l_level=new Gtk::Label();
    l_game=new Gtk::Label();

    dialog=new Gtk::Dialog();

    Gtk::RadioButtonGroup level_type;
    level_one=new Gtk::RadioButton(level_type,"Easy");
    level_two=new Gtk::RadioButton(level_type,"Moyen");
    level_three=new Gtk::RadioButton(level_type,"Hard");

    Gtk::RadioButtonGroup game_type;
    one_player=new Gtk::RadioButton(game_type,"One Player");
    two_players=new Gtk::RadioButton(game_type,"Two Players");

    l_game->set_markup("  Choose your game type : ");
    l_level->set_markup("Choose your level : ");

     hBox1->pack_start(*one_player);
      hBox1->pack_start(*two_players);
     hBox2->pack_start(*level_one);
     hBox2->pack_start(*level_two);
     hBox2->pack_start(*level_three);
     boiteBoutonsH->pack_start(*done);

     vBox1->set_border_width(20);
     vBox1->pack_start(*l_game);
     vBox1->pack_start(*Separator1);
     vBox1->pack_start(*hBox1);

     vBox2->set_border_width(20);
     vBox2->pack_start(*l_level);
     vBox2->pack_start(*Separator2);
     vBox2->pack_start(*hBox2);

     vBox_top->pack_start(*vBox1);
     vBox_top->pack_start(*vBox2);
     vBox_top->pack_start(*boiteBoutonsH);

    show_all();
}
void Start_b::On_game_Clicked( )
{
    dialog->set_title("Information");
   dialog->set_icon_from_file("img/icon_image.jpg");
   dialog->get_vbox()->pack_start(*vBox_top,false,0);
   dialog->set_border_width(10);
   dialog->set_default_size(500,200);
    dialog->set_position(Gtk::WIN_POS_CENTER);
   dialog->show_all_children();
    one_player->signal_toggled().connect(sigc::mem_fun(*this, &Start_b::Activate_Choices));
    two_players->signal_toggled().connect(sigc::mem_fun(*this, &Start_b::Disable_Choices));
    done->signal_clicked().connect(sigc::mem_fun(*this,&Start_b::On_done_clicked));
    dialog->run();

}
void Start_b::Disable_Choices()
{
    level_one->set_sensitive(false);
    level_two->set_sensitive(false);
    level_three->set_sensitive(false);
}
void Start_b::Activate_Choices()
{
    level_one->set_sensitive(true);
    level_two->set_sensitive(true);
    level_three->set_sensitive(true);
}
void Start_b::On_done_clicked()
{
    if(one_player->get_active())
    {
        game_type=1;
        if(level_one->get_active())
        {
            level=1;
        }
        if(level_two->get_active())
        {
            level=2;
        }
        if(level_three->get_active())
        {
            level=3;
        }
    }
    else if(two_players->get_active())
    {
        game_type=2;
        level=0;
    }
    delete dialog;
    this->destroy_();
    Game_Widget=new Game(game_type,level,board);
    Gtk::Main::run(*Game_Widget);
}
void Start_b::On_howToPlay_Clicked()
{
    this->hide();
    Help_Widget=new Help_b();
    Gtk::Main::run(*Help_Widget);
}
Start_b::~Start_b()
{
    delete boiteBoutonsx;
}
void Start_b::On_Options_Clicked()
{
    this->hide();
    Options_Widget=new Options_b();
    Gtk::Main::run(*Options_Widget);
}
