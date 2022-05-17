#ifndef _HOWTOWIDGET_
#define _HOWTOWIDGET_

#include"headers.hpp"


class Help_b : public Gtk::Window
{
protected :


    Gtk::Button *goBack;
    Gtk::Button *watch;
    Gtk::Label *rules_1,*rules_2,*rules_3,*rules_4,*rules_5,*rules_6,*rules_7;
    Gtk::Image *board_init,*image_1,*image_2,*image_3,*image_4,*image_5,*image_6,*image_7,*image_8,*image_9;
    Gtk::VBox *boxV;
    Gtk::HBox *boxH,*boxH_1,*boxH_2,*boxH_3,*boxH_4;
    Gtk::HButtonBox *boiteBoutonsH;
    Gtk::ScrolledWindow *scroll;

    //Start


public :
    Help_b();
    ~Help_b();
    void On_GoBack_Clicked();
    void On_Watch_Clicked();
};
#endif // _HOWTOWIDGET_
