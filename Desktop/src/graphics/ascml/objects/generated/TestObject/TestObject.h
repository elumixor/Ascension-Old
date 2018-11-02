#ifndef ASCENSION_OBJECTS_TESTOBJECT_H
#define ASCENSION_OBJECTS_TESTOBJECT_H

#include "../..//ObjectBase.h"
#include <glm/vec3.hpp>


struct TestObject : public ObjectBase {
	glm::vec3 position { .3f, .4f, .5f };
	float radius { 0.f };

	void set(const std::string& base_name = "") const override;
};

#endif //ASCENSION_OBJECTBASE_H
