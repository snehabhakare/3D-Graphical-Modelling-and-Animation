#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "primitive.hpp"

namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		primitive model;
		GLfloat tx,ty,tz,rx,ry,rz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		glm::vec4 centroid;		
	
		std::vector<HNode*> children;
		HNode* parent;
		void set_centroid(primitive);
		void update_matrices();

	  public:
		HNode (HNode*, primitive);
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, std::size_t, std::size_t);
		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		GLfloat* get_parameters();
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void inc_tx();
		void inc_ty();
		void inc_tz();
		void dec_tx();
		void dec_ty();
		void dec_tz();
		glm::vec4 get_centroid();
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif
