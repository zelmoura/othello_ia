#ifndef DEF_FENETRE
#define DEF_FENETRE

#include"Start.hpp"
#include"headers.hpp"

class Fenetre : public Gtk::Window {
    protected :
        Gtk::Button *Start,*Quit;
        Gtk::HButtonBox *boiteBoutonsH;
        Start_b *widget;

    public :
        Fenetre();
        ~Fenetre();
        void On_Start_Clicked();
};
#endif

