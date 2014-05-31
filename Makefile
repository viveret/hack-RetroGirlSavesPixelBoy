PROGRAM = libRGSPB-ubuntu.so

# Compiler
CXX := g++

# Compiler options during compilation
CXXFLAGS := -c -O0 -g3 -std=c++11 -D_UBUNTU -fPIC -DSE_PHYSICS_3D
NOTIF_FLAGS := -Wall -Wextra -MMD -MP -Wno-comment -rdynamic

# Libraries for linking
LIBS := -ldl -lX11 -lboost_system -lboost_thread -lGL -lGLU -lGLEW -lIL -lILU -lILUT -lfreetype -lassimp -lBulletDynamics -lBulletCollision -lLinearMath -lnoise -llua5.2 -lz -lzip
# Include all other makefiles
SRC=$(shell find src/ -name "*.cpp")
OBJS=$(patsubst src/%.cpp, obj/%.o, $(SRC))
#include path
INC := -I ./include -I ./include/SE -I/usr/include/freetype2
#Lib path
#LIBP := #-L ./bin

all: plugins/$(PROGRAM)

plugins/$(PROGRAM): $(OBJS)
	$(CXX) $(NOTIF_FLAGS) -shared $(OBJS) $(LIBP) $(LIBS) -o $@

#$(OBJECTS): $(SOURCES)
obj/%.o: src/%.cpp
	$(CXX) $(INC) $(NOTIF_FLAGS) $(CXXFLAGS) $< -o $@
	@echo ' '

obj/%.o: src/%.c
	$(CXX) $(INC) $(NOTIF_FLAGS) $(CXXFLAGS) $< -o $@
	@echo ' '

clean:
	@find obj/ -name \*.o -delete
	@find obj/ -name \*.d -delete

