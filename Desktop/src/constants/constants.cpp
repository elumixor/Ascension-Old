//
// Created by Vladyslav Yazykov on 04/09/2018.
//

#include "constants.h"

using namespace ASC::CONSTANTS;

// constraints
constexpr unsigned CONSTRAINTS::gradient_points_max{5};

// parameters
constexpr unsigned PARAMS::window_width{1024};
constexpr unsigned PARAMS::window_height{768};
constexpr unsigned PARAMS::vsync{1};
const char *PARAMS::window_title{"Desktop"};
constexpr unsigned PARAMS::gl_version_major{4};
constexpr unsigned PARAMS::gl_version_minor{0};
constexpr float PARAMS::persepctive_zoom{45.f};

// defaults
constexpr unsigned DEFAULTS::gradient_point_factor{2};

// paths to files
const char *PATHS::PROGRAM::home[2]{
        "../programs/home/vertex.glsl",
        "../programs/home/fragment.glsl"
};
const char *PATHS::PROGRAM::gradient_background[3]{
        "../programs/gradient_background/vertex.glsl",
        "../programs/gradient_background/fragment.glsl",
        "../programs/gradient_background/geometry.glsl"
};
const char *const PATHS::MESHES::home[1]{
        "../meshes/bin/home_dummy.ascobj"
};

// resources
const char *RESOURCES::PROGRAM::gradient_background{"grbg"};
const char *RESOURCES::PROGRAM::home{"my shader name"};

// uniforms
const char *UNIFORMS::GRB::points{"points"};
const char *UNIFORMS::GRB::points_count{"points_count"};
const char *UNIFORMS::GRB::point_color{"color"};
const char *UNIFORMS::GRB::point_location{"location"};
const char *UNIFORMS::GRB::point_radius{"radius"};
const char *UNIFORMS::GRB::point_factor{"factor"};
const char *UNIFORMS::MATRICES::projection{"projection"};
const char *UNIFORMS::MATRICES::view{"view"};
const char *UNIFORMS::MATRICES::model{"model"};

// errors
constexpr unsigned ERRORS::unknown{100};
constexpr unsigned ERRORS::file_open{101};
