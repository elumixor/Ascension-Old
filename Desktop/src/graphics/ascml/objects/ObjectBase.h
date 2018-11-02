//
// Created by Vladyslav Yazykov on 18/09/2018.
//

#ifndef ASCENSION_OBJECTBASE_H
#define ASCENSION_OBJECTBASE_H

#include <string>

class ObjectBase {
public:
    virtual void set(const std::string& base_name = "") const = 0;
};

#endif //ASCENSION_OBJECTBASE_H
