#include "hierarchical_modelling.hpp"
#include "texture.cpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

GLuint shaderProgram1;
GLuint shaderProgram2;
GLuint t;

glm::mat4 rotation_matrix;
// glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
// glm::mat4 model_matrix;
glm::mat4 lookat_matrix;
// glm::mat4 view_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix, normalMatrix, viewMatrix, Light;
glm::vec4 origin = glm::vec4(0.0);
glm::vec4 white = glm::vec4(1.0);

const int num_params = 71;
int in_bet = 24;
GLfloat in_frame[num_params];
GLfloat **key_f;
unsigned char *pRGB;
unsigned char *pRGB1;

//----------------------------------------------------------------

void room()
{
    csX75::primitive p;
    glm::vec4 color_wall = white;
    glm::vec4 color_door = white;
    glm::vec4 color_window = white;
    
    // floor -> 0 
    p = p.draw_cuboid(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(NULL,p, tex_floor);
    node->change_parameters(0.0,-10.0,0.0,90.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(left fourth) -> 1
    p = p.draw_cuboid(color_wall, 20.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(-15.0,-24.5,-25.5,-90.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(top fourth) -> 2
    p = p.draw_cuboid(color_wall, 10.0,20.0,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_s_wall);
    node->change_parameters(15.0,15.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(right fourth) -> 3
    p = p.draw_cuboid(color_wall, 20.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(15.0,-24.5,-25.5,-90.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(bottom fourth) -> 4
    p = p.draw_cuboid(color_wall, 10.0,20.0,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_s_wall);
    node->change_parameters(15.0,-15.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // window -> 5
    p = p.draw_window(color_window, 9.75,9.5,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_glass);
    node->change_parameters(15.0,0.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // front wall -> 6
    p = p.draw_door_wall(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(0.0,24.5,-25.5,-90.0,0.0,0.0);
    room_nodes.push_back(node);

    // door -> 7
    p = p.draw_cuboid(color_door, 11.5,38.0,1.0, glm::vec4(5.75,0,0,0));// fix rotation
    node = new csX75::HNode(room_nodes[6],p, tex_wood);
    node->change_parameters(24.0,-6.5,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

   // left wall -> 8
    p = p.draw_cuboid(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(-24.5,0.0,-25.5,0.0,-90.0,0.0);
    room_nodes.push_back(node);

    // right wall -> 9
    p = p.draw_cuboid(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(24.5,0.0,-25.5,0.0,-90.0,0.0);
    room_nodes.push_back(node);
   
    // ceiling -> 10
    /*p = p.draw_cuboid(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_ceil);
    node->change_parameters(0.0,0.0,-50.0,0.0,0.0,0.0);
    room_nodes.push_back(node);*/
}

//-----------------------------------------------------------------
void table()
{
    csX75::primitive p;
    glm::vec4 color_table = white;

    // plane -> 0 
    p = p.draw_cuboid(color_table, 10.0,10.0,1.0, origin);
    node = new csX75::HNode(NULL,p, tex_wood);
    node->change_parameters(0.0,-5.0,0.0,90.0,0.0,0.0);
    table_nodes.push_back(node);

    // leg1 -> 1 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node = new csX75::HNode(table_nodes[0],p, tex_wood);
    node->change_parameters(-3.0,-3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node);

    // leg2 -> 2 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node = new csX75::HNode(table_nodes[0],p, tex_wood);
    node->change_parameters(-3.0,3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node = new csX75::HNode(table_nodes[0],p, tex_wood);
    node->change_parameters(3.0,-3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node);

    // leg4 -> 4 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node = new csX75::HNode(table_nodes[0],p, tex_wood);
    node->change_parameters(3.0,3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node);
    
}

//-----------------------------------------------------------------
void wall_light()
{
    csX75::primitive p;
    glm::vec4 color_light = white;

    // wall light -> 0 
    p = p.draw_cuboid(color_light, 2.0,2.0,0.5, origin);
    node = new csX75::HNode(NULL,p, tex_light);
    node->change_parameters(-18.0,20.0,0.0,45.0,90.0,0.0);
    wall_light_nodes.push_back(node);
}

//-----------------------------------------------------------------
void side_table()
{
    csX75::primitive p;
    glm::vec4 color_table = white;

    // plane -> 0 
    p = p.draw_cuboid(color_table, 5.0,5.0,0.5, origin);
    node = new csX75::HNode(NULL,p, tex_wood_chair);
    node->change_parameters(20.0,-8.0,-6.0,90.0,0.0,0.0);
    side_table_nodes.push_back(node);

    // leg1 -> 1 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node);

    // leg2 -> 2 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node);

    // leg4 -> 4 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node);
}

//-----------------------------------------------------------------
void lamp()
{
    csX75::primitive p;
    glm::vec4 color_light = white;
    glm::vec4 color_light_body = white;

    // lamp_head -> 0 
    p = p.draw_trapezium_op(color_light, 4.0,4.0,3.0, origin);
    node = new csX75::HNode(NULL,p, tex_pat);
    node->change_parameters(20.0,3.0,-6.0,90.0,180.0,180.0);
    lamp_nodes.push_back(node);

    // lamp_stick -> 1
    p = p.draw_cuboid(color_light_body, 10.0,0.5,0.25, origin);
    node = new csX75::HNode(lamp_nodes[0],p, tex_st);
    node->change_parameters(0.0,0.0,-5.0,0.0,90.0,0.0);
    lamp_nodes.push_back(node);

    // lamp_base -> 2
    p = p.draw_cuboid(color_light_body, 1.0,2.0,2.0, origin);
    node = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node->change_parameters(5.25,0.0,0.0,0.0,0.0,0.0);
    lamp_nodes.push_back(node);

    // lamp_handle_left -> 3
    p = p.draw_cuboid(color_light_body, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node->change_parameters(-4.0,0.0,-0.25,0.0,90.0,0.0);
    lamp_nodes.push_back(node);

    // lamp_handle_right -> 4
    p = p.draw_cuboid(color_light_body, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node->change_parameters(-4.0,0.0,0.25,0.0,90.0,0.0);
    lamp_nodes.push_back(node);

    // lamp_bulb -> 5
    p = p.draw_trapezium(color_light,0.6, 0.5, 0.25, origin);
    node = new csX75::HNode(lamp_nodes[1],p, tex_light);
    node->change_parameters(-5.5,0.0,0.0,0.0,90.0,0.0);
    lamp_nodes.push_back(node);
}

//----------------------------------------------------------------
void side_rack()
{
    csX75::primitive p;
    glm::vec4 color_rack = white;

    // plane1 -> 0 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node = new csX75::HNode(NULL,p, tex_glass);
    node->change_parameters(-20.0,-8.0,20.0,90.0,0.0,0.0);
    side_rack_nodes.push_back(node);

    // leg11 -> 1 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg12 -> 2 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);  

    // leg13 -> 3 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg14 -> 4 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // plane2 -> 5 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node = new csX75::HNode(side_rack_nodes[0],p, tex_glass);
    node->change_parameters(0.0,0.0,-2.0,0.0,0.0,0.0);
    side_rack_nodes.push_back(node);

    // leg21 -> 6 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg22 -> 7 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);  

    // leg23 -> 8 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg24 -> 9 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // plane3 -> 10 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node = new csX75::HNode(side_rack_nodes[5],p, tex_glass);
    node->change_parameters(0.0,0.0,-2.0,0.0,0.0,0.0);
    side_rack_nodes.push_back(node);

    // leg31 -> 11
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg32 -> 12
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);  

    // leg33 -> 13
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);

    // leg34 -> 14
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node);
}

//-----------------------------------------------------------------
void sofa()
{
    csX75::primitive p;
    glm::vec4 color_base = white;
    glm::vec4 color_seat = white;
    glm::vec4 color_han = white;

    // base left -> 0 
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(NULL,p, tex_sofa);
    node->change_parameters(-20.0,-8.0,-19.0,-90.0,0.0,0.0);
    sofa_nodes.push_back(node);

    // base right-> 1
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(sofa_nodes[0],p, tex_sofa);
    node->change_parameters(0.0,-5.0,0.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node);

    // seat left-> 2 
    p = p.draw_cuboid(color_seat, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(sofa_nodes[0],p, tex_sofa);
    node->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node);

    // seat right-> 3
    p = p.draw_cuboid(color_seat, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(sofa_nodes[1],p, tex_sofa);
    node->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node);

    // leg1 -> 4
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node = new csX75::HNode(sofa_nodes[1],p, tex_wood_chair);
    node->change_parameters(-2.0,-2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node);

    // leg2 -> 5
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node = new csX75::HNode(sofa_nodes[1],p, tex_wood_chair);
    node->change_parameters(2.0,-2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node);

    // leg3 -> 6
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node = new csX75::HNode(sofa_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node);

    // leg4 -> 7
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node = new csX75::HNode(sofa_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node);

    // back support left-> 8
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(sofa_nodes[2],p, tex_sofa);
    node->change_parameters(-2.0,0.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node);

    // back support right-> 9
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(sofa_nodes[3],p, tex_sofa);
    node->change_parameters(-2.0,0.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node);

    // handle left-> 10
    p = p.draw_cuboid(color_han, 4.0,1.0,0.25, origin);
    node = new csX75::HNode(sofa_nodes[8],p, tex_wood_chair);
    node->change_parameters(-0.5,-2.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node);

    // handle right-> 11
    p = p.draw_cuboid(color_han, 4.0,1.0,0.25, origin);
    node = new csX75::HNode(sofa_nodes[9],p, tex_wood_chair);
    node->change_parameters(-0.5,2.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node);
}

//-----------------------------------------------------------------
void chair()
{
    csX75::primitive p;
    glm::vec4 color_body = white;

    // base -> 0 
    p = p.draw_cuboid(color_body, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(NULL,p, tex_wood_chair);
    node->change_parameters(18.0,-5.0,9.0,-90.0,0.0,0.0);
    chair_nodes.push_back(node);

    // leg1 -> 1 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,-1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node);

    // leg2 -> 2 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node->change_parameters(-2.0,1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,-1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node);

    // leg4 -> 4 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node);

    // back support -> 5
    p = p.draw_window(color_body, 5.0,5.0,1.0, origin);
    node = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node->change_parameters(2.0,0.0,3.0,0.0,90.0,90.0);
    chair_nodes.push_back(node);
}

//-----------------------------------------------------------------
void box()
{
    csX75::primitive p;
    glm::vec4 color_out = white;
    glm::vec4 color_in = white;
    glm::vec4 color_lid = white;

    // box -> 0
    p = p.draw_cuboid_oc(color_out, color_in, 8.0, 8.0, 6.0, origin);
    node = new csX75::HNode(NULL,p, tex_box); 
    node->change_parameters(0.0,-1.0,0.0,0.0,180.0,0.0);
    box_nodes.push_back(node);

    // lid -> 1
    p = p.draw_plane_ex(color_lid, 8.0, 8.0, 6.0, glm::vec4(0,0,-3.0,0));
    node = new csX75::HNode(box_nodes[0],p, tex_box); 
    node->change_parameters(0.0,4.0,-3.0,0.0,0.0,0.0);
    box_nodes.push_back(node);

}

//---------------------------------------------------------------
void perry()
{
    csX75::primitive p;
    glm::vec4 color_body = glm::vec4( 0.0, 0.75, 0.6, 1.0);
    glm::vec4 color_aux = glm::vec4( 1.0, 1.0, 0.0, 1.0);
    glm::vec4 color_eye = glm::vec4( 1.0, 1.0, 1.0, 1.0);
    glm::vec4 color_eyeball = glm::vec4( 0.0, 0.0, 0.0, 1.0);
    glm::vec4 color_hat = glm::vec4( 0.8, 0.0, 0.4, 1.0);

    //body -> 0
    p = p.draw_trapezoid_cuboid(color_body, 1.5, 0.5, 0.5, 0.5, origin);
    node = new csX75::HNode(NULL,p,tex_light); 
    node->change_parameters(-2.6,3.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //left thigh -> 1
    p = p.draw_cuboid(color_body, 0.2,0.25,0.5, glm::vec4(0,0.125,0,0));
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(-0.65,-1.5,0.0,-100.0,0.0,0.0);
    perry_nodes.push_back(node); 

    //left leg -> 2
    p = p.draw_cuboid(color_body, 0.2,0.25,0.5, origin);
    node = new csX75::HNode(perry_nodes[1],p,tex_light);
    node->change_parameters(0.0,-0.375,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node); 

    //left foot -> 3
    p = p.draw_frustrum(color_aux, 0.2,0.3,0.375, origin);
    node = new csX75::HNode(perry_nodes[2],p,tex_light);
    node->change_parameters(0.0,0.0,-0.375,90.0,0.0,0.0);
    perry_nodes.push_back(node); 

    //right thigh -> 4
    p = p.draw_cuboid(color_body, 0.2,0.25,0.5, glm::vec4(0,0.125,0,0));
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(0.65,-1.5,0.0,0.0,0.0,20.0);
    perry_nodes.push_back(node); 

    //right leg -> 5
    p = p.draw_cuboid(color_body, 0.2,0.25,0.5, origin);
    node = new csX75::HNode(perry_nodes[4],p,tex_light);
    node->change_parameters(0.0,-0.375,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node); 

    //right foot -> 6
    p = p.draw_frustrum(color_aux, 0.2,0.3,0.375, origin);
    node = new csX75::HNode(perry_nodes[5],p,tex_light);
    node->change_parameters(0.0,0.0,-0.375,90.0,0.0,0.0);
    perry_nodes.push_back(node); 

    //left upper arm-> 7
    p = p.draw_cuboid(color_body, 0.4,0.2,0.2, glm::vec4(0.2,0,0,0));
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(-0.75,-0.525,0.0,-30.0,0.0,-60.0);
    perry_nodes.push_back(node);

    //left lower arm-> 8
    p = p.draw_cuboid(color_body, 0.4,0.2,0.2, origin);
    node = new csX75::HNode(perry_nodes[7],p,tex_light);
    node->change_parameters(-0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //left hand-> 9
    p = p.draw_cuboid(color_body, 0.25,0.25,0.4, origin);
    node = new csX75::HNode(perry_nodes[8],p,tex_light);
    node->change_parameters(-0.2,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //right upper arm-> 10
    p = p.draw_cuboid(color_body, 0.4,0.2,0.2, glm::vec4(-0.2,0,0,0));
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(0.75,-0.525,0.0,-10.0,-30.0,-30.0);
    perry_nodes.push_back(node);

    //right lower arm-> 11
    p = p.draw_cuboid(color_body, 0.4,0.2,0.2, origin);
    node = new csX75::HNode(perry_nodes[10],p,tex_light);
    node->change_parameters(0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //right hand-> 12
    p = p.draw_cuboid(color_body, 0.25,0.25,0.4, origin);
    node = new csX75::HNode(perry_nodes[11],p,tex_light);
    node->change_parameters(0.2,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //tail-> 13
    p = p.draw_frustrum(color_aux, 0.25,0.5,1.0, glm::vec4(0,0.25,0,0));
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(0.0,-1.25,0.5,-90.0,0.0,0.0);
    perry_nodes.push_back(node);

    //left eye-> 14
    p = p.draw_trapezium(color_eye, 0.25, 0.25, 0.15, origin);
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(-0.375,-0.175,-0.255,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //left eye ball-> 15
    p = p.draw_trapezium(color_eyeball, 0.1, 0.25, 0.025, origin);
    node = new csX75::HNode(perry_nodes[14],p,tex_light);
    node->change_parameters(0.0,0.0,-0.075,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //right eye-> 16
    p = p.draw_trapezium(color_eye, 0.25, 0.25, 0.15, origin);
    node = new csX75::HNode(perry_nodes[0],p,tex_light);
    node->change_parameters(0.375,-0.175,-0.255,0.0,0.0,0.0);
    perry_nodes.push_back(node);

    //right eye ball-> 17
    p = p.draw_trapezium(color_eyeball, 0.1, 0.25, 0.025, origin);
    node = new csX75::HNode(perry_nodes[16],p,tex_light);
    node->change_parameters(0.0,0.0,-0.075,0.0,0.0,0.0);
    perry_nodes.push_back(node);

   //nose-> 18
   p = p.draw_trapezium(color_aux, 0.625,0.5,1.0, origin);
   node = new csX75::HNode(perry_nodes[0],p,tex_light);
   node->change_parameters(0.0,-0.45,-0.255,0.0,0.0,0.0);
   perry_nodes.push_back(node);

   //accessorize perry-> 19
   p = p.draw_hat( color_hat, 1.6, 0.6, 0.6, origin);
   node = new csX75::HNode(perry_nodes[0],p,tex_light);
   node->change_parameters(0.0,0.5,0.0,0.0,0.0,0.0);
   perry_nodes.push_back(node);
}

//----------------------------------------------------------------

void phineas()
{
    csX75::primitive p;
    glm::vec4 skin = glm::vec4(1.0, 0.8, 0.5, 1.0);
    glm::vec4 blue = glm::vec4(0.0, 0.0, 1.0, 1.0);
    glm::vec4 yellow = glm::vec4(1.0, 1.0, 0.0, 1.0);
    glm::vec4 red = glm::vec4(1.0, 0.0, 0.0, 1.0);

    //hip -> 0
    p = p.draw_cuboid(blue, 1.2,0.2,1.2, origin);
    node = new csX75::HNode(NULL,p,tex_light);
    node->change_parameters(1.2,2.5,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);
    
    // left thigh -> 1
    p = p.draw_cuboid(skin, 0.2,0.5,0.2, glm::vec4(0,0.25,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(-0.4,-0.1,0.0,10.0,-20.0,0.0);
    phineas_nodes.push_back(node);

    //left leg -> 2
    p = p.draw_cuboid(skin, 0.2,0.8,0.2, glm::vec4(0.0,0.4,0,0));
    node = new csX75::HNode(phineas_nodes[1],p,tex_light);
    node->change_parameters(0.0,-0.5,0.0,-90.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left foot -> 3
    p = p.draw_cuboid(blue, 0.3,0.2,0.4, glm::vec4(0,0.1,0,0));
    node = new csX75::HNode(phineas_nodes[2],p,tex_light);
    node->change_parameters(0.0,-0.8,-0.1,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right thigh -> 4
    p = p.draw_cuboid(skin, 0.2,0.5,0.2, glm::vec4(0,0.25,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(0.4,-0.1,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right leg -> 5
    p = p.draw_cuboid(skin, 0.2,0.8,0.2, glm::vec4(0.0,0.4,0,0));
    node = new csX75::HNode(phineas_nodes[4],p,tex_light);
    node->change_parameters(0.0,-0.5,0.0,-40.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right foot -> 6
    p = p.draw_cuboid(blue, 0.3,0.2,0.4, glm::vec4(0,0.1,0,0));
    node = new csX75::HNode(phineas_nodes[5],p,tex_light);
    node->change_parameters(0.0,-0.8,-0.1,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //torso -> 7
    p = p.draw_frustrum(glm::vec4(1.0, 0.4, 0.0, 1.0), 0.2,1.2,1.6, glm::vec4(0,-0.8,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(0.0,0.1,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left upper arm-> 8
    p = p.draw_cuboid(skin, 0.8,0.2,0.2, glm::vec4(0.4,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(-0.1,1.6,0.0,-60.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left lower arm-> 9
    p = p.draw_cuboid(skin, 0.8,0.2,0.2, glm::vec4(0.4,0,0,0));
    node = new csX75::HNode(phineas_nodes[8],p,tex_light);
    node->change_parameters(-0.8,0.0,0.0,0.0,50.0,0.0);
    phineas_nodes.push_back(node);

    //left hand-> 10
    p = p.draw_cuboid(skin, 0.5,0.3,0.2, glm::vec4(0.25,0,0,0));
    node = new csX75::HNode(phineas_nodes[9],p,tex_light);
    node->change_parameters(-0.8,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right upper arm-> 11
    p = p.draw_cuboid(skin, 0.8,0.2,0.2, glm::vec4(-0.4,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(0.1,1.6,0.0,50.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right lower arm-> 12
    p = p.draw_cuboid(skin, 0.8,0.2,0.2, glm::vec4(-0.4,0,0,0));
    node = new csX75::HNode(phineas_nodes[11],p,tex_light);
    node->change_parameters(0.8,0.0,0.0,0.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right hand-> 13
    p = p.draw_cuboid(skin, 0.5,0.3,0.2, glm::vec4(-0.25,0,0,0));
    node = new csX75::HNode(phineas_nodes[12],p,tex_light);
    node->change_parameters(0.8,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //neck-> 14
    p = p.draw_cuboid(skin, 0.2,0.2,0.2, glm::vec4(0,-0.1,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(0.0,1.6,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //head-> 15
    p = p.draw_face(skin, 1.5, glm::vec4(0,-1.5,0,0));
    node = new csX75::HNode(phineas_nodes[14],p,tex_light);
    node->change_parameters(0.0,0.2,0.0,0.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses mid rim -> 16
    p = p.draw_cuboid(yellow, 0.3, 0.1, 0.1, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(1.0,2.0,0.0,0.0,90.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left glass -> 17
    p = p.draw_cuboid(blue, 0.5, 0.5, 0.1, origin);
    node = new csX75::HNode(phineas_nodes[16],p,tex_light); 
    node->change_parameters(-0.4,-0.2,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right glass -> 18
    p = p.draw_cuboid(blue, 0.5, 0.5, 0.1, origin);
    node = new csX75::HNode(phineas_nodes[16],p,tex_light); 
    node->change_parameters(0.4,-0.2,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left rim -> 19
    p = p.draw_cuboid(yellow, 1.0, 0.1, 0.1, glm::vec4(-0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[17],p,tex_light); 
    node->change_parameters(-0.25,0.2,0,-30.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right rim -> 20
    p = p.draw_cuboid(yellow, 1.0, 0.1, 0.1, glm::vec4(0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[18],p,tex_light); 
    node->change_parameters(0.25,0.2,0,-30.0,-60.0,0.0);
    phineas_nodes.push_back(node);

    //hair 1 -> 21
    p = p.draw_prism(red, 0.6, 1.0, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-0.7,2.2,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //hair 2 -> 22
    p = p.draw_prism(red, 0.6, 1.0, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-0.7,2.2,0.0,30.0,30.0,30.0);
    phineas_nodes.push_back(node);

    //hair 3 -> 23
    p = p.draw_prism(red, 0.4, 1.0, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-0.7,2.2,0.0,0.0,-30.0,60.0);
    phineas_nodes.push_back(node);

     //hair 4 -> 24
    p = p.draw_prism(red, 0.6, 1.0, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-0.7,2.2,0.0,-30.0,-30.0,-30.0);
    phineas_nodes.push_back(node);

    //hair 5 -> 25
    p = p.draw_prism(red, 0.4, 1.0, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-0.7,2.2,0.0,0.0,30.0,-60.0);
    phineas_nodes.push_back(node);
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{
  // Load Textures 
  tex_glass=LoadTexture("textures/glass.bmp",2732,2732);
  tex_ceil=LoadTexture("textures/ceil.bmp",800,548);
  tex_floor=LoadTexture("textures/floor.bmp",800,800);
  tex_pat=LoadTexture("textures/lamp_pat.bmp",294,171);
  tex_sofa=LoadTexture("textures/sofa.bmp",1280,617);
  tex_wall=LoadTexture("textures/wall2.bmp",1300,1300);
  tex_wood=LoadTexture("textures/wood.bmp",224,224);
  tex_wood_chair=LoadTexture("textures/wood_chair.bmp",500,375);
  tex_st=LoadTexture("textures/lamp_stand.bmp",251,201);
  tex_box=LoadTexture("textures/box.bmp",768,1024);
  tex_light=LoadTexture("textures/light.bmp",390,280);
  //tex_s_wall=LoadTexture("textures/pattern.bmp",225,225);
  tex_s_wall = tex_wall;
  tex_wall_light=LoadTexture("textures/wall_light.bmp",480,480);

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file1("vshader1.glsl");
  std::string fragment_shader_file1("fshader1.glsl");

  std::vector<GLuint> shaderList1;
  shaderList1.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file1));
  shaderList1.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file1));
// 
  shaderProgram1 = csX75::CreateProgramGL(shaderList1);
  glUseProgram( shaderProgram1 );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram1, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram1, "vColor" ); 
  vNormal = glGetAttribLocation( shaderProgram1, "vNormal" );
  vTexture = glGetAttribLocation( shaderProgram1, "vTexture" );
  uModelViewMatrix = glGetUniformLocation( shaderProgram1, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram1, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram1, "viewMatrix");
  Light = glGetUniformLocation( shaderProgram1, "Light");

  csX75::primitive p;
  p = p.draw_cuboid(glm::vec4(0.0, 0.0, 0.0, 0.0), 200.0,200.0,200.0, origin);
  node = new csX75::HNode(NULL,p, tex_wood_chair);
  node->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  scene_nodes.push_back(node);
  
  room();
  table();
  wall_light();
  side_table();
  side_rack();
  lamp();
  sofa();
  chair();
  phineas();
  box();
  perry();

  root_node = curr_node = scene_nodes[0];  
}

//-----------------------------------------------------------------------------------------------------------------------
glm::vec3 getPoint(float t){
    std::vector<glm::vec3> Points = control_points;
    for(int k=1; k<Points.size(); k++){
        for(int i=0; i<Points.size()-k; i++){
            Points[i] = (1 - t)*Points[i] + t*Points[i+1];
        }
    } 
    return Points[0];
}

void capture_frame(unsigned int framenum)
{
    int SCREEN_WIDTH=768;
    int SCREEN_HEIGHT=768;
    //global pointer float *pRGB
    pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];
    pRGB1 = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];

    // set the framebuffer to read
    //default for double buffered
    glReadBuffer(GL_BACK);

    glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment

    glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
    unsigned int i=0, j=0;
    for(unsigned int x=0; x<SCREEN_WIDTH; x++)
        for(unsigned int y=0;y<SCREEN_HEIGHT; y++)
        {
            i = (3*SCREEN_WIDTH*y) + (3*x);
            j = (3*SCREEN_WIDTH*(SCREEN_HEIGHT-1-y)) + (3*x);
            pRGB1[j] = (unsigned char)(pRGB[i]);
            pRGB1[j+1]=(unsigned char)(pRGB[i+1]);
            pRGB1[j+2]=(unsigned char)(pRGB[i+2]);
        }
    char filename[200];
    sprintf(filename,"./frames/frame_%04d.ppm",framenum);
    std::ofstream out(filename, std::ios::out);
    out<<"P6"<<std::endl;
    out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
    out.write(reinterpret_cast<char const *>(pRGB1), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
    out.close();

    //function to store pRGB in a file named count
    delete pRGB;
}

void renderFrame(GLfloat q[], GLfloat r[], GLfloat k, unsigned int frame)
{
	if(k <= 0.5)
		in_frame[0] = q[0];
	else
		in_frame[0] = r[0];
		
	for(int l=1;l<num_params;l++)
		in_frame[l] = (1-k)*q[l] + k*r[l];			

	csX75::HNode* read_node;
	GLfloat atx, aty, atz, arx, ary, arz;
    int c = 0;
    light = in_frame[c]; c++;    

	read_node = box_nodes[0];
	GLfloat *p = read_node->get_parameters();
	atx = in_frame[c]; c++;
	aty = in_frame[c]; c++;
	atz = in_frame[c]; c++;
	arx = p[3];
	ary = in_frame[c]; c++;
	arz = p[5];
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = box_nodes[1];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	if(in_frame[c] == p[3] && p[3]!=0)
		x = true;
	//if(x && p[3] > -80)
		//x = false;
	arx = in_frame[c]; c++;
	ary = p[4];
	arz = p[5];
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[0];
	p = read_node->get_parameters();
	atx = in_frame[c]; c++;
	aty = in_frame[c]; c++;
	atz = in_frame[c]; c++;
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[1];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[4];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[7];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[10];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = perry_nodes[13];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = p[3];
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[0];
	p = read_node->get_parameters();
	atx = in_frame[c]; c++;
	aty = in_frame[c]; c++;
	atz = in_frame[c]; c++;
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[1];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[4];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[3];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[6];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[8];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[11];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[9];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[12];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[10];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[13];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[7];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[14];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);

	read_node = phineas_nodes[15];
	p = read_node->get_parameters();
	atx = p[0];
	aty = p[1];
	atz = p[2];
	arx = in_frame[c]; c++;
	ary = in_frame[c]; c++;
	arz = in_frame[c]; c++;
	read_node->change_parameters(atx, aty, atz, arx, ary, arz);
}

void renderNode(csX75::HNode* curr, float x, float y)
{
    
    matrixStack.clear();
    curr_node = curr;

    rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(xpos-x), -(ypos), -zpos));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
    rotation_matrix = glm::translate(rotation_matrix, glm::vec3((xpos-x), (ypos), zpos));
    model_matrix = rotation_matrix;

    if(enable_perspective)
        projection_matrix = glm::frustum(-0.5, 0.5, -0.5, 0.5, 1.0, 700.0);
    else
        projection_matrix = glm::ortho(-16.0, 16.0, -16.0, 16.0, -100.0, 200.0);

    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

    //c_rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(c_xpos, 0.0, 0.0));
    glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
    glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;

    //Creating the lookat matrix
    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));
    view_matrix = projection_matrix*lookat_matrix;

    if(!play_back)
	view_matrix = view_matrix * model_matrix;
    
    matrixStack.push_back(view_matrix);

    curr_node->render_tree();
}

void read_keyframes()
{
	std::ifstream myfile;
	myfile.open(filename); 

	GLfloat word;
	GLfloat r[num_params];
	int i = 0, j=0;
	int y=0, z=0;

	// Read the keyframe configuration
	while (myfile >> word && i<num_params) 
	{
		if(i==num_params-1)
		{
			i=0;
			z++;
		}
		else
			i++;
	}   
	key_frame = z;
	myfile.close();

	myfile.open(filename); 
	i=0;
	j=0;

	key_f = (GLfloat**)malloc(key_frame* sizeof(GLfloat*));
	for(int l=0;l<key_frame;l++)
		key_f[l] = (GLfloat*)malloc(num_params* sizeof(GLfloat));

	while (myfile >> word && i<num_params) 
	{ 
		r[i] = word;

		if(i==num_params-1)
		{
			i=0;
			for(int l=0;l<num_params;l++)
				key_f[y][l] = r[l];
			y++;
		}
		else
			i++;
	}

	myfile.close();
}

void renderGL(unsigned int frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    matrixStack.clear();
    
    if(mode)
    {
	    renderNode(room_nodes[0], 0.0, 0.0);
	    renderNode(table_nodes[0], 0.0, 0.0);
	    renderNode(side_table_nodes[0], 0.0, 0.0);
	    renderNode(side_rack_nodes[0], 0.0, 0.0);
	    renderNode(wall_light_nodes[0], 0.0, 0.0);
	    renderNode(sofa_nodes[0], 0.0, 0.0);
	    renderNode(chair_nodes[0], 0.0, 0.0);
	    renderNode(lamp_nodes[0], 0.0, 0.0);
	    renderNode(box_nodes[0], 0.0, 0.0);
	    if((play_back && x) || (play_back && x))
	    {
		    renderNode(phineas_nodes[0], 0.0, 3.0);
		    renderNode(perry_nodes[0], 0.0, 3.0 );
	    }
            if(!play_back || !play_camera)
	    {
		GLfloat *q = box_nodes[1]->get_parameters();
		if(q[3]<=-90 || x){
		    renderNode(phineas_nodes[0], 0.0, 3.0);
		    renderNode(perry_nodes[0], 0.0, 3.0 );}
	    }
	    for(int i=0; i<control_nodes.size(); i++)
            renderNode(control_nodes[i], 0.0, 0.0);
    }
    else
    {
        if(enable_perspective)
            projection_matrix = glm::frustum(-0.5, 0.5, -0.5, 0.5, 1.0, 700.0);
        else
            projection_matrix = glm::ortho(-16.0, 16.0, -16.0, 16.0, -100.0, 200.0);

        c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
        c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
        c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

        //c_rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(c_xpos, 0.0, 0.0));
        glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
        glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
        //Creating the lookat matrix
        lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));
	
        view_matrix = projection_matrix*lookat_matrix;

	if(!play_back)
		view_matrix = view_matrix * model_matrix;

        matrixStack.push_back(view_matrix);

        room_nodes[0]->render_tree();
        table_nodes[0]->render_tree();
        side_table_nodes[0]->render_tree();
        side_rack_nodes[0]->render_tree();
        wall_light_nodes[0]->render_tree();
        sofa_nodes[0]->render_tree();
        chair_nodes[0]->render_tree();
        lamp_nodes[0]->render_tree();
        box_nodes[0]->render_tree();
    if((play_back && x) || (play_camera && x))
    {
        phineas_nodes[0]->render_tree();
        perry_nodes[0]->render_tree();
    }
    if(!play_back || !play_camera)
    {
	GLfloat *q = box_nodes[1]->get_parameters();
	if(q[3]<=-90 || x){
	phineas_nodes[0]->render_tree();
        perry_nodes[0]->render_tree();}
	    }

        for(int i=0; i<control_nodes.size(); i++)
            control_nodes[i]->render_tree();  
    }

    if(play_back || play_camera){
        // std::cout << frame << std::endl;
        // capture_frame(frame);
    }
}

int main(int argc, char** argv)
{
    //! The pointer to the GLFW window
    GLFWwindow* window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(csX75::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
    return -1;

    //We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    //We don't want the old OpenGL 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    //! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(768, 768, "Modelling Music Box", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //! Make the window's context current 
    glfwMakeContextCurrent(window);
	
    //Initialize GLEW
    //Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Problem: glewInit failed, something is seriously wrong.
        std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

    //Print and see what context got enabled
    std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
    std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

    //Keyboard Callback
    glfwSetKeyCallback(window, csX75::key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    csX75::initGL();
    initBuffersGL();
    //glfwSetTime(30.f);

    int numf = 0, j = 0;
    int total_frames = 5*in_bet;
    double du = 1.0/total_frames;
    double u = 0, k = 0;
    double tf = 1/float(in_bet);
    glm::vec3 pos;
    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0)
    {
        if(play_camera){
            if(glfwGetTime()>(double)numf/(double)in_bet){
                pos = getPoint(u);
                c_xpos = pos.x;
                c_ypos = pos.y;
                c_zpos = pos.z;
                // std::cout << u << " " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
                u += du;    
                numf++;
                if(numf == total_frames){
                    play_camera = false;
		    //x= true;
                    numf = 0;
                    u = 0;
		    std::cout<<"Returning to last modelling session"<<std::endl;
                }
            }
        }
        if(play_back){
            if(glfwGetTime() > (double)numf/(double)in_bet){
                if(k<=1){
                    renderFrame(key_f[j], key_f[j+1], k, fr);           
                    k += tf;
                    numf++;
                    fr++;
                }
                else{
                    k = 0;
                    j++;
                }
                            
                if(j == key_frame-1)
                {
                    play_back=false;
		    //x = false;
                    numf = 0;
                    j = 0;
		    std::cout<<"Returning to last modelling session"<<std::endl;
                }
            }
        }
        
        renderGL(fr);
        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//-------------------------------------------------------------------------

