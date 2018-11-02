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
GLuint tex_glass, tex_ceil, tex_floor, tex_pat, tex_sofa, tex_wall, tex_wood, tex_wood_chair, tex_st, tex_box,tex_light;

//----------------------------------------------------------------
void room()
{
    csX75::primitive p;
    glm::vec4 color_wall = white;
    glm::vec4 color_door = white;
    glm::vec4 color_window = white;
    
    // floor -> 0 
    p = p.draw_cuboid(color_wall, 25.0,25.0,1.0, origin);
    node4 = new csX75::HNode(NULL,p, tex_floor);
    node4->change_parameters(0.0,-10.0,0.0,90.0,0.0,0.0);
    room_nodes.push_back(node4);
    
    // left wall -> 1
    /*p = p.draw_cuboid(color_wall, 23.0,25.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[0],p, tex_wall);
    node4->change_parameters(-12.0,0.0,-12.0,0.0,-90.0,0.0);
    room_nodes.push_back(node4);

    // right wall -> 2 
    p = p.draw_cuboid(color_wall, 23.0,25.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[0],p, tex_wall);
    node4->change_parameters(12.0,0.0,-12.0,0.0,-90.0,0.0);
    room_nodes.push_back(node4);

    // back wall(left fourth) -> 3
    p = p.draw_cuboid(color_wall, 6.5,23.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[0],p, tex_wall);
    node4->change_parameters(-8.5,12.0,-12.0,-90.0,0.0,0.0);
    room_nodes.push_back(node4);

    // back wall(top fourth) -> 4
    p = p.draw_cuboid(color_wall, 23.0,6.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[3],p, tex_wall);
    node4->change_parameters(8.5,8.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);

    // back wall(right fourth) -> 5
    p = p.draw_cuboid(color_wall, 6.5,23.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[4],p, tex_wall);
    node4->change_parameters(9.35,-9.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);

    // back wall(bottom fourth) -> 6 
    p = p.draw_cuboid(color_wall, 23.0,6.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[3],p, tex_wall);
    node4->change_parameters(8.5,-8.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);

    // window -> 7
    p = p.draw_window(color_window, 12.5,11.5,1.0, origin);
    node4 = new csX75::HNode(room_nodes[3],p, tex_glass);
    node4->change_parameters(8.5,0.0,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);

    // front wall(left half) -> 8
    p = p.draw_cuboid(color_wall, 12.5,23.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[0],p, tex_wall);
    node4->change_parameters(-5.25,-12.0,-12.0,-90.0,0.0,0.0);
    room_nodes.push_back(node4);

    // front wall(right top half) -> 9
    p = p.draw_cuboid(color_wall, 11.5,11.5,1.0, origin);
    node4 = new csX75::HNode(room_nodes[8],p, tex_wall);
    node4->change_parameters(12.0,5.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);

    // door -> 10
    p = p.draw_cuboid(color_door, 11.5,11.5,1.0, glm::vec4(0,0,0,0));// fix rotation
    node4 = new csX75::HNode(room_nodes[8],p, tex_wood);
    node4->change_parameters(12.0,-5.75,0.0,0.0,0.0,0.0);
    room_nodes.push_back(node4);*/

    // ceiling -> 11
    /*p = p.draw_cuboid(color_wall, 25.0,25.0,1.0, origin);
    node4 = new csX75::HNode(room_nodes[0],p, tex_ceil);
    node4->change_parameters(0.0,0.0,-23.5,0.0,0.0,0.0);
    room_nodes.push_back(node4);*/
}

//-----------------------------------------------------------------
void table()
{
    csX75::primitive p;
    glm::vec4 color_table = white;

    // plane -> 0 
    p = p.draw_cuboid(color_table, 10.0,10.0,1.0, origin);
    node5 = new csX75::HNode(NULL,p, tex_wood);
    node5->change_parameters(0.0,-5.0,0.0,90.0,0.0,0.0);
    table_nodes.push_back(node5);

    // leg1 -> 1 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node5 = new csX75::HNode(table_nodes[0],p, tex_wood);
    node5->change_parameters(-3.0,-3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node5);

    // leg2 -> 2 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node5 = new csX75::HNode(table_nodes[0],p, tex_wood);
    node5->change_parameters(-3.0,3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node5);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node5 = new csX75::HNode(table_nodes[0],p, tex_wood);
    node5->change_parameters(3.0,-3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node5);

    // leg4 -> 4 
    p = p.draw_cuboid(color_table, 5.0,1.0,0.5, origin);
    node5 = new csX75::HNode(table_nodes[0],p, tex_wood);
    node5->change_parameters(3.0,3.0,2.0,0.0,-90.0,0.0);
    table_nodes.push_back(node5);
    
}

