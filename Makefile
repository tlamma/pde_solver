CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -MMD -MP -Ilib
LDFLAGS =

# Source files
SRCS_MAIN = main.cpp
SRCS_LIB  = lib/ode.cpp lib/vector.cpp lib/numerics.cpp lib/matrix.cpp lib/ode_integrator.cpp lib/finite_elements.cpp lib/pde.cpp lib/pde_integrator.cpp

SOURCES = $(SRCS_MAIN) $(SRCS_LIB)

# Build directory
BUILD = build

# Object and dependency files go into build/
OBJECTS = $(patsubst %.cpp,$(BUILD)/%.o,$(SOURCES))
DEPS    = $(OBJECTS:.o=.d)

EXECUTABLE = pde_integrator

.PHONY: all clean

all: $(EXECUTABLE)

# Link executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Pattern rule: build/%.o from %.cpp
# Automatically creates subdirectories such as build/lib/
$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(EXECUTABLE)

# Include auto-generated header dependencies
-include $(DEPS)
