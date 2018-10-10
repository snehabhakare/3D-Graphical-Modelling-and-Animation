#ifndef _PRIMITIVE_HPP_
#define _PRIMITIVE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"

namespace csX75	 
{
	class primitive 
	{
		public:
		std::vector<glm::vec4> points;
		std::vector<glm::vec4> color;
		glm::vec4 origin;
		int num_vertices;
		
		void quad(glm::vec4*, glm::vec4, int, int, int, int);
		primitive draw_cuboid(glm::vec4, double, double, double, glm::vec4);
		primitive draw_frustrum(glm::vec4, double, double, double, glm::vec4);
		primitive draw_prism(glm::vec4, double, double, glm::vec4);
		primitive draw_face(glm::vec4, double, glm::vec4);
		primitive draw_cuboid_oc(glm::vec4, glm::vec4, double, double, double, glm::vec4);
		primitive draw_plane_ex(glm::vec4, double, double, double, glm::vec4);
		primitive draw_trapezoid_cuboid(glm::vec4, double, double, double, double, glm::vec4);
		primitive draw_trapezium(glm::vec4, double, double, double, glm::vec4);
		primitive draw_hat(glm::vec4, double, double, double, glm::vec4);
	};
};

#endif
