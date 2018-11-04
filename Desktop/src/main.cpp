#include <iostream>

#include <GL/glew.h>

#include <dlfcn.h>
#include <graphics/Mainframe/Mainframe.h>
#include <graphics/ascml/AscmlApi.h>

int main() {
    void *hndl = dlopen("src/graphics/ascml/libASCML.dylib", RTLD_LAZY);
    if (!hndl) {
        return -1;            // library not present
    }
/**/
    auto ascml = (AscmlApi *) dlsym(hndl, "api");
    ascml->program = &ASC::GRAPHICS::PROGRAM::active;

    ASC::GRAPHICS::SCENES::Base *dynamicScene = ascml->scenes["DynamicScene"]();

    // initialize mainframe
    auto mf = ASC::GRAPHICS::Mainframe::in/**/stance();
    // set start states
//    mf->scene = ASC::GRAPHICS::SCENES::Home::instance();
    mf->scene = dynamicScene;
    // start loop
    mf->start();

    return 0;
}