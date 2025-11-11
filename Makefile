
CXX = g++
# Define Windows version and reduce Windows header pollution to avoid
# conflicts when compiling cpp-httplib on MSYS/MinGW. If you prefer to
# build in WSL/Linux, these defines aren't necessary.
CXXFLAGS = -std=c++17 -O2 -Iinclude -Wall -Wextra -D_WIN32_WINNT=0x0A00 -DWIN32_LEAN_AND_MEAN -DNOMINMAX
LDFLAGS = -lpthread -lws2_32
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

# build the executable
$(TARGET): $(SRCS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)
	@echo "Built $(TARGET)"

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