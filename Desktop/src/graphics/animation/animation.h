//
// Created by Vladyslav Yazykov on 04/12/2018.
//

#ifndef ASCENSION_ANIMATION_H
#define ASCENSION_ANIMATION_H

#include <cstdio>
#include <cmath>
#include "code_organizers.h"

NAMESPACE(ASC, GRAPHICS)
        typedef float (*Easing)(float);

        namespace Easings {
            float linear(float);
        }

        class Animation;

        extern Animation *animations;
        extern Animation *end_animations;

        class Animation {
            /// Animation class
            /// \tparam T Animated type
            template<typename T>
            struct Ani {
                static constexpr unsigned STEPS_PER_SECOND{200};

                T *data;
                T diff;

                unsigned steps{0};
                unsigned current{0};
                Easing easing{Easings::linear};

                bool reversed{false};

                Ani(T *start, T finish, float seconds, Easing easing = Easings::linear) : data{start}, easing{easing} {
                    steps = (unsigned) std::floor(seconds * STEPS_PER_SECOND);
                    diff = (finish - *start) / (float) steps;
                }

                /// Perform animation step
                /// \return False if animation ended.
                bool step() {
                    if (reversed) {
                        if (current == 0) return false;
                        current--;
                    } else {
                        if (current == steps) return false;
                        current++;
                    }

                    float percent = (float) current / steps;

                    if (reversed) {
                        *data -= diff * easing(percent);
                    } else {
                        *data += diff * easing(percent);
                    }

                    return true;
                }
            };

            /// Pointer to animation
            void *ani{nullptr};

            /// Linked list pointers
            Animation *_next{nullptr}, *_previous{nullptr};

            /// Animation step function
            bool (*step_function)(void *);

            /// Animation step function
            void (*reverse_function)(void *);

            void (*delete_function)(void *);

        public:

            /// Register and start animation
            template<typename T>
            static void start(Animation **animation, T *start, T finish,
                              float seconds, Easing easing = Easings::linear) {
                if (!(*animation)) {
                    if (!animations) {
                        *animation = animations = end_animations = new Animation;
                    } else {
                        end_animations->_next = new Animation;
                        end_animations->_next->_previous = end_animations;
                        *animation = end_animations = end_animations->_next;
                    }

                    (*animation)->step_function = [](void *ani) -> bool {
                        return ((Ani<T> *) ani)->step();
                    };

                    (*animation)->reverse_function = [](void *ani) {
                        auto p = (Ani<T> *) ani;
                        p->reversed = !p->reversed;
                    };

                    (*animation)->delete_function = [](void *ani) {
                        delete (Ani<T> *) ani;
                    };

                    (*animation)->ani = new Ani<T>(start, finish, seconds, easing);
                }
            }

            /// Perform step
            inline void step() { if (!step_function(ani)) stop(); }

            /// Interrupt animation at point
            void stop() {
                delete_function(ani);

                if (!_previous)
                    animations = nullptr;
                else _previous->_next = _next;

                if (_next) {
                    _next->_previous = _previous;
                }


                delete (this);
            }

            /// Stop animation and launch in reverse
            inline void reverse() { reverse_function(ani); }

            inline Animation *next() const { return _next; }

            Animation &operator=(const Animation *other);
        };

        void free_animations();
N2

#endif //ASCENSION_ANIMATION_H
