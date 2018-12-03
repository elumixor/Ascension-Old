//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_BASE_H
#define ASCENSION_BASE_H

#include <util/Singleton.h>
#include "code_organizers.h"

#define SCENE_BASE(name)            \
    protected:                      \
        name();                     \
        SINGLETON(name)             \
        void render() override;     \
        virtual ~name() = default;  \


NAMESPACE(ASC, GRAPHICS, SCENES)
            class SceneBase {
            protected:
                SceneBase() = default;

            SINGLETON_V(SceneBase)

                virtual ~SceneBase() = default;

                virtual void render() = 0;
            };
N3

#endif //ASCENSION_BASE_H