//-----------------------------------------------------------------
void wall_light()
{
    csX75::primitive p;
    glm::vec4 color_light = white;

    // wall light -> 0 
    p = p.draw_cuboid(color_light, 2.0,2.0,0.5, origin);
    node6 = new csX75::HNode(NULL,p, tex_light);
    node6->change_parameters(-11.0,10.0,0.0,45.0,90.0,0.0);
    wall_light_nodes.push_back(node6);
}

//-----------------------------------------------------------------
void side_table()
{
    csX75::primitive p;
    glm::vec4 color_table = white;

    // plane -> 0 
    p = p.draw_cuboid(color_table, 5.0,5.0,0.5, origin);
    node7 = new csX75::HNode(NULL,p, tex_wood_chair);
    node7->change_parameters(9.0,-8.0,0.0,90.0,0.0,0.0);
    side_table_nodes.push_back(node7);

    // leg1 -> 1 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node7 = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node7->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node7);

    // leg2 -> 2 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node7 = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node7->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node7);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node7 = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node7->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node7);

    // leg4 -> 4 
    p = p.draw_cuboid(color_table, 2.0,0.5,0.25, origin);
    node7 = new csX75::HNode(side_table_nodes[0],p, tex_wood_chair);
    node7->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_table_nodes.push_back(node7);
}


//-----------------------------------------------------------------
void lamp()
{
    csX75::primitive p;
    glm::vec4 color_light = white;
    glm::vec4 color_light_body = white;

    // lamp_head -> 0 
    p = p.draw_trapezium_op(color_light, 4.0,4.0,3.0, origin);
    node8 = new csX75::HNode(NULL,p, tex_pat);
    node8->change_parameters(10.0,3.0,0.0,90.0,180.0,180.0);
    lamp_nodes.push_back(node8);

    // lamp_stick -> 1
    p = p.draw_cuboid(color_light_body, 10.0,0.5,0.25, origin);
    node8 = new csX75::HNode(lamp_nodes[0],p, tex_st);
    node8->change_parameters(0.0,0.0,-5.0,0.0,90.0,0.0);
    lamp_nodes.push_back(node8);

    // lamp_base -> 2
    p = p.draw_cuboid(color_light_body, 1.0,2.0,2.0, origin);
    node8 = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node8->change_parameters(5.25,0.0,0.0,0.0,0.0,0.0);
    lamp_nodes.push_back(node8);

    // lamp_handle_left -> 3
    p = p.draw_cuboid(color_light_body, 3.0,0.5,0.25, origin);
    node8 = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node8->change_parameters(-4.0,0.0,-0.25,0.0,90.0,0.0);
    lamp_nodes.push_back(node8);

    // lamp_handle_right -> 4
    p = p.draw_cuboid(color_light_body, 3.0,0.5,0.25, origin);
    node8 = new csX75::HNode(lamp_nodes[1],p, tex_st);
    node8->change_parameters(-4.0,0.0,0.25,0.0,90.0,0.0);
    lamp_nodes.push_back(node8);

    // lamp_bulb -> 5
    p = p.draw_trapezium(color_light,0.6, 0.5, 0.25, origin);
    node8 = new csX75::HNode(lamp_nodes[1],p, tex_light);
    node8->change_parameters(-5.5,0.0,0.0,0.0,90.0,0.0);
    lamp_nodes.push_back(node8);
}

