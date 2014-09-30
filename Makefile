client_objects = \
	build/main.o \
	build/gl_program.o \
	build/gl_window.o \
	build/camera.o \
	build/mesh.o \
	build/model.o \
	build/util.o \
	build/texture.o \
	build/cube.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: aspect

#Client
aspect: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

build/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

build/gl_program.o: src/gl_program.cpp
	$(CXX) -c -o $@ src/gl_program.cpp

build/gl_window.o: src/gl_window.cpp
	$(CXX) -c -o $@ src/gl_window.cpp

build/camera.o: src/camera.cpp
	$(CXX) -c -o $@ src/camera.cpp

build/mesh.o: src/mesh.cpp
	$(CXX) -c -o $@ src/mesh.cpp

build/model.o: src/model.cpp
	$(CXX) -c -o $@ src/model.cpp

build/util.o: src/util.cpp
	$(CXX) -c -o $@ src/util.cpp

build/texture.o: src/texture.cpp
	$(CXX) -c -o $@ src/texture.cpp

build/cube.o: src/cube.cpp
	$(CXX) -c -o $@ src/cube.cpp

clean:
	rm -rf build/*.o aspect
