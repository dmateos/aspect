client_objects = \
	src/main.o \
	src/gl_program.o \
	src/camera.o \
	src/mesh.o \
	src/model.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: aspect

#Client
aspect: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

src/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

src/gl_program.o: src/gl_program.cpp
	$(CXX) -c -o $@ src/gl_program.cpp

src/camera.o: src/camera.cpp
	$(CXX) -c -o $@ src/camera.cpp

src/mesg.o: src/mesh.cpp
	$(CXX) -c -o $@ src/mesh.cpp

src/model.o: src/model.cpp
	$(CXX) -c -o $@ src/model.cpp

clean:
	rm -rf src/*.o aspect
