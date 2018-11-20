#include "hierarchy_node.hpp"

#include <iostream>
#include <cstdlib>

extern GLuint vPosition,vColor,vNormal,vTexture,uModelViewMatrix, normalMatrix,viewMatrix, Light, choice;
extern glm::mat4 view_matrix;
extern std::vector<glm::mat4> matrixStack;
extern glm::mat3 normal_matrix;
extern int light;

namespace csX75
{
	HNode::HNode(HNode* a_parent, primitive p_model, GLuint texture){
		textures = texture;
		num_vertices = p_model.num_vertices;
		vertex_buffer_size = sizeof(p_model.points[0]) * p_model.points.size();
		color_buffer_size = sizeof(p_model.color[0]) * p_model.color.size();
		normal_buffer_size = sizeof(p_model.normal[0]) * p_model.normal.size();
		texture_buffer_size = sizeof(p_model.texture[0]) * p_model.texture.size();
		// initialize vao and vbo of the object;
		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, &p_model.points[0] );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, &p_model.color[0] );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, normal_buffer_size, &p_model.normal[0] );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size, texture_buffer_size, &p_model.texture[0] );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));

	  	glEnableVertexAttribArray( vTexture );
	  	glVertexAttribPointer( vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size + normal_buffer_size));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}
		model = p_model;
		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		set_centroid(p_model);
		update_matrices();
	}

	void HNode::set_centroid(primitive p){
		float s_area = 0.0;
		glm::vec4 cen = glm::vec4(0.0,0.0,0.0,1.0);
		glm::vec3 c;

		for(int i=0;i<num_vertices;i++)
		{
			glm::vec3 pnt[3];
			for(int j=0;j<3;j++)
			{
				pnt[j][0]=p.points[j][0];
				pnt[j][1]=p.points[j][1];
				pnt[j][2]=p.points[j][2];
			}

			c[0] =(p.points[i][0] + p.points[i+1][0] + p.points[i+2][0])/3;
			c[1] =(p.points[i][1] + p.points[i+1][1] + p.points[i+2][1])/3;
			c[2] =(p.points[i][2] + p.points[i+1][2] + p.points[i+2][2])/3;
			
			float a = 0.5 * glm::length(glm::cross((pnt[1]-pnt[0]),(pnt[2]-pnt[0])));

			cen[0]+= a*c[0];
			cen[1]+= a*c[1];
			cen[2]+= a*c[2];

			s_area+=a;
		}

		cen[0]/=s_area;
		cen[1]/=s_area;
		cen[2]/=s_area;

		centroid = cen;
	}
	
	glm::vec4 HNode::get_centroid(){
		glm::vec4 c = centroid;

		return c;
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
		
	}

        GLfloat* HNode::get_parameters()
        {
		GLfloat *p = (GLfloat*)malloc(6*sizeof(GLfloat));
		p[0] = tx;
		p[1] = ty;
		p[2] = tz;
		p[3] = rx;
		p[4] = ry;
		p[5] = rz;
		//std::cout<<p[2]<<std::endl;
		return p;
		
	}

	void HNode::render(){
		glm::vec4 c = get_centroid();

		//std::cout<<num_vertices<<std::endl;
  		//std::cout<<c[0]<<" "<<c[1]<<" "<<c[2]<<" "<<c[3]<<std::endl;
		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		glBindTexture(GL_TEXTURE_2D, textures);
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		normal_matrix = glm::mat3(glm::transpose (glm::inverse(glm::mat4(glm::inverse(view_matrix) * *ms_mult))));
		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
		glUniform1i(Light,light);
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, model.points.size());

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx+=10;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry+=10;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz+=10;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx-=10;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry-=10;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz-=10;
		update_matrices();
	}

	void HNode::inc_tx(){
		tx++;
		update_matrices();
	}


	void HNode::inc_ty(){
		ty++;
		update_matrices();
	}

	void HNode::inc_tz(){
		tz++;
		update_matrices();
	}

	void HNode::dec_tx(){
		tx--;
		update_matrices();
	}

	void HNode::dec_ty(){
		ty--;
		update_matrices();
	}

	void HNode::dec_tz(){
		tz--;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}
