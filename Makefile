# --- Compiler and Flags ---
CXX := g++

# CXXFLAGS are the compiler flags
# -std=c++17: Use the C++17 standard (for std::optional, etc.)
# -O2: Optimization level 2
# -Iinclude: Tell the compiler to look for headers in the 'include' folder
# -Wall -Wextra: Enable all common warnings
# -g: Include debug symbols
# -D_WIN32_WINNT=0x0A00: Define Windows version as Windows 10 (fixes httplib error)
# -DWIN32_LEAN_AND_MEAN: Windows optimization
# -DNOMINMAX: Windows optimization (prevents 'byte' conflict)
CXXFLAGS := -std=c++17 -O2 -Iinclude -Wall -Wextra -g \
            -D_WIN32_WINNT=0x0A00 \
            -DWIN32_LEAN_AND_MEAN \
            -DNOMINMAX

# LDFLAGS are the linker flags
# -lpthread: Link the POSIX threads library (for std::thread)
# -lws2_32: Link the Windows Sockets 2 library (for httplib)
LDFLAGS := -lpthread -lws2_32

# --- Project Structure ---
SRCDIR := src
BINDIR := build
TARGET := $(BINDIR)/dsa_project.exe

# Find all .cpp files in the src directory
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# Map the source files to their corresponding object files in the build directory
# Example: src/Node.cpp -> build/Node.o
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SRCS))

# --- Rules ---
# .PHONY means these are not files, but commands
.PHONY: all run clean

# Default target: 'make all' or just 'make'
all: prepare $(TARGET)

# Link the executable
# This rule runs *after* all .o files are built
$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile object files
# This is the efficient, two-step compilation rule
# It compiles any .cpp file that has changed into its .o counterpart
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories needed for the build
prepare:
	@mkdir -p $(BINDIR)
	@mkdir -p demo_results
	@mkdir -p logs

# Run the live C++ server
# This is now a foreground process; stop with Ctrl+C
run: all
	@echo "--- C++ Network Engine is LIVE ---"
	@$(TARGET)

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BINDIR)
	@echo "Clean done."