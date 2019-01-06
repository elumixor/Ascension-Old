//
// Created by Vladyslav Yazykov on 16/11/2018.
//

#ifndef ASCENSION_CODE_ORGANIZERS_H
#define ASCENSION_CODE_ORGANIZERS_H

//#define PRODUCTION

#define _variadic_(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define _variadic_4(_1, _2, _3, _4, NAME, ...) NAME
#define _variadic_3(_1, _2, _3, NAME, ...) NAME
#define _variadic_2(_1, _2, NAME, ...) NAME

//region Namespaces
#define __namespace_two(x, y) namespace x { namespace y {
#define __namespace_three(x, y, z) namespace x { namespace y { namespace z {
#define NAMESPACE(...) _variadic_3(__VA_ARGS__, __namespace_three, __namespace_two)(__VA_ARGS__)

#define N3 }}}
#define N2 }}
//endregion

//region Uniforms
#define BASE_NAME base_name + (base_name.empty() ? "" : ".")
#define UNI_SET(name) ASC::GRAPHICS::PROGRAM::set(#name, name)
#define UNI_FIELD(name) ASC::GRAPHICS::PROGRAM::set((BASE_NAME + #name).c_str(), name)
#define UNI_INT(name) ASC::GRAPHICS::PROGRAM::set_int((BASE_NAME + #name).c_str(), name)
#define UNI(method, name)ASC::GRAPHICS::PROGRAM::method(#name, name)
#define UNI_BOOL(name) ASC::GRAPHICS::PROGRAM::set_bool((BASE_NAME + #name).c_str(), name)
#define UNI_ARRAY(name, count) ASC::GRAPHICS::PROGRAM::set_array(BASE_NAME + #name, count, name);
//endregion

#define String std::string
#define CString const char *

#define USE_PROGRAM(program) glUseProgram(ASC::GRAPHICS::PROGRAM::active = program)

#if (PRODUCTION)
#define LOG(message)
#define ERROR(message)
#else
#define LOG(message) printf("LOG: %s\n", String(message).c_str())
#define ERROR(message) fprintf(stderr, "ERROR: %s\n", String(message).c_str());
#endif

#define i_range(start, count) for (unsigned i = start; i < count; ++i)

#define CRASH exit(1);

#define __require_simple(condition) if (!(condition)) { CRASH }
#define __require_message(condition, message) if (!(condition)) { ERROR(message); CRASH }
#define require(...) _variadic_2(__VA_ARGS__, __require_message, __require_simple)(__VA_ARGS__)

#endif //ASCENSION_CODE_ORGANIZERS_H