//----------------------------------------------------------------
void side_rack()
{
    csX75::primitive p;
    glm::vec4 color_rack = white;

    // plane1 -> 0 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node9 = new csX75::HNode(NULL,p, tex_glass);
    node9->change_parameters(-10.0,-8.0,7.0,90.0,0.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg11 -> 1 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node9->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg12 -> 2 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node9->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);  

    // leg13 -> 3 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node9->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg14 -> 4 
    p = p.draw_cuboid(color_rack, 2.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[0],p, tex_wood_chair);
    node9->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // plane2 -> 5 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node9 = new csX75::HNode(side_rack_nodes[0],p, tex_glass);
    node9->change_parameters(0.0,0.0,-2.0,0.0,0.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg21 -> 6 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node9->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg22 -> 7 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node9->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);  

    // leg23 -> 8 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node9->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg24 -> 9 
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[5],p, tex_wood_chair);
    node9->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // plane3 -> 10 
    p = p.draw_trapezium(color_rack, 5.0,5.0,0.5, origin);
    node9 = new csX75::HNode(side_rack_nodes[5],p, tex_glass);
    node9->change_parameters(0.0,0.0,-2.0,0.0,0.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg31 -> 11
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node9->change_parameters(-2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg32 -> 12
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node9->change_parameters(-2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);  

    // leg33 -> 13
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node9->change_parameters(2.0,-2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);

    // leg34 -> 14
    p = p.draw_cuboid(color_rack, 3.0,0.5,0.25, origin);
    node9 = new csX75::HNode(side_rack_nodes[10],p, tex_wood_chair);
    node9->change_parameters(2.0,2.0,0.5,0.0,-90.0,0.0);
    side_rack_nodes.push_back(node9);
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
    node10 = new csX75::HNode(NULL,p, tex_sofa);
    node10->change_parameters(-9.0,-8.0,-9.0,-90.0,0.0,0.0);
    sofa_nodes.push_back(node10);

    // base right-> 1
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node10 = new csX75::HNode(sofa_nodes[0],p, tex_sofa);
    node10->change_parameters(0.0,-5.0,0.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node10);

    // seat left-> 2 
    p = p.draw_cuboid(color_seat, 5.0,5.0,1.0, origin);
    node10 = new csX75::HNode(sofa_nodes[0],p, tex_sofa);
    node10->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node10);

    // seat right-> 3
    p = p.draw_cuboid(color_seat, 5.0,5.0,1.0, origin);
    node10 = new csX75::HNode(sofa_nodes[1],p, tex_sofa);
    node10->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
    sofa_nodes.push_back(node10);

    // leg1 -> 4
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node10 = new csX75::HNode(sofa_nodes[1],p, tex_wood_chair);
    node10->change_parameters(-2.0,-2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node10);

    // leg2 -> 5
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node10 = new csX75::HNode(sofa_nodes[1],p, tex_wood_chair);
    node10->change_parameters(2.0,-2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node10);

    // leg3 -> 6
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node10 = new csX75::HNode(sofa_nodes[0],p, tex_wood_chair);
    node10->change_parameters(-2.0,2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node10);

    // leg4 -> 7
    p = p.draw_cuboid(color_han, 1.35,0.25,0.5, origin);
    node10 = new csX75::HNode(sofa_nodes[0],p, tex_wood_chair);
    node10->change_parameters(2.0,2.0,-1.0,0.0,90.0,0.0);
    sofa_nodes.push_back(node10);

    // back support left-> 8
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node10 = new csX75::HNode(sofa_nodes[2],p, tex_sofa);
    node10->change_parameters(-2.0,0.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node10);

    // back support right-> 9
    p = p.draw_cuboid(color_base, 5.0,5.0,1.0, origin);
    node10 = new csX75::HNode(sofa_nodes[3],p, tex_sofa);
    node10->change_parameters(-2.0,0.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node10);

    // handle left-> 10
    p = p.draw_cuboid(color_han, 4.0,1.0,0.25, origin);
    node10 = new csX75::HNode(sofa_nodes[8],p, tex_wood_chair);
    node10->change_parameters(-0.5,-2.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node10);

    // handle right-> 11
    p = p.draw_cuboid(color_han, 4.0,1.0,0.25, origin);
    node10 = new csX75::HNode(sofa_nodes[9],p, tex_wood_chair);
    node10->change_parameters(-0.5,2.0,2.0,90.0,90.0,90.0);
    sofa_nodes.push_back(node10);
}


