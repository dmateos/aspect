objects = \
	build/main.o \
	build/gl_program.o \
	build/gl_window.o \
	build/camera.o \
	build/mesh.o \
	build/model.o \
	build/util.o \
	build/texture.o \
	build/cube.o \

libs = -lglfw3 -lglew -lassimp -lil -lilu -lilut -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
c_args = -std=c++11 -stdlib=libc++ -Wall -Wextra -Wwrite-strings -Werror

all: aspect

#Client
aspect: $(objects)
	$(CXX) $(libs) -o $@ $(objects)

build/main.o: src/main.cpp
	$(CXX) ${c_args} -c -o $@ src/main.cpp

build/gl_program.o: src/gl_program.cpp
	$(CXX) ${c_args} -c -o $@ src/gl_program.cpp

build/gl_window.o: src/gl_window.cpp
	$(CXX) ${c_args} -c -o $@ src/gl_window.cpp

build/camera.o: src/camera.cpp
	$(CXX) ${c_args} -c -o $@ src/camera.cpp

build/mesh.o: src/mesh.cpp
	$(CXX) ${c_args} -c -o $@ src/mesh.cpp

build/model.o: src/model.cpp
	$(CXX) ${c_args} -c -o $@ src/model.cpp

build/util.o: src/util.cpp
	$(CXX) ${c_args} -c -o $@ src/util.cpp

build/texture.o: src/texture.cpp
	$(CXX) ${c_args} -c -o $@ src/texture.cpp

build/cube.o: src/cube.cpp
	$(CXX) ${c_args} -c -o $@ src/cube.cpp

clean:
	rm -rf build/*.o aspect
