#include <graphics/ascml/AscmlApi.h>
#include <GL/glew.h>
#include "TestObject.h"

void TestObject::set(const std::string& base_name = "") const {
	glUniform3fv(glGetUniformLocation(*api.program, (base_name + ".position").c_str()), 1, &this->position[0]);
	glUniform1f(glGetUniformLocation(*api.program, (base_name + ".radius").c_str()), this->radius);
}
