#include <utility>

//
// Created by Vladyslav Yazykov on 04/12/2018.
//

#ifndef ASCENSION_ANIMATION_H
#define ASCENSION_ANIMATION_H

#include <cstdio>
#include <cmath>
#include <util/list.h>
#include <util/Singleton.h>
#include <cstring>
#include <cstdlib>
#include <glm/vec3.hpp>
#include <util/map.h>
#include <util/linked_map.h>
#include <util/Bezier.h>
#include "code_organizers.h"

NAMESPACE(ASC, GRAPHICS)
        typedef float (*Easing)(float);

        namespace Easings {
#define Easing inline constexpr float
            Easing linear(float) { return 1.f; }
            Easing in(float t) {
                return 1.f;
            }
            Easing  out(float t) {
                return 0.5f;
            }
            Easing  in_out(float t) {
                return 1.f;
            }
            template <const Bezier<float> &b>
            float bezier(float t) {
                return b(t) / b.integrated;
            }
#undef Easing
        }

        /// Animable wrapper
        class Animable {
            /// Modification operation
            typedef void (*Modify)(void *, void *, float);
            typedef void (*Free)(void *);
            Modify _modify;
            Free _free;

            /// Data pointer
            void *_data;
            void *_diff;

            /// Constructor
            Animable(void *data, void *_diff, Modify modify, Free _free);
        public:
            ~Animable() {
                _free(_diff);
            }

            /// Move constructor
            Animable(Animable &&other) noexcept;
            inline void *data() const { return _data; }

            /// Modify data
            inline void modify(float coefficient = 1.f) { _modify(_data, _diff, coefficient); }

#define Tval(value) *(T*)(value)

            /// Factory function
            template<typename T>
            static Animable from(T *data, const T &diff) {
                T *d = new T(diff);

                return Animable(data, d, [](void *data, void *diff, float coef) {
                    Tval(data) += Tval(diff) * coef;

                }, [](void *diff) {
                    delete (T *) diff;
                });
            }
#undef Tval
        };

        namespace ani {

            /// When triggered fluently changes animable property to another value
            class Sustained {
            protected:
                unsigned steps;
                mutable unsigned current{0};
                mutable Animable animable;
                Easing easing;
            public:
                Sustained(Animable animable, unsigned steps, Easing easing = Easings::linear);
                virtual bool step() const;

                template<typename F>
                void on_finish(F f) {

                }
            };

            /// When active - moves to a state, then returns back
            class Fleeting : Sustained {
                bool _reversed{false};
            public:
                inline Fleeting(Animable animable, unsigned steps, Easing easing = Easings::linear) : Sustained{
                        std::move(animable),
                        steps, easing} {}

                bool step() const override {
                    if (_reversed) {
                        if (current == 0)
                            return false;

                        current--;
                        animable.modify(-easing((float) current / steps));

                        return true;
                    } else {
                        if (current == steps)
                            return true;

                        current++;
                        animable.modify(easing((float) current / steps));

                        return true;
                    }
                }

                void reverse() {
                    _reversed = !_reversed;
                }
            };
        }

        /// Animations container
        extern class Animations {
            static constexpr unsigned STEPS_PER_SECOND{200};

            list<ani::Sustained> _sustained;
            linked_map<ani::Fleeting> _fleeting;
        public:

            /// Starts or resume animation
            template<typename T>
            ani::Sustained &sustained(T *data, T finish, float seconds, Easing easing = Easings::linear) {
                unsigned steps{(unsigned) std::floor(seconds * STEPS_PER_SECOND)};

                return *_sustained.add(std::move(
                        ani::Sustained(Animable::from(data, (finish - *data) / (float) steps), steps, easing)))->data;
            }

            template<typename T>
            ani::Fleeting &fleeting(CString id, T *data, T finish, float seconds, Easing easing = Easings::linear) {
                unsigned steps{(unsigned) std::floor(seconds * STEPS_PER_SECOND)};

                auto fl = _fleeting[id];

                if (fl.is_present()) {
                    fl.value().reverse();
                    return fl.value();
                }

                fl = std::move(ani::Fleeting(Animable::from(data, (finish - *data) / (float) steps), steps, easing));
                return fl.value();
            }

            inline bool is_present(CString id) { return _fleeting[id].is_present(); }

            void reverse(CString id) {
                _fleeting[id].value().reverse();
            }

            void step() {
                _sustained.for_each_indexed([&](const ani::Sustained &s, list<ani::Sustained>::iterator *it) {
                    if (!s.step()) _sustained.remove(it);
                });
                _fleeting.for_each_indexed([&](const ani::Fleeting &s, linked_map<ani::Fleeting>::iterator *it) {
                    if (!s.step()) _fleeting.remove(it);
                });
            }
        } animations;
N2

#endif //ASCENSION_ANIMATION_H
