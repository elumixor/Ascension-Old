#include <GL/glew.h>
#include "Point.h"
#include "graphics/graphics.h"

void ASC::GRAPHICS::RESOURCES::Point::render(const String &base_name) const {
    UNI_FIELD(color);
    UNI_FIELD(location);
    UNI_FIELD(radius);
    UNI_INT(factor);
}
