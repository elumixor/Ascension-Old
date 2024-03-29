#include <iostream>

#include <GL/glew.h>

#include <dlfcn.h>
#include <graphics/Mainframe/Mainframe.h>
#include <graphics/scenes/Home/Home.h>
#include <array>
#include "util/math.h"

int main() {

    // initialize mainframe
    auto mf = ASC::GRAPHICS::Mainframe::instance();

    // set start states
    mf->scene = ASC::GRAPHICS::SCENES::Home::instance();
    // start loop
    mf->start();

    return 0;
}
