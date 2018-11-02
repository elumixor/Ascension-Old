//
// Created by Vladyslav Yazykov on 11/09/2018.
//

#ifndef ASCENSION_TESTSCENE_H
#define ASCENSION_TESTSCENE_H

#include <graphics/ascml/scenes/Base/Base.h>
#include <graphics/ascml/objects/generated/TestObject/TestObject.h>

class DynamicScene : public ASC::GRAPHICS::SCENES::Base {
private:
    DynamicScene();

    TestObject object;
public:
    void render() override;

    static DynamicScene* instance();

    ~DynamicScene() override;
};


#endif //ASCENSION_TESTSCENE_H
