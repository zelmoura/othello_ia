#ifndef _OPTIONS_
#define _OPTIONS_

#include"headers.hpp"


class Options_b : public Gtk::Window
{
    private :
      Gtk::Frame *board_frame,*lang_frame;
      Gtk::VBox *boxV;
      Gtk::Button *done,*go_back;
      Gtk::HButtonBox *boiteH;
      Gtk::RadioButton *b_green,*b_beige,*l_fr,*l_en;
      Gtk::HBox *boxH_b,*boxH_l;

      int board_type,lang;

    public :
      Options_b();
      ~Options_b();
      void on_return_clicked();
      void on_done_clicked();

};
#endif // _OPTIONS_
