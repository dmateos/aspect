client_objects = \
	build/main.o \
	build/gl_program.o \
	build/camera.o \
	build/mesh.o \
	build/model.o \
	build/entity.o \
	build/util.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: aspect

#Client
aspect: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

build/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

build/gl_program.o: src/gl_program.cpp
	$(CXX) -c -o $@ src/gl_program.cpp

build/camera.o: src/camera.cpp
	$(CXX) -c -o $@ src/camera.cpp

build/mesh.o: src/mesh.cpp
	$(CXX) -c -o $@ src/mesh.cpp

build/model.o: src/model.cpp
	$(CXX) -c -o $@ src/model.cpp

build/entity.o: src/entity.cpp
	$(CXX) -c -o $@ src/entity.cpp

build/util.o: src/util.cpp
	$(CXX) -c -o $@ src/util.cpp

clean:
	rm -rf build/*.o aspect
