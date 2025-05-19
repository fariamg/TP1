CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -Iinclude -O2
SRCDIRS    := src/app src/datastructures src/algorithms src/measurement src/core
SOURCES    := $(wildcard $(addsuffix /*.cpp,$(SRCDIRS)))
OBJDIR     := obj
BINDIR     := bin
BINARY     := $(BINDIR)/tp1
OBJECTS    := $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(BINARY)

# Link
$(BINARY): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	
# Compile
$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
