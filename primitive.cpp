#include "primitive.hpp"

namespace csX75
{
	void primitive::quad(glm::vec4 positions[], glm::vec4 clr, int a, int b, int c, int d)
	{
		glm::vec4 normals[6] = {
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[c])-glm::vec3(positions[b]), glm::vec3(positions[a])-glm::vec3(positions[b]))),1.0),
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[c])-glm::vec3(positions[b]), glm::vec3(positions[a])-glm::vec3(positions[b]))),1.0),
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[c])-glm::vec3(positions[b]), glm::vec3(positions[a])-glm::vec3(positions[b]))),1.0),
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[a])-glm::vec3(positions[d]), glm::vec3(positions[c])-glm::vec3(positions[a]))),1.0),
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[a])-glm::vec3(positions[d]), glm::vec3(positions[c])-glm::vec3(positions[a]))),1.0),
			glm::vec4(glm::normalize(glm::cross(glm::vec3(positions[a])-glm::vec3(positions[d]), glm::vec3(positions[c])-glm::vec3(positions[a]))),1.0)
		};
		for(int i=0;i<6;i++)
			if(normals[i][1] < 0)
				normals[i] = -normals[i];

		//std::cout<<normals[0][0]<<" "<<normals[0][1]<<" "<<normals[0][2]<<std::endl;
		color.push_back(clr); points.push_back(positions[a]); normal.push_back(normals[0]); 
		color.push_back(clr); points.push_back(positions[b]); normal.push_back(normals[1]);
		color.push_back(clr); points.push_back(positions[c]); normal.push_back(normals[2]); 
		color.push_back(clr); points.push_back(positions[a]); normal.push_back(normals[3]); 
		color.push_back(clr); points.push_back(positions[c]); normal.push_back(normals[4]); 
		color.push_back(clr); points.push_back(positions[d]); normal.push_back(normals[5]); 
		num_vertices += 6;
	}

	primitive primitive::draw_cuboid(glm::vec4 clr, double x, double y, double z, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		normal.clear();
		origin = o;
		glm::vec4 positions[8] = {
			glm::vec4(-x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -y/2, -z/2, 1.0) - o
		};

		glm::vec4 normals[6] = {
			glm::vec4(1.0,0.0,0.0,1.0),
			glm::vec4(0.0,1.0,0.0,1.0),
			glm::vec4(0.0,0.0,1.0,1.0),
			glm::vec4(-1.0,0.0,0.0,1.0),
			glm::vec4(0.0,-1.0,0.0,1.0),
			glm::vec4(0.0,0.0,-1.0,1.0)
		};

		quad(positions, clr, 1, 0, 3, 2);
		quad(positions, clr, 2, 3, 7, 6);
		quad(positions, clr, 3, 0, 4, 7);
		quad(positions, clr, 6, 5, 1, 2);
		quad(positions, clr, 4, 5, 6, 7);
		quad(positions, clr, 5, 4, 0, 1);

    		return *this;
	}

	primitive primitive::draw_frustrum(glm::vec4 clr, double r1, double r2, double h, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[8] = {
			glm::vec4(-r2/2, -h/2,  r2/2, 1.0) - o,
			glm::vec4(-r1/2,  h/2,  r1/2, 1.0) - o,
			glm::vec4( r1/2,  h/2,  r1/2, 1.0) - o,
			glm::vec4( r2/2, -h/2,  r2/2, 1.0) - o,
			glm::vec4(-r2/2, -h/2, -r2/2, 1.0) - o,
			glm::vec4(-r1/2,  h/2, -r1/2, 1.0) - o,
			glm::vec4( r1/2,  h/2, -r1/2, 1.0) - o,
			glm::vec4( r2/2, -h/2, -r2/2, 1.0) - o
		};

		quad(positions, clr, 1, 0, 3, 2 );
		quad(positions, clr, 2, 3, 7, 6 );
		quad(positions, clr, 3, 0, 4, 7 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 4, 5, 6, 7 );
		quad(positions, clr, 5, 4, 0, 1 );
	   	return *this;
	}

	primitive primitive::draw_face(glm::vec4 clr, double a, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[5] = {
			glm::vec4( -a/2, a/2, 0, 1.0) - o,
			glm::vec4( 4*a/3, 0, 0, 1.0) - o,
			glm::vec4( 0, -a, 0, 1.0) - o,
			glm::vec4( a/2, -a/2,  a/3, 1.0) - o,
			glm::vec4( a/2, -a/2, -a/3, 1.0) - o
		};

		quad(positions, clr, 1, 0, 3, 2 );
	    	quad(positions, clr, 2, 3, 0, 4 );
	    	quad(positions, clr, 1, 0, 4, 2 );
    		return *this;
	}

	primitive primitive::draw_prism(glm::vec4 clr, double r, double h, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[4] = {
			glm::vec4( -r/3, 0, r/3, 1.0) - o,
			glm::vec4( r/3, 0, r/3, 1.0) - o,
			glm::vec4( 0, 0, -2*r/3, 1.0) - o,
			glm::vec4( 0, h, 0, 1.0) - o
		};

		quad(positions, clr, 1, 0, 3, 2 );
	    	quad(positions, clr, 1, 3, 2, 0 );
	    	return *this;
	}

	primitive primitive::draw_cuboid_oc(glm::vec4 clr_out, glm::vec4 clr_in, double x, double y, double z, glm::vec4 o)
	{
		num_vertices=0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[18] = {
			glm::vec4(-x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4( 0.0, y/2, z/2, 1.0) - o,
			glm::vec4( 0.0, -y/2, z/2, 1.0) - o,
			glm::vec4( 0.0, -y/2, -z/2, 1.0) - o,
			glm::vec4( 0.0, y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, 0.0, z/2, 1.0) - o,
			glm::vec4( 0.0, 0.0, z/2, 1.0) - o,
			glm::vec4( x/2, 0.0, -z/2, 1.0) - o,
			glm::vec4( 0.0, 0.0, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/4,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/4,  z/2, 1.0) - o,
		};
	
		quad( positions, clr_out, 16, 0, 3, 17);
		quad( positions, clr_out, 2, 3, 7, 6);
		quad( positions, clr_out, 3, 0, 4, 7);
		quad( positions, clr_out, 4, 5, 6, 7);
		quad( positions, clr_out, 5, 4, 0, 1);
		quad( positions, clr_in, 11, 10, 9, 8);
		quad( positions, clr_in, 15, 14, 12, 13);
		return *this;
	}

	primitive primitive::draw_plane_ex(glm::vec4 clr, double x, double y, double z, glm::vec4 o)
	{
		num_vertices=0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[6] = {
			glm::vec4(-x/2,  0,  z/2, 1.0) - o,
			glm::vec4( x/2,  0,  z/2, 1.0) - o,
			glm::vec4(-x/2,  0, -z/2, 1.0) - o,
			glm::vec4( x/2,  0, -z/2, 1.0) - o,
			glm::vec4(-x/2,  -y/4,  z/2, 1.0) - o,
			glm::vec4( x/2,  -y/4,  z/2, 1.0) - o,
		};
	
		quad( positions, clr, 3, 2, 0, 1);
		quad( positions, clr, 0, 4, 5, 1);
		return *this;
	}
	
	primitive primitive::draw_trapezoid_cuboid(glm::vec4 clr, double x, double y, double z, double h, glm::vec4 o)
	{
		num_vertices=0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[12] = {
			glm::vec4(-x/2, -3*y,  z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2, -3*y,  z/2, 1.0) - o,
			glm::vec4(-x/2, -3*y, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -3*y, -z/2, 1.0) - o,
			glm::vec4(-x/4, (y/2)+h, z/2, 1.0) - o,
			glm::vec4( x/4, (y/2)+h, z/2, 1.0) - o,
			glm::vec4( x/4, (y/2)+h, -z/2, 1.0) - o,
			glm::vec4(-x/4, (y/2)+h, -z/2, 1.0) - o
		};
    		
		quad(positions, clr, 1, 0, 3, 2 );
		quad(positions, clr, 2, 3, 7, 6 );
		quad(positions, clr, 3, 0, 4, 7 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 4, 5, 6, 7 );
		quad(positions, clr, 5, 4, 0, 1 );

		quad(positions, clr, 1, 8, 9, 2 );
		quad(positions, clr, 2, 9, 10, 6 );
		quad(positions, clr, 9, 8, 11, 10 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 11, 5, 6, 10 );
		quad(positions, clr, 5, 11, 8, 1 );
	
    		return *this;
	}

	primitive primitive::draw_trapezium(glm::vec4 clr, double x, double y, double z, glm::vec4 o)
	{
		num_vertices=0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[8] = {
			glm::vec4(-x/4, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/4,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/4,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/4, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -y/2, -z/2, 1.0) - o
		};
    		
		quad(positions, clr, 1, 0, 3, 2 );
		quad(positions, clr, 2, 3, 7, 6 );
		quad(positions, clr, 3, 0, 4, 7 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 4, 5, 6, 7 );
		quad(positions, clr, 5, 4, 0, 1 );
	
    		return *this;
	}

	primitive primitive::draw_hat(glm::vec4 clr, double x, double y, double z, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[] = {
			glm::vec4(-x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-(3*x)/4, -y/2,  z, 1.0) - o,
			glm::vec4(-(3*x)/4, -y/2, -z, 1.0) - o,
			glm::vec4( (3*x)/4, -y/2, -z, 1.0) - o,
			glm::vec4( (3*x)/4, -y/2,  z, 1.0) - o,
			glm::vec4(-(3*x)/4, -y/2,  z/2, 1.0) - o,
			glm::vec4(-(3*x)/4, -y/2, -z/2, 1.0) - o,
			glm::vec4( (3*x)/4, -y/2, -z/2, 1.0) - o,
			glm::vec4( (3*x)/4, -y/2,  z/2, 1.0) - o,
		};

		quad(positions, clr, 1, 0, 3, 2 );
		quad(positions, clr, 2, 3, 7, 6 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 4, 5, 6, 7 );
		quad(positions, clr, 5, 4, 0, 1 );

		quad(positions, clr, 10, 9, 13, 14);
		quad(positions, clr, 4, 13, 12, 0);
		quad(positions, clr, 15, 12, 8, 11);
		quad(positions, clr, 14, 7, 3, 15);
    		return *this;
	}

	primitive primitive::draw_window(glm::vec4 clr, double x, double y, double z, glm::vec4 o)
	{
		num_vertices = 0;
		points.clear();
		color.clear();
		origin = o;
		glm::vec4 positions[16] = {
			glm::vec4(-x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/2, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/2, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/2, -y/2, -z/2, 1.0) - o,

			glm::vec4(-x/4, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/4,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/4,  y/2,  z/2, 1.0) - o,
			glm::vec4( x/4, -y/2,  z/2, 1.0) - o,
			glm::vec4(-x/4, -y/2, -z/2, 1.0) - o,
			glm::vec4(-x/4,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/4,  y/2, -z/2, 1.0) - o,
			glm::vec4( x/4, -y/2, -z/2, 1.0) - o
		};

		quad(positions, clr, 13, 12, 8, 9 );
		quad(positions, clr, 2, 3, 7, 6 );
		quad(positions, clr, 3, 0, 4, 7 );
		quad(positions, clr, 6, 5, 1, 2 );
		quad(positions, clr, 14, 15, 11, 10 );
		quad(positions, clr, 5, 4, 0, 1 );

    		return *this;
	}
}
