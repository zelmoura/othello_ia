#ifndef _STARTWIDGET_
#define _STARTWIDGET_

#include"headers.hpp"
#include"Help.hpp"
#include"Options.hpp"
#include"Game.hpp"

class Start_b : public Gtk::Window {

private :
        Gtk::Button *game,*howToPlay,*Options,*Quit;
        Gtk::VButtonBox *boiteBoutonsx;

        Gtk::Label *l_game,*l_level;
        Gtk::Button *done;
        Gtk::VBox *vBox_top, *vBox1, *vBox2;
        Gtk::HBox *hBox1,*hBox2;
        Gtk::HButtonBox *boiteBoutonsH;
        Gtk::RadioButton *level_one , *level_two ,*level_three ;
        Gtk::RadioButton *one_player, *two_players;
        Gtk::HSeparator *Separator1,*Separator2;
        Gtk::Dialog *dialog;

        Game *Game_Widget;
        Help_b *Help_Widget;
        Options_b *Options_Widget;

        int game_type,level,board;

    public :
        Start_b(int board_type);
        ~Start_b();
        void On_done_clicked();
        void On_game_Clicked();
        void On_howToPlay_Clicked();
        void On_Options_Clicked();
        void Disable_Choices();
        void Activate_Choices();

};
#endif // _STARTWIDGET_

