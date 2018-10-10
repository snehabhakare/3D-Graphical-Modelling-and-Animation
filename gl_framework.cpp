#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot, c_xpos, c_ypos, c_zpos, c_up_x, c_up_y, c_up_z;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3,*curr_node;
extern std::vector<csX75::HNode*> phineas_nodes, box_nodes, perry_nodes, scene_nodes;
int ch =0;
bool op=false;
extern bool mode;

namespace csX75
{
	//! Initialize GL State
	void initGL(void)
	{
		//Set framebuffer clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Set depth buffer furthest depth
		glClearDepth(1.0);
		//Set depth test to less-than
		glDepthFunc(GL_LESS);
		//Enable depth testing
		glEnable(GL_DEPTH_TEST);
	}

	//!GLFW Error Callback
	void error_callback(int error, const char* description)
	{
		std::cerr<<description<<std::endl;
	}

	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		//!Resize the viewport to fit the window size - draw to entire window
		glViewport(0, 0, width, height);
	}
  
	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
    
    
	    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && !mode)
	    {
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if( curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_ry();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[4] > -20)   //leg movement
				curr_node->dec_ry();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[4] > -30)   //hand movement
				curr_node->dec_ry();
			else if( curr_node == perry_nodes[13] && p[4] > -30)   //tail movement
				curr_node->dec_ry();
			// restrict the phineas's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[4] > -20) ||	//thigh movement
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[4] > -30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[4] > -60) ||	//upper arm movement
					 ((curr_node == phineas_nodes[9] || curr_node == phineas_nodes[12]) && p[4] > 0) ||	//lower arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[4] > -30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14]) && p[4] > -30) ||	//torso, neck movement 
					 ((curr_node == phineas_nodes[15]) && p[4] > -180))	//head movement
				curr_node->dec_ry();
		}
	    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && !mode)
	    {
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if( curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_ry();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[4] < 20)   //leg movement
				curr_node->inc_ry();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[4] < 30)   //hand movement
			  	curr_node->inc_ry();
			else if( curr_node == perry_nodes[13] && p[4] < 30)   //tail movement
  				curr_node->inc_ry();
  			// restrict the phineas's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[4] < 20) ||	//thigh movement
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[4] < 30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[4] < 30) ||	//upper arm movement
					 ((curr_node == phineas_nodes[9] || curr_node == phineas_nodes[12]) && p[4] < 90) ||	//lower arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[4] < 30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14]) && p[4] < 30) ||	//torso, neck movement 
					 ((curr_node == phineas_nodes[15]) && p[4] < 0))	//head movement
				curr_node->inc_ry();
	    }
    
		else if (key == GLFW_KEY_UP && action == GLFW_PRESS && !mode)
		{
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_rx();
			// restrict the box lid's rotation by maximum possible angle of rotation
			else if( curr_node == box_nodes[1] && p[3] >= - 225)	
				curr_node->dec_rx();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[3] >= -90)   //leg movement
				curr_node->dec_rx();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[3] >= -20)   //hand movement
				curr_node->dec_rx();
			// restrict the phineas's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[3] > -45) ||	//thigh movement
					 ((curr_node == phineas_nodes[2] || curr_node == phineas_nodes[5]) && p[3] > -90) ||	//leg movement 
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[3] > -30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[3] > -60) ||	//upper arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[3] > -30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14] || curr_node == phineas_nodes[15]) && p[3] > -30))	//torso, neck, head movement
				curr_node->dec_rx();
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && !mode)
		{
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_rx();
			// restrict the box lid's rotation by maximum possible angle of rotation
			else if( curr_node == box_nodes[1] && p[3] < 0)	
				curr_node->inc_rx();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[3] < 45)   //leg movement
				curr_node->inc_rx();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[3] < 10)   //hand movement
				curr_node->inc_rx();
			// restrict the phineas's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[3] < 90) ||	//thigh movement
					 ((curr_node == phineas_nodes[2] || curr_node == phineas_nodes[5]) && p[3] < 0) ||	//leg movement 
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[3] < 30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[3] < 60) ||	//upper arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[3] < 30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14] || curr_node == phineas_nodes[15]) && p[3] < 30))	//torso, neck, head movement
				curr_node->inc_rx();
		}
    
		else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && !mode)
		{
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_rz();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[5] >= -20)   //leg movement
				curr_node->dec_rz();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[5] >= -80)   //hand movement
				curr_node->dec_rz();
			else if( curr_node == perry_nodes[13] && p[5] > -30)   //tail movement
				curr_node->dec_rz();
			// restrict the phineas's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[5] > -20) ||	//thigh movement
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[5] > -30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[5] > -80) ||	//upper arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[5] > -30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14] || curr_node == phineas_nodes[15]) && p[5] > -30))	//torso, neck, head movement
				curr_node->dec_rz();
		}
		else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && !mode)
		{
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_rz();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( (curr_node == perry_nodes[1] || curr_node == perry_nodes[4]) && p[5] < 20)   //leg movement
				curr_node->inc_rz();
			else if( (curr_node == perry_nodes[7] || curr_node == perry_nodes[10]) && p[5] < 80)   //hand movement
				curr_node->inc_rz();
			else if( curr_node == perry_nodes[13] && p[5] < 30)   //tail movement
				curr_node->inc_rz();
			// restrict the perry's rotation by maximum possible angle of rotation
			else if( ((curr_node == phineas_nodes[1] || curr_node == phineas_nodes[4]) && p[5] < 20) ||	//thigh movement
					 ((curr_node == phineas_nodes[3] || curr_node == phineas_nodes[6]) && p[5] < 30) ||	//foot movement 
					 ((curr_node == phineas_nodes[8] || curr_node == phineas_nodes[11]) && p[5] < 80) ||	//upper arm movement
					 ((curr_node == phineas_nodes[10] || curr_node == phineas_nodes[13]) && p[5] < 30) ||	//hand movement 
					 ((curr_node == phineas_nodes[7] || curr_node == phineas_nodes[14] || curr_node == phineas_nodes[15]) && p[5] < 30))	//torso, neck, head movement
				curr_node->inc_rz();
		}

		// translate the entire model
		else if (key == GLFW_KEY_J && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_ty();
		}
		else if (key == GLFW_KEY_U && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_ty();
		}
		else if (key == GLFW_KEY_H && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_tx();
		}
		else if (key == GLFW_KEY_K && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_tx();
		}
		else if (key == GLFW_KEY_O && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->dec_tz();
		}
		else if (key == GLFW_KEY_L && action == GLFW_PRESS && !mode)
		{
			if(curr_node == box_nodes[0] || curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
				curr_node->inc_tz();
		}
		
		else if (key == GLFW_KEY_I && action == GLFW_PRESS)
		{
			mode=!mode;
			if(mode == false)
			{
				std::cout<<"Individual rotation mode"<<std::endl;
				c_xpos = 0.0;
				c_ypos = 0.0;
				c_zpos = 10.0;
				c_up_x = 0.0;
				c_up_y = 1.0;
				c_up_z = 0.0;
				c_xrot = 0.0;
				c_yrot = 0.0;
				c_zrot = 0.0;
				curr_node = scene_nodes[0];
				op=false;
				ch=0;
			}
			else
				std::cout<<"Global rotation mode"<<std::endl;
		}
    
    else if (key == GLFW_KEY_A && action == GLFW_PRESS && mode)
    {
	c_xrot+=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS && mode)
    {
	c_xrot-=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS && mode)
    {
	c_yrot+=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS && mode)
    {
	c_yrot-=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS && mode)
    {
	c_zrot+=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }
    else if (key == GLFW_KEY_X && action == GLFW_PRESS && mode)
    {
	c_zrot-=10;
	glm::vec4 c = curr_node->get_centroid();
	c_xpos = c[0];
	c_ypos = c[1];
	c_zpos = c[2];
    }

    else if (key == GLFW_KEY_B && action == GLFW_PRESS && (!op || (op && ch!=1)) && !mode)
    {	//select box
		curr_node = box_nodes[0];
		std::cout<<"Box selected"<<std::endl;
		ch=1;
		op=true;
    }
    else if (key == GLFW_KEY_N && action == GLFW_PRESS && (!op || (op && ch!=2)) && !mode)
    {	//select phineas
		curr_node = phineas_nodes[0];
		std::cout<<"Phineas selected"<<std::endl;
		ch=2;
		op=true;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS && (!op || (op && ch!=3)) && !mode)
    {	//select perry
		curr_node = perry_nodes[0];
		std::cout<<"Perry selected"<<std::endl;
		ch=3;
		op=true;
    }

    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && ch==1)
		//select boxes' body
		curr_node = box_nodes[0];
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && ch==2)
		//select phineas's hip
		curr_node = phineas_nodes[0];
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && ch==3)
		//select perry's body
		curr_node = perry_nodes[0];

    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && ch==1)
		//select boxes' lid
		curr_node = box_nodes[1];
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && ch==2)
		//select phineas's left thigh
		curr_node = phineas_nodes[1];
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && ch==3)
		//select perry's left thigh
		curr_node = perry_nodes[1];

    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && ch==2)
		//select phineas's left leg
		curr_node = phineas_nodes[2];
   	else if (key == GLFW_KEY_2 && action == GLFW_PRESS && ch==3)
		//select perry's right thigh
		curr_node = perry_nodes[4];

    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && ch==2)
		//select phineas's left foot
		curr_node = phineas_nodes[3];
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && ch==3)
		//select perry's left upper arm
		curr_node = perry_nodes[7];

    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && ch==2)
		//select phineas's right thigh
		curr_node = phineas_nodes[4];
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && ch==3)
		//select perry's right upper arm
		curr_node = perry_nodes[10];

    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && ch==2)
		//select phineas's right leg
		curr_node = phineas_nodes[5];
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && ch==3)
		//select perry's tail
		curr_node = perry_nodes[13];

    else if (key == GLFW_KEY_6 && action == GLFW_PRESS && ch==2)
		//select phineas's right foot
		curr_node = phineas_nodes[6];

    else if (key == GLFW_KEY_7 && action == GLFW_PRESS && ch==2)
		//select phineas's torso
		curr_node = phineas_nodes[7];

    else if (key == GLFW_KEY_8 && action == GLFW_PRESS && ch==2)
		//select phineas's left upper arm
		curr_node = phineas_nodes[8];

    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && ch==2)
		//select phineas's left lower arm
		curr_node = phineas_nodes[9];

    else if (key == GLFW_KEY_Q && action == GLFW_PRESS && ch==3)
		//select phineas's left hand
		curr_node = phineas_nodes[10];

    else if (key == GLFW_KEY_W && action == GLFW_PRESS && ch==2)
		//select phineas's right upper arm
		curr_node = phineas_nodes[11];

    else if (key == GLFW_KEY_E && action == GLFW_PRESS && ch==2)
		//select phineas's right lower arm
		curr_node = phineas_nodes[12];

    else if (key == GLFW_KEY_R && action == GLFW_PRESS && ch==2)
		//select phineas's right hand
		curr_node = phineas_nodes[13];

    else if (key == GLFW_KEY_T && action == GLFW_PRESS && ch==2)
		//select phineas's neck 
		curr_node = phineas_nodes[14];

    else if (key == GLFW_KEY_Y && action == GLFW_PRESS && ch==2)
		//select phineas's head
		curr_node = phineas_nodes[15];
    }
};  
  