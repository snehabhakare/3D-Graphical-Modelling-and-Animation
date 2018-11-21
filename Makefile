CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
GLULIB = -lGLU
LIBS=$(GLULIB) $(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=hierarchical_modelling
SRCS=hierarchical_modelling.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp primitive.cpp
INCLUDES=gl_framework.hpp shader_util.hpp hierarchical_modelling.hpp hierarchy_node.hpp primitive.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
