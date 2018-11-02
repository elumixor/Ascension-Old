#include <graphics/ascml/AscmlApi.h>
#include <GL/glew.h>
#include "Point.h"

void Point::set(const std::string& base_name = "") const {
	glUniformMatrix4fv(glGetUniformLocation(*api.program, (base_name + ".myMatrix").c_str()), 1, GL_FALSE, &this->myMatrix[0][0]);
	myObject.set(base_name + ".myObject");
}
