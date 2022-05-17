#include "Help.hpp"
#include"Start.hpp"
#include"Game.hpp"

Help_b::Help_b()
{
    set_title("OTHELLO");
    set_default_size(814,550);
    set_icon_from_file("img/icon_image.jpg");
    set_border_width(20);
    set_position(Gtk::WIN_POS_CENTER);

    this->override_background_color(Gdk::RGBA("lavender"));

    scroll=new Gtk::ScrolledWindow();
    scroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    board_init=new Gtk::Image("img/regles/board_init.png");
    image_1=new Gtk::Image("img/regles/image_1.png");
    image_2=new Gtk::Image("img/regles/image_2.png");
    image_3=new Gtk::Image("img/regles/image_3.png");
    image_4=new Gtk::Image("img/regles/image_4.png");
    image_5=new Gtk::Image("img/regles/image_5.png");
    image_6=new Gtk::Image("img/regles/image_6.png");
    image_7=new Gtk::Image("img/regles/image_7.png");
    image_8=new Gtk::Image("img/regles/image_8.png");
    image_9=new Gtk::Image("img/regles/image_9.png");

    goBack=new Gtk::Button("Return");
    watch=new Gtk::Button("Watch How");
    boxV=new Gtk::VBox(false,10);
    boxH=new Gtk::HBox(false,0);
    boxH_1=new Gtk::HBox(false,0);
    boxH_2=new Gtk::HBox(false,0);
    boxH_3=new Gtk::HBox(false,0);
    boxH_4=new Gtk::HBox(false,20);
    boiteBoutonsH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 30);

    rules_1=new Gtk::Label;
    rules_1->set_line_wrap();
    rules_1->set_markup("<big><b>\t\t<u><span color='Maroon'>Game Goal</span></u></b></big>\n\n"
                        "\t<b><span color='white'>Have more pawns of his color than the opponent at the end of the game. \n\tThis ends when neither of the two players can play a legal move. This usually happens when all 64 squares are occupied.</span></b>");
    rules_1->set_justify(Gtk::JUSTIFY_LEFT );


    rules_2=new Gtk::Label;
    rules_2->set_line_wrap();
    rules_2->set_justify(Gtk::JUSTIFY_LEFT );
    rules_2->set_markup("<big><b>\t\t<u><span color='Maroon'>Setup</span></u></b></big>\n\n"
                        "\t<b><span color='white'>At the start of the game, two black pawns are placed at e4 and d5 and two white \n\tpawns are placed at d4 and e5 .\n</span></b>"
                        "\t<b><span color='white'>Black always begins and the two opponents then take turns.</span></b>");

    rules_3=new Gtk::Label;
    rules_3->set_line_wrap();
    rules_3->set_justify(Gtk::JUSTIFY_LEFT );
    rules_3->set_markup("<big><b>\t\t<u><span color='Maroon'>Move a Pawn</span></u></b></big>\n\n"
                        "\t<b><span color='white'>On his turn, the player must place a pawn of his color on an empty space in the othellier, adjacent to an opposing pawn. He must also, by placing his pawn, frame one or more opposing pawns between the pawn he \nplaces and a pawn of his color, already placed on the othellier. This sandwich can be done horizontally or vertically , as well as diagnonal . The player turns over the pawn (s) he has just framed, which thus becomes his color. \nThe pawns are neither removed from the othellier, nor moved from one square to another.</span></b>"
                        "\n\n\<b><span color='white'>tBlack's first move is, for example, at f5 (see figure 2). By playing f5, he surrounds the white pawn e5 between the pawn he places and a black pawn already present (here d5); he then turns this pawn over (see figure 3). Black could also have played in e6, c4 or d3. Note that these four black moves are perfectly symmetrical; Black therefore does not have to think about choosing his first move.</span></b>"
                        "\n\n\t<b><span color='white'>Now it's White's turn. It has three possible moves (see figure 4). Indeed, it is mandatory to turn over at least one opposing pawn on each move. White can therefore play f4, f6 or d6.</span></b>");

    rules_4=new Gtk::Label;
    rules_4->set_line_wrap();
    rules_4->set_justify(Gtk::JUSTIFY_LEFT );
    rules_4->set_markup("\t<b><span color='white'>You can frame opposing pawns in all eight directions. In addition, in each direction, several pawns can \nbe framed (see figures 6 and 7). We must then return them all.</span></b>");

    rules_5=new Gtk::Label;
    rules_5->set_line_wrap();
    rules_5->set_justify(Gtk::JUSTIFY_LEFT );
    rules_5->set_markup("\t<b><span color='white'>The Black player played in c6. He then turns over the pawns b6 (framed by a6), b5 (framed by a4), d7 \n(framed by e8), c5 and c4 (framed by c3). Note that neither d6 nor e6 are returned because of the empty cell in f6. \nThere is no chain reaction: the turned pieces cannot be used to turn over others during the same game turn.</span></b>"
                        "\n\n\t<b><span color='white'>Thus, in figure 8, Black plays in a5:</span></b>");

    rules_6=new Gtk::Label;
    rules_6->set_line_wrap();
    rules_6->set_justify(Gtk::JUSTIFY_LEFT );
    rules_6->set_markup("\t<b><span color='white'>Black returns b5 and c5 which are framed. Although c4 is then framed, it is not returned (see figure 9). \nIndeed, it is not framed between the pawn that we have just placed and another pawn. If, on your turn, \nyou cannot place a pawn by turning over an opponent's pawn according to the rules, you must pass your turn and it is your opponent's turn to play. But if a reversal is possible, you cannot avoid it.</span></b>");

    rules_7=new Gtk::Label;
    rules_7->set_line_wrap();
    rules_7->set_justify(Gtk::JUSTIFY_LEFT );
    rules_7->set_markup("<big><b>\t\t<u><span color='FireBrick'>End Of Game</span></u></b></big>\n\n"
                        "\t<b><span color='white'>The game is over when neither player can play anymore. This usually happens when all 64 squares are occupied. But there may still be empty squares where no one can play anymore: for example when all the pawns become of the same color after a flip. Or as in this position (see figure 10).\n</span></b>"
                        "\n\t<b><span color='white'>Neither player can play in b1 since no reversal is possible. The pawns are counted to determine the score. Empty boxes are given to the winner. Here White has 29 pawns, Black 34 and there is an empty square. So Black wins by 35 to 29.</span></b>");


 Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data
           ("label {font-weight:bold;\
                    font-family:Calibri;\
                    font-size: 16px;\
                    background-color: black;\
                    color: white;}");

    rules_1->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_2->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_3->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_4->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_5->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_6->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    rules_7->get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    boxH->pack_start(*board_init);
    boxH->pack_start(*rules_2);
    boxH_1->pack_start(*image_1);
    boxH_1->pack_start(*image_2);
    boxH_1->pack_start(*image_3);
    boxH_2->pack_start(*image_4);
    boxH_2->pack_start(*image_5);
    boxH_2->pack_start(*image_6);
    boxH_3->pack_start(*image_7);
    boxH_3->pack_start(*image_8);
    boxH_4->pack_start(*image_9);
    boxH_4->pack_start(*rules_7);
    boiteBoutonsH->pack_start(*goBack);
    boiteBoutonsH->pack_start(*watch);
    boxV->pack_start(*rules_1);
    boxV->pack_start(*boxH);
    boxV->pack_start(*rules_3);
    boxV->pack_start(*boxH_1);
    boxV->pack_start(*rules_4);
    boxV->pack_start(*boxH_2);
    boxV->pack_start(*rules_5);
    boxV->pack_start(*boxH_3);
    boxV->pack_start(*rules_6);
    boxV->pack_start(*boxH_4);
    boxV->pack_start(*boiteBoutonsH);


    scroll->add(*boxV);
    add(*scroll);


    goBack->signal_clicked().connect(sigc::mem_fun(*this, &Help_b::On_GoBack_Clicked));
    watch->signal_clicked().connect(sigc::mem_fun(*this, &Help_b::On_Watch_Clicked));

    show_all();
}

Help_b::~Help_b()
{
    delete scroll;
}

void Help_b::On_GoBack_Clicked()
{
    this->hide();
    Start_b widget(1);
    Gtk::Main::run(widget);
}

void Help_b::On_Watch_Clicked()
{
    Game game(2);
    Gtk::Main::run(game);

}
