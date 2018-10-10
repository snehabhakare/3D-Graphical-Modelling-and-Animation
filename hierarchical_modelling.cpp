#include "hierarchical_modelling.hpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;

glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
glm::vec4 origin = glm::vec4(0.0);

//-----------------------------------------------------------------
void box()
{
    csX75::primitive p;
    glm::vec4 color_out = glm::vec4(0.0, 0.0, 0.8, 1.0);
    glm::vec4 color_in = glm::vec4(0.8, 0.0, 0.0, 1.0);
    glm::vec4 color_lid = glm::vec4(0.0, 0.8, 0.0, 1.0);

    // box -> 0
    p = p.draw_cuboid_oc(color_out, color_in, 5.0, 2.0, 3.0, origin);
    node1 = new csX75::HNode(NULL,p); 
    node1->change_parameters(-6.0,0.0,0.0,0.0,180.0,0.0);
    box_nodes.push_back(node1);

    // lid -> 1
    p = p.draw_plane_ex(color_lid, 5.0, 2.0, 3.0, glm::vec4(0,0,-1.5,0));
    node1 = new csX75::HNode(box_nodes[0],p); 
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
    node2 = new csX75::HNode(NULL,p); 
    node2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left thigh -> 1
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, glm::vec4(0,0.25,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(-1.3,-3.0,0.0,-100.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left leg -> 2
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, origin);
    node2 = new csX75::HNode(perry_nodes[1],p);
    node2->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left foot -> 3
    p = p.draw_frustrum(color_aux, 0.4,0.6,0.75, origin);
    node2 = new csX75::HNode(perry_nodes[2],p);
    node2->change_parameters(0.0,0.0,-0.75,90.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //right thigh -> 4
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, glm::vec4(0,0.25,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(1.3,-3.0,0.0,0.0,0.0,20.0);
    perry_nodes.push_back(node2); 

    //right leg -> 5
    p = p.draw_cuboid(color_body, 0.4,0.5,1.0, origin);
    node2 = new csX75::HNode(perry_nodes[4],p);
    node2->change_parameters(0.0,-0.75,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //right foot -> 6
    p = p.draw_frustrum(color_aux, 0.4,0.6,0.75, origin);
    node2 = new csX75::HNode(perry_nodes[5],p);
    node2->change_parameters(0.0,0.0,-0.75,90.0,0.0,0.0);
    perry_nodes.push_back(node2); 

    //left upper arm-> 7
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, glm::vec4(0.4,0,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(-1.5,-1.05,0.0,-30.0,0.0,-60.0);
    perry_nodes.push_back(node2);

    //left lower arm-> 8
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, origin);
    node2 = new csX75::HNode(perry_nodes[7],p);
    node2->change_parameters(-0.8,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left hand-> 9
    p = p.draw_cuboid(color_body, 0.5,0.5,0.8, origin);
    node2 = new csX75::HNode(perry_nodes[8],p);
    node2->change_parameters(-0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right upper arm-> 10
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, glm::vec4(-0.4,0,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(1.5,-1.05,0.0,-10.0,-30.0,-30.0);
    perry_nodes.push_back(node2);

    //right lower arm-> 11
    p = p.draw_cuboid(color_body, 0.8,0.4,0.4, origin);
    node2 = new csX75::HNode(perry_nodes[10],p);
    node2->change_parameters(0.8,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right hand-> 12
    p = p.draw_cuboid(color_body, 0.5,0.5,0.8, origin);
    node2 = new csX75::HNode(perry_nodes[11],p);
    node2->change_parameters(0.4,0.0,0.0,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //tail-> 13
    p = p.draw_frustrum(color_aux, 0.5,1.0,2.0, glm::vec4(0,0.5,0,0));
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(0.0,-2.5,1.0,-90.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left eye-> 14
    p = p.draw_trapezium(color_eye, 0.5, 0.5, 0.3, origin);
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(-0.75,-0.35,-0.51,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //left eye ball-> 15
    p = p.draw_trapezium(color_eyeball, 0.2, 0.5, 0.05, origin);
    node2 = new csX75::HNode(perry_nodes[14],p);
    node2->change_parameters(0.0,0.0,-0.15,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right eye-> 16
    p = p.draw_trapezium(color_eye, 0.5, 0.5, 0.3, origin);
    node2 = new csX75::HNode(perry_nodes[0],p);
    node2->change_parameters(0.75,-0.35,-0.51,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

    //right eye ball-> 17
    p = p.draw_trapezium(color_eyeball, 0.2, 0.5, 0.05, origin);
    node2 = new csX75::HNode(perry_nodes[16],p);
    node2->change_parameters(0.0,0.0,-0.15,0.0,0.0,0.0);
    perry_nodes.push_back(node2);

   //nose-> 18
   p = p.draw_trapezium(color_aux, 1.25,1.0,2.0, origin);
   node2 = new csX75::HNode(perry_nodes[0],p);
   node2->change_parameters(0.0,-0.9,-0.51,0.0,0.0,0.0);
   perry_nodes.push_back(node2);

   //accessorize perry-> 19
   p = p.draw_hat( color_hat, 3.2, 1.2, 1.2, origin);
   node2 = new csX75::HNode(perry_nodes[0],p);
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
    node = new csX75::HNode(NULL,p);
    node->change_parameters(6.0,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);
    
    // left thigh -> 1
    p = p.draw_cuboid(skin, 0.4,1.0,0.4, glm::vec4(0,0.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p);
    node->change_parameters(-0.8,-0.25,0.0,10.0,-20.0,0.0);
    phineas_nodes.push_back(node);

    //left leg -> 2
    p = p.draw_cuboid(skin, 0.4,1.6,0.4, glm::vec4(0.0,0.8,0,0));
    node = new csX75::HNode(phineas_nodes[1],p);
    node->change_parameters(0.0,-1.0,0.0,-90.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left foot -> 3
    p = p.draw_cuboid(glm::vec4(0.0, 0.0, 1.0, 1.0), 0.6,0.4,0.8, glm::vec4(0,0.2,0,0));
    node = new csX75::HNode(phineas_nodes[2],p);
    node->change_parameters(0.0,-1.6,-0.2,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right thigh -> 4
    p = p.draw_cuboid(skin, 0.4,1.0,0.4, glm::vec4(0,0.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p);
    node->change_parameters(0.8,-0.25,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right leg -> 5
    p = p.draw_cuboid(skin, 0.4,1.6,0.4, glm::vec4(0.0,0.8,0,0));
    node = new csX75::HNode(phineas_nodes[4],p);
    node->change_parameters(0.0,-1.0,0.0,-40.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right foot -> 6
    p = p.draw_cuboid(glm::vec4(0.0, 0.0, 1.0, 1.0), 0.6,0.4,0.8, glm::vec4(0,0.2,0,0));
    node = new csX75::HNode(phineas_nodes[5],p);
    node->change_parameters(0.0,-1.6,-0.2,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //torso -> 7
    p = p.draw_frustrum(glm::vec4(1.0, 0.4, 0.0, 1.0), 0.5,2.5,3, glm::vec4(0,-1.5,0,0));
    node = new csX75::HNode(phineas_nodes[0],p);
    node->change_parameters(0.0,0.25,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left upper arm-> 8
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p);
    node->change_parameters(-0.25,3.0,0.0,-60.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //left lower arm-> 9
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[8],p);
    node->change_parameters(-1.6,0.0,0.0,0.0,50.0,0.0);
    phineas_nodes.push_back(node);

    //left hand-> 10
    p = p.draw_cuboid(skin, 1.0,0.6,0.4, glm::vec4(0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[9],p);
    node->change_parameters(-1.6,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //right upper arm-> 11
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(-0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[7],p);
    node->change_parameters(0.25,3.0,0.0,50.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right lower arm-> 12
    p = p.draw_cuboid(skin, 1.6,0.4,0.4, glm::vec4(-0.8,0,0,0));
    node = new csX75::HNode(phineas_nodes[11],p);
    node->change_parameters(1.6,0.0,0.0,0.0,0.0,-30.0);
    phineas_nodes.push_back(node);

    //right hand-> 13
    p = p.draw_cuboid(skin, 1.0,0.6,0.4, glm::vec4(-0.5,0,0,0));
    node = new csX75::HNode(phineas_nodes[12],p);
    node->change_parameters(1.6,0.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //neck-> 14
    p = p.draw_cuboid(skin, 0.4,0.4,0.4, glm::vec4(0,-0.2,0,0));
    node = new csX75::HNode(phineas_nodes[7],p);
    node->change_parameters(0.0,3.0,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //head-> 15
    p = p.draw_face(skin, 3.0, glm::vec4(0,-3,0,0));
    node = new csX75::HNode(phineas_nodes[14],p);
    node->change_parameters(0.0,0.4,0.0,0.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses mid rim -> 16
    p = p.draw_cuboid(yellow, 0.6, 0.2, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(2.0,4.0,0.0,0.0,90.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left glass -> 17
    p = p.draw_cuboid(blue, 1.0, 1.0, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[16],p); 
    node->change_parameters(-0.8,-0.4,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right glass -> 18
    p = p.draw_cuboid(blue, 1.0, 1.0, 0.2, origin);
    node = new csX75::HNode(phineas_nodes[16],p); 
    node->change_parameters(0.8,-0.4,0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses left rim -> 19
    p = p.draw_cuboid(yellow, 2.0, 0.2, 0.2, glm::vec4(-1.0,0,0,0));
    node = new csX75::HNode(phineas_nodes[17],p); 
    node->change_parameters(-0.5,0.4,0,-30.0,60.0,0.0);
    phineas_nodes.push_back(node);

    //sunglasses right rim -> 20
    p = p.draw_cuboid(yellow, 2.0, 0.2, 0.2, glm::vec4(1.0,0,0,0));
    node = new csX75::HNode(phineas_nodes[18],p); 
    node->change_parameters(0.5,0.4,0,-30.0,-60.0,0.0);
    phineas_nodes.push_back(node);

    //hair 1 -> 21
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(-1.4,4.4,0.0,0.0,0.0,0.0);
    phineas_nodes.push_back(node);

    //hair 2 -> 22
    p = p.draw_prism(red, 0.9, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(-1.4,4.4,0.0,30.0,30.0,30.0);
    phineas_nodes.push_back(node);

    //hair 3 -> 23
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(-1.4,4.4,0.0,0.0,-30.0,60.0);
    phineas_nodes.push_back(node);

     //hair 4 -> 24
    p = p.draw_prism(red, 0.9, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(-1.4,4.4,0.0,-30.0,-30.0,-30.0);
    phineas_nodes.push_back(node);

    //hair 5 -> 25
    p = p.draw_prism(red, 0.6, 1.5, origin);
    node = new csX75::HNode(phineas_nodes[15],p); 
    node->change_parameters(-1.4,4.4,0.0,0.0,30.0,-60.0);
    phineas_nodes.push_back(node);
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));
// 
  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  csX75::primitive p;
  p = p.draw_cuboid(glm::vec4(0.0, 0.0, 0.0, 0.0), 100.0,100.0,100.0, origin);
  node3 = new csX75::HNode(NULL,p);
  node3->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  scene_nodes.push_back(node3);
  
  
  phineas();
  box();
  perry();

  root_node = curr_node = scene_nodes[0];  
}

void renderNode(csX75::HNode* curr, float x)
{
    projection_matrix = glm::ortho(-14.0, 14.0, -14.0, 14.0, 20.0, -40.0);
   
    matrixStack.clear();
    curr_node = curr;

    c_rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-(c_xpos-x), -c_ypos, -c_zpos));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));
    c_rotation_matrix = glm::translate(c_rotation_matrix, glm::vec3((c_xpos-x), c_ypos, c_zpos));


    //c_rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(c_xpos, 0.0, 0.0));
    glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
    glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
    //Creating the lookat matrix
    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

    view_matrix = projection_matrix*c_rotation_matrix;

    matrixStack.push_back(view_matrix);

    curr_node->render_tree();
}

void renderGL(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     matrixStack.clear();
    if(mode)
    {
	    renderNode(box_nodes[0], -6.0);
	    renderNode(phineas_nodes[0], 6.0);
	    renderNode(perry_nodes[0], 0.0);
    }
    else
    {
	    projection_matrix = glm::ortho(-14.0, 14.0, -14.0, 14.0, 20.0, -40.0);
 
	    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
	    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
	    c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

	    //c_rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(c_xpos, 0.0, 0.0));
	    glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
	    glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
	    //Creating the lookat matrix
	    lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

	    view_matrix = projection_matrix*lookat_matrix;

	    matrixStack.push_back(view_matrix);

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
