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
constexpr CString const PARAMS::window_title{"Desktop"};
constexpr unsigned PARAMS::gl_version_major{4};
constexpr unsigned PARAMS::gl_version_minor{0};
constexpr float PARAMS::persepctive_zoom{45.f};

// defaults
constexpr unsigned DEFAULTS::gradient_point_factor{2};

// paths to files
constexpr PATHS::Program PATHS::program{
        "../programs/%s/vertex.glsl",
        "../programs/%s/fragment.glsl",
        "../programs/%s/geometry.glsl"};

constexpr CString const PATHS::MESHES::home[1]{
        "../meshes/generated/home_dummy.ascobj"
};
constexpr CString const PATHS::MESHES::base{"../meshes/generated/%s.ascobj"};

// resources
CString RESOURCES::PROGRAM::gradient_background{"grbg"};
CString RESOURCES::PROGRAM::home{"my shader name"};

// uniforms
CString UNIFORMS::GRB::points{"points"};
CString UNIFORMS::GRB::points_count{"points_count"};
CString UNIFORMS::GRB::point_color{"color"};
CString UNIFORMS::GRB::point_location{"location"};
CString UNIFORMS::GRB::point_radius{"radius"};
CString UNIFORMS::GRB::point_factor{"factor"};
CString UNIFORMS::MATRICES::projection{"projection"};
CString UNIFORMS::MATRICES::view{"view"};
CString UNIFORMS::MATRICES::model{"model"};

// errors
constexpr unsigned ERRORS::unknown{100};
constexpr unsigned ERRORS::file_open{101};
