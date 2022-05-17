#include "Options.hpp"
#include"Start.hpp"

Options_b::Options_b()
{
    set_title("OTHELLO");
    set_default_size(814,550);

    set_icon_from_file("img/icon_image.jpg");
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(50);

    Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
    css->load_from_path("style.css");
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    board_frame=new Gtk::Frame();
    lang_frame=new Gtk::Frame();
    done=new Gtk::Button();
    go_back=new Gtk::Button();
    boxV=new Gtk::VBox(false,20);
    boxH_b=new Gtk::HBox(false,90);
    boxH_l=new Gtk::HBox(false,0);
    boiteH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 80);

    Gtk::RadioButtonGroup b_type;
    b_green=new Gtk::RadioButton(b_type);
    b_beige=new Gtk::RadioButton(b_type);

    Gtk::Image *pic_g=new Gtk::Image("img/Board_Pion/b_green.jpeg");
    Gtk::Image *pic_b=new Gtk::Image("img/Board_Pion/b_beige.jpeg");

    Gtk::RadioButtonGroup l_type;
    l_en=new Gtk::RadioButton(l_type,"English");
    l_fr=new Gtk::RadioButton(l_type," French ");

    board_frame->set_label("\tChoose Your Board : ");
    lang_frame->set_label ("\tChoose Your Language : ");
    done->set_label("Done ");
    go_back->set_label("Return ");

    boiteH->pack_start(*done);
    boiteH->pack_start(*go_back);
    boxH_b->pack_start(*b_green);
    boxH_b->pack_start(*pic_g);
    boxH_b->pack_start(*b_beige);
    boxH_b->pack_start(*pic_b);
    boxH_l->pack_start(*l_en);
    boxH_l->pack_start(*l_fr);

    board_frame->add(*boxH_b);
    lang_frame->add(*boxH_l);

    boxV->pack_start(*board_frame);
    boxV->pack_start(*lang_frame);
    boxV->pack_start(*boiteH);

    done->signal_clicked().connect(sigc::mem_fun(*this,&Options_b::on_done_clicked));
    go_back->signal_clicked().connect(sigc::mem_fun(*this,&Options_b::on_return_clicked));

    add(*boxV);
    show_all_children();

}
Options_b::~Options_b()
{
   delete boxV;
}
void Options_b::on_return_clicked()
{
   this->hide();
   Start_b start(board_type);
   Gtk::Main::run(start);
}

void Options_b::on_done_clicked()
{
    if(b_beige->get_active())
    {
        b_beige->set_active(true);
        board_type=2;
    }
     if(l_fr->get_active())
    {
        lang=2;
    }
    this->on_return_clicked();
}
