#version 330

in vec2 t;
in vec4 color;
in vec3 normal;
in vec4 eye;

out vec4 frag_color;

uniform mat4 viewMatrix;
uniform int Light;
uniform sampler2D textures;

void main () 
{
  vec4 tex = texture2D(textures, t);

  // Defining Materials

  //Material 1
  vec4 diffuse1 = vec4(1.0, 1.0, 1.0, 1.0); 
  vec4 ambient1 = vec4(0.3, 0.3, 0.3, 1.0);
  vec4 specular1 = vec4(0.1, 0.1, 0.1, 1.0);
  float shininess1 = 1.0;

  //Material 2
  vec4 diffuse2 = vec4(0.1, 0.1, 0.1, 1.0); 
  vec4 ambient2 = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular2 = vec4(0.5, 0.5, 0.5, 1.0);
  float shininess2 = 0.2;

  //Material 3
  vec4 diffuse3 = vec4(0.3, 0.1, 0.6, 1.0); 
  vec4 ambient3 = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular3 = vec4(0.1, 0.4, 0.1, 1.0);
  float shininess3 = 0.9;

  //Material 4
  vec4 diffuse4 = vec4(0.5, 0.5, 0.5, 1.0); 
  vec4 ambient4 = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular4 = vec4(0.1, 0.1, 0.1, 1.0);
  float shininess4 = 0.6;

  //Initialize specular component for light sources 1 and 2
  vec4 spec1 = vec4(0.0), spec2 = vec4(0.0);
 
  // Defining Lamp: Light 1
  vec4 lightPos1 = vec4(20.0,3.0,-6.0, 1.0);
  vec3 lightDir1 = vec3(viewMatrix * lightPos1);  // Transforms with camera
  lightDir1 = normalize( vec3(lightDir1));  
  
  // Defining Wall Fixature: Light 2
  vec4 lightPos2 = vec4(-18.0,20.0, 0.0, 1.0);
  vec3 lightDir2 = vec3(viewMatrix * lightPos2);  // Transforms with camera
  lightDir2 = normalize( vec3(lightDir2)); 

  //Diffuse component for light sources 1 and 2
  vec3 n = normalize(vec3(normal));	
     
  float dotProduct = dot(n, lightDir1);
  float intensity1 =  max( dotProduct, 0.0);

  dotProduct = dot(n, lightDir2);
  float intensity2 =  max( dotProduct, 0.0);

  vec3 e = normalize(vec3(eye));
  // Compute specular component only if light 1 falls on vertex
  if(intensity1 > 0.0)
  {
	vec3 h = normalize(lightDir1 + e );
   	float intSpec = max(dot(h,n), 0.0);	
        spec1 = specular1 * pow(intSpec, shininess1);
  }  

  // Compute specular component only if light 2 falls on vertex
  if(intensity2 > 0.0)
  {
	vec3 h = normalize(lightDir2 + e );
   	float intSpec = max(dot(h,n), 0.0);	
        spec2 = specular1 * pow(intSpec, shininess1);
  }

  vec4 COLOR;
 

  {
	  if(Light==0)
	  {	
	  	COLOR = ambient1*tex*color; // All
	  }
	  else if(Light==1)
	  {	
	  	COLOR = ((intensity1 * diffuse1  + spec1 + ambient1)*tex*color); // All
	  }
	  else if(Light==2)
	  {
		COLOR = ((intensity2 * diffuse1  + spec2 + ambient1)*tex*color); // All
	  }
	  else
	  {
		COLOR = ((intensity1 * diffuse1  + spec1 + intensity2 * diffuse1  + spec2 + ambient1)*tex*color); // All
	  }
  }

  frag_color = COLOR;
}
