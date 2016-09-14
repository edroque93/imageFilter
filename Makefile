CXX = g++
CFLAGS = -std=c++0x -I include/
LDFLAGS =
WARNINGS =
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = kernel

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LIBRARIES) $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir obj -p
	$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)