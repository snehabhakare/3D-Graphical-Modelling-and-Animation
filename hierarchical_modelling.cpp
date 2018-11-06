#include "hierarchical_modelling.hpp"
#include "texture.cpp"

GLuint shaderProgram1;
GLuint shaderProgram2;
GLuint t;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 model_matrix;
glm::mat4 lookat_matrix;

glm::mat4 view_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix, normalMatrix, viewMatrix, Light;
glm::vec4 origin = glm::vec4(0.0);
glm::vec4 white = glm::vec4(1.0);

  // Load Textures 
GLuint tex_glass, tex_ceil, tex_floor, tex_pat, tex_sofa, tex_wall, tex_wall_t, tex_wood, tex_wood_chair, tex_st, tex_box,tex_light;

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
    p = p.draw_cuboid(color_wall, 6.5,23.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(-8.5,24.0,-12.0,-90.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(top fourth) -> 2
    p = p.draw_cuboid(color_wall, 23.0,6.0,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_wall);
    node->change_parameters(8.25,8.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(right fourth) -> 3
    p = p.draw_cuboid(color_wall, 6.5,23.0,1.0, origin);
    node = new csX75::HNode(room_nodes[2],p, tex_wall);
    node->change_parameters(9.35,-9.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // back wall(bottom fourth) -> 4
    p = p.draw_cuboid(color_wall, 23.0,6.0,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_wall);
    node->change_parameters(8.5,-8.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // window -> 5
    p = p.draw_window(color_window, 12.5,11.5,1.0, origin);
    node = new csX75::HNode(room_nodes[1],p, tex_glass);
    node->change_parameters(8.5,0.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

    // front wall -> 6
    p = p.draw_door_wall(color_wall, 50.0,23.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(0.0,-24.0,-12.0,-90.0,0.0,0.0);
    room_nodes.push_back(node);

    // door -> 7
    p = p.draw_cuboid(color_door, 11.5,17.5,1.0, glm::vec4(5.75,0,0,0));// fix rotation
    node = new csX75::HNode(room_nodes[6],p, tex_wood);
    node->change_parameters(24,-2.9,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node);

   // left wall -> 8
    p = p.draw_cuboid(color_wall, 23.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(-24.5,0.0,-12.0,0.0,-90.0,0.0);
    room_nodes.push_back(node);

    // right wall -> 9
    p = p.draw_cuboid(color_wall, 23.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_wall);
    node->change_parameters(24.5,0.0,-12.0,0.0,-90.0,0.0);
    room_nodes.push_back(node);
   
    // ceiling -> 10
    /*p = p.draw_cuboid(color_wall, 50.0,50.0,1.0, origin);
    node = new csX75::HNode(room_nodes[0],p, tex_ceil);
    node->change_parameters(0.0,0.0,-23.5,0.0,0.0,0.0);
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
    node->change_parameters(-11.0,10.0,0.0,45.0,90.0,0.0);
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
    node->change_parameters(15.0,-8.0,10.0,90.0,0.0,0.0);
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
    node->change_parameters(15.0,3.0,10.0,90.0,180.0,180.0);
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
    node->change_parameters(-15.0,-8.0,10.0,90.0,0.0,0.0);
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
    node->change_parameters(-15.0,-8.0,-2.0,-90.0,0.0,0.0);
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
    node->change_parameters(8.8,-5.0,9.0,-90.0,0.0,0.0);
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
    p = p.draw_cuboid_oc(color_out, color_in, 5.0, 4.0, 3.0, origin);
    node = new csX75::HNode(NULL,p, tex_box); 
    node->change_parameters(0.0,-3.0,0.0,0.0,180.0,0.0);
    box_nodes.push_back(node);

    // lid -> 1
    p = p.draw_plane_ex(color_lid, 5.0, 4.0, 3.0, glm::vec4(0,0,-1.5,0));
    node = new csX75::HNode(box_nodes[0],p, tex_box); 
    node->change_parameters(0.0,2.0,-1.5,0.0,0.0,0.0);
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
    node->change_parameters(-1.0,1.5,0.0,0.0,0.0,0.0);
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
    node->change_parameters(2.0,1.0,0.0,0.0,0.0,0.0);
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
  tex_wall=LoadTexture("textures/wall.bmp",1024,680);
  tex_wood=LoadTexture("textures/wood.bmp",224,224);
  tex_wood_chair=LoadTexture("textures/wood_chair.bmp",500,375);
  tex_st=LoadTexture("textures/lamp_stand.bmp",251,201);
  tex_box=LoadTexture("textures/box.bmp",768,1024);
  tex_light=LoadTexture("textures/light.bmp",390,280);

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

void renderNode(csX75::HNode* curr, float x)
{
    
    matrixStack.clear();
    curr_node = curr;

    rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(xpos-x), -ypos, -zpos));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
    rotation_matrix = glm::translate(rotation_matrix, glm::vec3((xpos-x), ypos, zpos));
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
    view_matrix = projection_matrix*lookat_matrix*model_matrix;
    
    matrixStack.push_back(view_matrix);

    curr_node->render_tree();
}

void renderGL(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     matrixStack.clear();
    if(mode)
    {
	    renderNode(room_nodes[0], 0.0);
	    renderNode(table_nodes[0], 0.0);
	    renderNode(side_table_nodes[0], 0.0);
	    renderNode(side_rack_nodes[0], 0.0);
	    renderNode(wall_light_nodes[0], 0.0);
	    renderNode(sofa_nodes[0], 0.0);
	    renderNode(chair_nodes[0], 0.0);
	    renderNode(lamp_nodes[0], 0.0);
	    renderNode(box_nodes[0], 0.0);
	    renderNode(phineas_nodes[0], 2.0);
	    renderNode(perry_nodes[0], -2.0);
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
	    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0,0,0),glm::vec3(c_up));

	    view_matrix = projection_matrix*lookat_matrix*model_matrix;
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
	    perry_nodes[0]->render_tree();
	    phineas_nodes[0]->render_tree();
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

    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0)
    {
        // Render here
        renderGL();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//-------------------------------------------------------------------------