//-----------------------------------------------------------------
void chair()
{
    csX75::primitive p;
    glm::vec4 color_body = white;

    // base -> 0 
    p = p.draw_cuboid(color_body, 5.0,5.0,1.0, origin);
    node11 = new csX75::HNode(NULL,p, tex_wood_chair);
    node11->change_parameters(8.8,-5.0,9.0,-90.0,0.0,0.0);
    chair_nodes.push_back(node11);

    // leg1 -> 1 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node11 = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node11->change_parameters(-2.0,-1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node11);

    // leg2 -> 2 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node11 = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node11->change_parameters(-2.0,1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node11);  

    // leg3 -> 3 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node11 = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node11->change_parameters(2.0,-1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node11);

    // leg4 -> 4 
    p = p.draw_cuboid(color_body, 5.0,0.5,0.25, origin);
    node11 = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node11->change_parameters(2.0,1.0,-2.0,0.0,-90.0,0.0);
    chair_nodes.push_back(node11);

    // back support -> 5
    p = p.draw_window(color_body, 5.0,5.0,1.0, origin);
    node11 = new csX75::HNode(chair_nodes[0],p, tex_wood_chair);
    node11->change_parameters(2.0,0.0,3.0,0.0,90.0,90.0);
    chair_nodes.push_back(node11);
}

