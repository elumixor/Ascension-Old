//
// Created by Vladyslav Yazykov on 18/11/2018.
//

#ifndef ASCENSION_KEYS_H
#define ASCENSION_KEYS_H

#include "code_organizers.h"
#include "graphics/graphics.h"


//region Helpers

#define __name4(name, n1, n2, n3, n4) __reaction__##name##__##n1##_##n2##_##n3##_##n4
#define __name3(name, n1, n2, n3) __reaction__##name##__##n1##_##n2##_##n3
#define __name2(name, n1, n2) __reaction__##name##__##n1##_##n2
#define __name1(name, n1) __reaction__##name##__##n1
#define __reaction_name(name, ...) _variadic_4(__VA_ARGS__, __name4, __name3,__name2,__name1)(name, __VA_ARGS__)

#define __on_press4(k1, k2, k3, k4) KEYS::check_keys<GLFW_KEY_##k1, GLFW_KEY_##k2, GLFW_KEY_##k3, GLFW_KEY_##k4>
#define __on_press3(k1, k2, k3) KEYS::check_keys<GLFW_KEY_##k1, GLFW_KEY_##k2, GLFW_KEY_##k3>
#define __on_press2(k1, k2) KEYS::check_keys<GLFW_KEY_##k1, GLFW_KEY_##k2>
#define __on_press1(k1) KEYS::check_keys<GLFW_KEY_##k1>
#define __keys_pressed(...) _variadic_4(__VA_ARGS__, __on_press4, __on_press3, __on_press2, __on_press1)(__VA_ARGS__)
#define __reaction(type, ...)\
    static constexpr KEYS::Predicate __reaction_name(type, __VA_ARGS__) {__keys_pressed(__VA_ARGS__)};\
    if ( KEYS:: type (__reaction_name(type, __VA_ARGS__)))\

//endregion

#define PRESS(...) __reaction(press, __VA_ARGS__)
#define HOLD(...) __reaction(hold, __VA_ARGS__)
#define RELEASE(...) __reaction(release, __VA_ARGS__)

NAMESPACE(ASC, GRAPHICS, KEYS)
            typedef bool (*Predicate)();
            typedef bool (*Function)();

            const Predicate condition{nullptr};
            const Function callback{nullptr};

            bool release(Predicate condition);
            bool press(Predicate condition);
            constexpr bool hold(Predicate condition) {
                return condition();
            }

            template<class none = void>
            constexpr bool check_keys() {
                return true;
            }

            template<int key, int... keys>
            constexpr bool check_keys() {
                return glfwGetKey(ASC::GRAPHICS::GL::window, key) == GLFW_PRESS && check_keys<keys...>();
            }
N3

#endif //ASCENSION_KEYS_H
