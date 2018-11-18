//
// Created by Vladyslav Yazykov on 05/09/2018.
//

#ifndef ASCENSION_CONSTANTS_H
#define ASCENSION_CONSTANTS_H

#include "code_organizers.h"

namespace ASC {
    namespace CONSTANTS {
        namespace CONSTRAINTS {
            extern const unsigned gradient_points_max;
        }
        namespace PARAMS {
            extern const unsigned window_width;
            extern const unsigned window_height;
            extern const unsigned vsync;
            extern CString const window_title;
            extern const unsigned gl_version_major;
            extern const unsigned gl_version_minor;
            extern const float persepctive_zoom;
        }
        namespace DEFAULTS {
            extern const unsigned gradient_point_factor;
        }
        namespace PATHS {
            struct Program {
                CString vertex;
                CString fragment;
                CString geometry;
            };
            extern const Program program;
            namespace MESHES {
                extern CString const home[1];
                extern CString const base;
            }
        }
        namespace RESOURCES {
            namespace PROGRAM {
                extern CString gradient_background;
                extern CString home;
            }
        }
        namespace UNIFORMS {
            // Gradient Background
            namespace GRB {
                extern CString points;
                extern CString points_count;
                extern CString point_color;
                extern CString point_location;
                extern CString point_radius;
                extern CString point_factor;
            }
            // Matrices
            namespace MATRICES {
                extern CString projection;
                extern CString view;
                extern CString model;
            }
        }
        namespace ERRORS {
            extern const unsigned unknown;
            extern const unsigned file_open;
        }
    }
}

#endif //ASCENSION_CONSTANTS_H
