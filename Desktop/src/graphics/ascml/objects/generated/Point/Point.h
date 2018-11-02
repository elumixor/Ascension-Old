#ifndef ASCENSION_OBJECTS_POINT_H
#define ASCENSION_OBJECTS_POINT_H

#include "../..//ObjectBase.h"
#include <glm/detail/type_mat4x4.hpp>
#include "TestObject/TestObject.h"

struct Point : public ObjectBase {
	glm::mat4 myMatrix { 1.f };
	TestObject myObject {  };

	void set(const std::string& base_name = "") const override;
};

#endif //ASCENSION_OBJECTBASE_H
