#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <fstream>
#include <iostream>

extern GLfloat xrot,yrot,zrot,xpos,ypos,zpos,c_xrot,c_yrot,c_zrot,c_xpos,c_ypos,c_zpos;
extern bool enable_perspective;
extern int light;
extern std::string filename;
extern GLuint tex_light;
extern csX75::HNode* curr_node, *node, *root_node;
extern std::vector<glm::vec3> control_points;
extern std::vector<csX75::HNode*> phineas_nodes, box_nodes, perry_nodes, scene_nodes, room_nodes, table_nodes, control_nodes;
extern glm::mat4 projection_matrix, lookat_matrix;
extern void read_keyframes();
extern void initPath();
int ch =0;
bool op=false;
extern bool mode, x, capture;
extern bool play_back, play_camera, render_path;
extern int key_frame;
int f = 0;

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

		else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		{
			enable_perspective = !enable_perspective; 
		}
    
    	else if (key == GLFW_KEY_F && action == GLFW_PRESS)
    	{
    		if(!control_points.empty()){
    			glm::vec3 v = control_points.back();
    			std::cout << "Deleted Point: " << v.x << ", " << v.y << ", " << v.z << std::endl;
    			control_points.pop_back();
    			control_nodes.pop_back();
    		}
    	}
    
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
			// restrict the room door's rotation to y-direction only
			else if( curr_node == room_nodes[7] && p[4] > -90)
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
			// restrict the room door's rotation to y-direction only
			else if( curr_node == room_nodes[7] && p[4] < 0)
				curr_node->inc_ry();
	    }
    
		else if (key == GLFW_KEY_UP && action == GLFW_PRESS && !mode)
		{
			GLfloat *p = curr_node->get_parameters(); //p={tx,ty,tz,rx,ry,rz}
			// restrict the box lid's rotation to x-direction only
			if(curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
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
			if(curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
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
			if(curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
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
			if(curr_node == perry_nodes[0] || curr_node == phineas_nodes[0])
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

				curr_node = scene_nodes[0];
				op=false;
				ch=0;
			}
			else
				std::cout<<"Global rotation mode"<<std::endl;
		}
    
	    else if (key == GLFW_KEY_G && action == GLFW_PRESS)
	    {
			if(light==0)
			{
				std::cout<<"Light 1 On"<<std::endl;
				light=1;
			}
			else if(light==1)
			{
				std::cout<<"Light 2 On"<<std::endl;
				light=2;
			}
			else if(light==2)
			{
				std::cout<<"Lights 1 and 2 On"<<std::endl;
				light=3;
			}
			else
			{
				std::cout<<"Lights 1 and 2 Off"<<std::endl;
				light=0;
			}
	    }

	    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	    {
			std::ofstream myfile;
			if(f==0)
			{
				myfile.open (filename, std::ios::trunc | std::ios::out);
				f=1;
				key_frame = 0;
			}
			else
			{
				myfile.open (filename, std::ios::out | std::ios::app);
			}

			std::cout << "Recording current configuration as keyframe "<<std::endl;
			key_frame ++;
  	
			//Get the current configuration and save it
			myfile<<light<<"\t";
			GLfloat *p = box_nodes[0]->get_parameters();
			myfile<<p[0]<<"\t"<<p[1]<<"\t"<<p[2]<<"\t"<<p[4]<<"\t";
			p = box_nodes[1]->get_parameters();
			myfile<<p[3]<<"\t";
			
			p = perry_nodes[0]->get_parameters();
			myfile<<p[0]<<"\t"<<p[1]<<"\t"<<p[2]<<"\t"<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = perry_nodes[1]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = perry_nodes[4]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = perry_nodes[7]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = perry_nodes[10]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = perry_nodes[13]->get_parameters();
			myfile<<p[4]<<"\t"<<p[5]<<"\t";
			
			p = phineas_nodes[0]->get_parameters();
			myfile<<p[0]<<"\t"<<p[1]<<"\t"<<p[2]<<"\t"<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[1]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[4]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[3]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[6]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[8]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[11]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[9]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[12]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[10]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[13]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[7]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[14]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\t";
			p = phineas_nodes[15]->get_parameters();
			myfile<<p[3]<<"\t"<<p[4]<<"\t"<<p[5]<<"\n";


			myfile.close();	      
	    }

	    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	    {
			x = false;
	    	std::ifstream myfile(filename);
	    	if(!myfile){
	    		std::cout << filename << " is missing" << std::endl;
	    	}
	    	else{
	    		std::cout<<"Play the animation"<<std::endl;
				play_back = true;
				read_keyframes();
				glfwSetTime(0.0);
	    	}
	    }

	    else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	    {
			x = false;
			std::cout<<"Play the camera animation"<<std::endl;
	    	if(control_points.size()==1){
	    		c_xpos = control_points[0].x;
	    		c_ypos = control_points[0].y;
	    		c_zpos = control_points[0].z;
	    	}
	    	else if(control_points.size()>1){
	    		play_camera = true;
	    		glfwSetTime(0.0);
	    	}
	    }
	    else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	    {
	    	render_path = !render_path;
	    	initPath();
	    }

	    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		xrot+=10;
				 glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];	
	    	}
	    	else{
	    		c_xpos++;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
	    }
	    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		xrot-=10;
				 glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];
	    	}
	    	else{
	    		c_xpos--;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
	    }
	    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		yrot+=10;
				 glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];
	    	}
	    	else{
	    		c_ypos++;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
	    }
	    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		yrot-=10;
				 glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];	
	    	}
	    	else{
	    		c_ypos--;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
	    }
	    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		zrot+=10;
				glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];	
	    	}
	    	else{
	    		c_zpos++;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
	    }
	    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
	    {
	    	if(mode){
	    		zrot-=10;
				 glm::vec4 c = curr_node->get_centroid();
				 xpos = c[0];
				 ypos = c[1];
				 zpos = c[2];	
	    	}
	    	else{
	    		c_zpos--;
	    		std::cout << "Camera co-ordinates: " << c_xpos << " " << c_ypos << " " << c_zpos << std::endl;
	    	}
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
	    else if (key == GLFW_KEY_V && action == GLFW_PRESS && (!op || (op && ch!=4)) && !mode)
	    {	//select room's door
			curr_node = room_nodes[7];
			std::cout<<"Room Door selected"<<std::endl;
			ch=4;
			op=true;
	    }

	    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	    {
		capture = !capture;
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

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		double xpos, ypos;
		double x=c_xpos, y=c_ypos, z=c_zpos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if(button==GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			// std::cout << xpos << " " << ypos << std::endl;
			// x += (768 - xpos)/24 - 16;
			// y += (768 - ypos)/24 - 13;
			// z += 5;
			xpos = c_xpos -1+xpos/(2*768);
			ypos = c_ypos +1-ypos/(2*768);

			glm::vec3 point;
			point = glm::unProject(glm::vec3(xpos, ypos, 0), lookat_matrix, projection_matrix, glm::vec4(c_xpos-0.5, c_xpos+0.5, c_ypos-0.5, c_ypos+0.5));
			// std::cout << point.x << " " << point.y << " " << point.z << std::endl;
			// point = glm::unProject(glm::vec3(xpos, ypos, 1), lookat_matrix, projection_matrix, glm::vec4(-0.5, 0.5, -0.5, 0.5));
			// std::cout << point.x << " " << point.y << " " << point.z << std::endl;
			// point.x += c_xpos;
			// point.y += c_ypos;
			std::cout << point.x << " " << point.y << " " << point.z << std::endl;
			
			control_points.push_back(point);
			csX75::primitive p;
		    glm::vec4 red = glm::vec4(1.0, 0.0, 0.0, 1.0);
		    p = p.draw_cuboid(red, 0.1,0.1,0.1, glm::vec4(0));
		    node = new csX75::HNode(NULL,p,tex_light);
		    node->change_parameters(point.x,point.y,point.z,0.0,0.0,0.0);
		    control_nodes.push_back(node);
			// std::cout << "Selected Point: " << x << ", " << y << ", " << z << std::endl;
		}
	}
};  
