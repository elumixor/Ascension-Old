//
// Created by Vladyslav Yazykov on 02/09/2018.
//

#ifndef ASCENSION_BASE_H
#define ASCENSION_BASE_H

namespace ASC {
    namespace GRAPHICS {
        namespace SCENES {

            class Base {
            protected:
                Base() = default;

            public:
                Base(const Base &) = delete;

                void operator=(const Base &) = delete;

                virtual ~Base() = default;

                virtual void render() = 0;
            };
        }
    }
}


#endif //ASCENSION_BASE_H
