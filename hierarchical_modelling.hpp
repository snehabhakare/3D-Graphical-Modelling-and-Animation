#ifndef _HIERARCHICAL_MODELLING_HPP_
#define _HIERARCHICAL_MODELLING_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"
#include "primitive.hpp"

// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = -22.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true, enable_perspective=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Shader program attribs
GLuint vPosition,vColor,vNormal,vTexture;
int light=0;
bool mode=true;
bool play_back=false;
bool play_camera = false;
bool play_s = false;
int key_frame = 0;
unsigned int fr = 0;
std::string filename = "keyframes2.txt";
bool x = false;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;
glm::mat4 projection_matrix;
glm::mat4 lookat_matrix;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* node;

std::vector<csX75::HNode*> scene_nodes;
std::vector<csX75::HNode*> phineas_nodes;
std::vector<csX75::HNode*> box_nodes;
std::vector<csX75::HNode*> perry_nodes;
std::vector<csX75::HNode*> room_nodes;
std::vector<csX75::HNode*> table_nodes;
std::vector<csX75::HNode*> wall_light_nodes;
std::vector<csX75::HNode*> side_table_nodes;
std::vector<csX75::HNode*> side_rack_nodes;
std::vector<csX75::HNode*> lamp_nodes;
std::vector<csX75::HNode*> sofa_nodes;
std::vector<csX75::HNode*> chair_nodes;
std::vector<csX75::HNode*> control_nodes;

std::vector<glm::vec3> control_points;

GLuint tex_glass, tex_ceil, tex_floor, tex_pat, tex_sofa, tex_wall, tex_wall_t, tex_wood, tex_wood_chair, tex_st, tex_box, tex_light, tex_s_wall, tex_wall_light;
void read_keyframes();
//-------------------------------------------------------------------------

#endif
