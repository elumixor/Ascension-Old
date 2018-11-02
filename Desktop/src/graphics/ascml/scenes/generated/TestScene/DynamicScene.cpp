//
// Created by Vladyslav Yazykov on 11/09/2018.
//

#include <cstdio>
#include <GL/glew.h>
#include "DynamicScene.h"

DynamicScene::DynamicScene() {
    printf("DynamicScene is being created...\n");
}

DynamicScene::~DynamicScene() {
    printf("DynamicScene is being destroyed...\n");
}

DynamicScene *DynamicScene::instance() {
    static DynamicScene instance;
    return &instance;
}

void DynamicScene::render() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    object.set();
}


