#include "Main_Window.hpp"
#include"Start.hpp"

Fenetre::Fenetre()
{
    set_title("OTHELLO");
    set_default_size(714,500);
    set_resizable(false);
    set_icon_from_file("img/icon_image.jpg");
    set_position(Gtk::WIN_POS_CENTER);

    Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
    css->load_from_path("style.css");
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    Start=new Gtk::Button("Start");
    Quit=new Gtk::Button("Quit");
    boiteBoutonsH=new Gtk::HButtonBox(Gtk::BUTTONBOX_CENTER, 80);
    add(*boiteBoutonsH);

    Start->set_can_focus(false);
    Quit->set_can_focus(false);
    boiteBoutonsH->pack_start(*Start);
    boiteBoutonsH->pack_start(*Quit);
    boiteBoutonsH->set_margin_top(250);

    Start->signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::On_Start_Clicked));
    Quit->signal_clicked().connect(sigc::ptr_fun(&Gtk::Main::quit));

    show_all();
}
Fenetre::~Fenetre()
{
    delete boiteBoutonsH;
}
void Fenetre::On_Start_Clicked()
{
    this->hide();
     widget=new Start_b(1);
    Gtk::Main::run(*widget);
}
