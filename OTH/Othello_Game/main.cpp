#include "Main_Window.hpp"
#include <gtkmm/main.h>

 int main(int argc, char* argv[]) {
    Gtk::Main Kit(argc, argv);
    Fenetre fenetre;
    Gtk::Main::run(fenetre);
    return 0;
}