//-----------------------------------------------------------------
void box()
{
    csX75::primitive p;
    glm::vec4 color_out = white;
    glm::vec4 color_in = white;
    glm::vec4 color_lid = white;

    // box -> 0
    p = p.draw_cuboid_oc(color_out, color_in, 5.0, 2.0, 3.0, origin);
    node1 = new csX75::HNode(NULL,p, tex_box); 
    node1->change_parameters(0.0,-4.0,0.0,0.0,180.0,0.0);
    box_nodes.push_back(node1);

    // lid -> 1
    p = p.draw_plane_ex(color_lid, 5.0, 2.0, 3.0, glm::vec4(0,0,-1.5,0));
    node1 = new csX75::HNode(box_nodes[0],p, tex_box); 
    node1->change_parameters(0.0,1.0,-1.5,0.0,0.0,0.0);
    box_nodes.push_back(node1);

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
    p = p.draw_trapezoid_cuboid(color_body, 3.0, 1.0, 1.0, 1.0, origin);
    node2 = new csX75::HNode(NULL,p,tex_light); 
    node2->change_parameters(-2.0,1.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left thigh -> 1
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, glm::vec4(0,0.25,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(-1.3,-3.0,0.0,-100.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left leg -> 2
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, origin);
    node2 = new csX75::HNode(perry_nodes[1],p,tex_light);
    node2->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left foot -> 3
    p = p.draw_frustrum(color_aux, 0.4,0.6,0.75, origin);
    node2 = new csX75::HNode(perry_nodes[2],p,tex_light);
    node2->change_parameters(0.0,0.0,-0.75,90.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //right thigh -> 4
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, glm::vec4(0,0.25,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(1.3,-3.0,0.0,0.0,0.0,20.0);
    perry_nodes.push_back(node2); 

    //right leg -> 5
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, origin);
    node2 = new csX75::HNode(perry_nodes[4],p,tex_light);
    node2->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //right foot -> 6
    p = p.draw_frustrum(color_aux, 0.4,0.6,0.75, origin);
    node2 = new csX75::HNode(perry_nodes[5],p,tex_light);
    node2->change_parameters(0.0,0.0,-0.75,90.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left upper arm-> 7
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, glm::vec4(0.4,0,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(-1.5,-1.05,0.0,-30.0,0.0,-60.0);
    perry_nodes.push_back(node2);

    //left lower arm-> 8
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, origin);
    node2 = new csX75::HNode(perry_nodes[7],p,tex_light);
    node2->change_parameters(-0.8,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left hand-> 9
    p = p.draw_cuboid(color_body, 0.5,0.5,0.8, origin);
    node2 = new csX75::HNode(perry_nodes[8],p,tex_light);
    node2->change_parameters(-0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right upper arm-> 10
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, glm::vec4(-0.4,0,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(1.5,-1.05,0.0,-10.0,-30.0,-30.0);
    perry_nodes.push_back(node2);

    //right lower arm-> 11
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, origin);
    node2 = new csX75::HNode(perry_nodes[10],p,tex_light);
    node2->change_parameters(0.8,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right hand-> 12
    p = p.draw_cuboid(color_body, 0.5,0.5,0.8, origin);
    node2 = new csX75::HNode(perry_nodes[11],p,tex_light);
    node2->change_parameters(0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //tail-> 13
    p = p.draw_frustrum(color_aux, 0.5,1.0,2.0, glm::vec4(0,0.5,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(0.0,-2.5,1.0,-90.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left eye-> 14
    p = p.draw_trapezium(color_eye, 0.5, 0.5, 0.3, origin);
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(-0.75,-0.35,-0.51,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left eye ball-> 15
    p = p.draw_trapezium(color_eyeball, 0.2, 0.5, 0.05, origin);
    node2 = new csX75::HNode(perry_nodes[14],p,tex_light);
    node2->change_parameters(0.0,0.0,-0.15,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right eye-> 16
    p = p.draw_trapezium(color_eye, 0.5, 0.5, 0.3, origin);
    node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
    node2->change_parameters(0.75,-0.35,-0.51,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right eye ball-> 17
    p = p.draw_trapezium(color_eyeball, 0.2, 0.5, 0.05, origin);
    node2 = new csX75::HNode(perry_nodes[16],p,tex_light);
    node2->change_parameters(0.0,0.0,-0.15,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

   //nose-> 18
   p = p.draw_trapezium(color_aux, 1.25,1.0,2.0, origin);
   node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
   node2->change_parameters(0.0,-0.9,-0.51,0.0,0.0,0.0);
   perry_nodes.push_back(node2);

   //accessorize perry-> 19
   p = p.draw_hat( color_hat, 3.2, 1.2, 1.2, origin);
   node2 = new csX75::HNode(perry_nodes[0],p,tex_light);
   node2->change_parameters(0.0,1.0,0.0,0.0,0.0,0.0);
   perry_nodes.push_back(node2);
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
    p = p.draw_cuboid(blue, 2.5,0.5,2.5, origin);
    node = new csX75::HNode(NULL,p,tex_light);
    node->change_parameters(2.0,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);
    
    // left thigh -> 1
    p = p.draw_cuboid(skin, 0.4,1.0,0.4, glm::vec4(0,0.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(-0.8,-0.25,0.0,10.0,-20.0,0.0);
    phineas_nodes.push_back(node);

    //left leg -> 2
    p = p.draw_cuboid(skin, 0.4,1.6,0.4, glm::vec4(0.0,0.8,0,0));
    node = new csX75::HNode(phineas_nodes[1],p,tex_light);
    node->change_parameters(0.0,-1.0,0.0,-90.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left foot -> 3
    p = p.draw_cuboid(glm::vec4(0.0, 0.0, 1.0, 1.0), 0.6,0.4,0.8, glm::vec4(0,0.2,0,0));
    node = new csX75::HNode(phineas_nodes[2],p,tex_light);
    node->change_parameters(0.0,-1.6,-0.2,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right thigh -> 4
    p = p.draw_cuboid(skin, 0.4,1.0,0.4, glm::vec4(0,0.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(0.8,-0.25,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right leg -> 5
    p = p.draw_cuboid(skin, 0.4,1.6,0.4, glm::vec4(0.0,0.8,0,0));
    node = new csX75::HNode(phineas_nodes[4],p,tex_light);
    node->change_parameters(0.0,-1.0,0.0,-40.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right foot -> 6
    p = p.draw_cuboid(glm::vec4(0.0, 0.0, 1.0, 1.0), 0.6,0.4,0.8, glm::vec4(0,0.2,0,0));
    node = new csX75::HNode(phineas_nodes[5],p,tex_light);
    node->change_parameters(0.0,-1.6,-0.2,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //torso -> 7
    p = p.draw_frustrum(glm::vec4(1.0, 0.4, 0.0, 1.0), 0.5,2.5,3, glm::vec4(0,-1.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p,tex_light);
    node->change_parameters(0.0,0.25,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left upper arm-> 8
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(-0.25,3.0,0.0,-60.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left lower arm-> 9
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[8],p,tex_light);
    node->change_parameters(-1.6,0.0,0.0,0.0,50.0,0.0);
    phineas_nodes.push_back(node);

    //left hand-> 10
    p = p.draw_cuboid(skin, 1.0,0.6,0.4, glm::vec4(0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[9],p,tex_light);
    node->change_parameters(-1.6,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right upper arm-> 11
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(-0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(0.25,3.0,0.0,50.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right lower arm-> 12
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(-0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[11],p,tex_light);
    node->change_parameters(1.6,0.0,0.0,0.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right hand-> 13
    p = p.draw_cuboid(skin, 1.0,0.6,0.4, glm::vec4(-0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[12],p,tex_light);
    node->change_parameters(1.6,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //neck-> 14
    p = p.draw_cuboid(skin, 0.4,0.4,0.4, glm::vec4(0,-0.2,0,0));
    node = new csX75::HNode(phineas_nodes[7],p,tex_light);
    node->change_parameters(0.0,3.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //head-> 15
    p = p.draw_face(skin, 3.0, glm::vec4(0,-3,0,0));
    node = new csX75::HNode(phineas_nodes[14],p,tex_light);
    node->change_parameters(0.0,0.4,0.0,0.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses mid rim -> 16
    p = p.draw_cuboid(yellow, 0.6, 0.2, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(2.0,4.0,0.0,0.0,90.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left glass -> 17
    p = p.draw_cuboid(blue, 1.0, 1.0, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[16],p,tex_light); 
    node->change_parameters(-0.8,-0.4,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right glass -> 18
    p = p.draw_cuboid(blue, 1.0, 1.0, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[16],p,tex_light); 
    node->change_parameters(0.8,-0.4,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left rim -> 19
    p = p.draw_cuboid(yellow, 2.0, 0.2, 0.2, glm::vec4(-1.0,0,0,0));
    node = new csX75::HNode(phineas_nodes[17],p,tex_light); 
    node->change_parameters(-0.5,0.4,0,-30.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right rim -> 20
    p = p.draw_cuboid(yellow, 2.0, 0.2, 0.2, glm::vec4(1.0,0,0,0));
    node = new csX75::HNode(phineas_nodes[18],p,tex_light); 
    node->change_parameters(0.5,0.4,0,-30.0,-60.0,0.0);
    phineas_nodes.push_back(node);

    //hair 1 -> 21
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-1.4,4.4,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //hair 2 -> 22
    p = p.draw_prism(red, 0.9, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-1.4,4.4,0.0,30.0,30.0,30.0);
    phineas_nodes.push_back(node);

    //hair 3 -> 23
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-1.4,4.4,0.0,0.0,-30.0,60.0);
    phineas_nodes.push_back(node);

     //hair 4 -> 24
    p = p.draw_prism(red, 0.9, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-1.4,4.4,0.0,-30.0,-30.0,-30.0);
    phineas_nodes.push_back(node);

    //hair 5 -> 25
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p,tex_light); 
    node->change_parameters(-1.4,4.4,0.0,0.0,30.0,-60.0);
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
  p = p.draw_cuboid(glm::vec4(0.0, 0.0, 0.0, 0.0), 100.0,100.0,100.0, origin);
  node3 = new csX75::HNode(NULL,p, tex_wood_chair);
  node3->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  scene_nodes.push_back(node3);
  
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
    //projection_matrix = glm::ortho(-14.0, 14.0, -14.0, 14.0, 20.0, -40.0);
   
    matrixStack.clear();
    curr_node = curr;

    rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(xpos-x), -ypos, -zpos));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
    rotation_matrix = glm::translate(rotation_matrix, glm::vec3((xpos-x), ypos, zpos));
    model_matrix = rotation_matrix;

    projection_matrix = glm::ortho(-14.0, 14.0, -14.0, 14.0, 200.0, -400.0);

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
	    projection_matrix = glm::ortho(-14.0, 14.0, -14.0, 14.0, 200.0, -400.0);
 
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

