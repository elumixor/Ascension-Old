//
// Created by Vladyslav Yazykov on 05/09/2018.
//

#ifndef ASCENSION_CONSTANTS_H
#define ASCENSION_CONSTANTS_H

namespace ASC {
    namespace CONSTANTS {
        namespace CONSTRAINTS {
            extern const unsigned gradient_points_max;
        }
        namespace PARAMS {
            extern const unsigned window_width;
            extern const unsigned window_height;
            extern const unsigned vsync;
            extern const char *window_title;
            extern const unsigned gl_version_major;
            extern const unsigned gl_version_minor;
            extern const float persepctive_zoom;
        }
        namespace DEFAULTS {
            extern const unsigned gradient_point_factor;
        }
        namespace PATHS {
            namespace PROGRAM {
                extern const char *gradient_background[3];
                extern const char *home[2];
            }
            namespace MESHES {
                extern const char * const home[1];
            }
        }
        namespace RESOURCES {
            namespace PROGRAM {
                extern const char *gradient_background;
                extern const char *home;
            }
        }
        namespace UNIFORMS {
            // Gradient Background
            namespace GRB {
                extern const char *points;
                extern const char *points_count;
                extern const char *point_color;
                extern const char *point_location;
                extern const char *point_radius;
                extern const char *point_factor;
            }
            // Matrices
            namespace MATRICES {
                extern const char *projection;
                extern const char *view;
                extern const char *model;
            }
        }
        namespace ERRORS {
            extern const unsigned unknown;
            extern const unsigned file_open;
        }
    }
}

#endif //ASCENSION_CONSTANTS_H
