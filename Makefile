
CXX = g++
# Define Windows version and reduce Windows header pollution to avoid
# conflicts when compiling cpp-httplib on MSYS/MinGW. If you prefer to
# build in WSL/Linux, these defines aren't necessary.
CXXFLAGS = -std=c++17 -O2 -Iinclude -Wall -Wextra -D_WIN32_WINNT=0x0A00 -DWIN32_LEAN_AND_MEAN -DNOMINMAX
LDFLAGS = -lpthread -lws2_32
SRCDIR := src
BINDIR := build
TARGET := $(BINDIR)/dsa_project.exe

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all run clean 

all: prepare $(TARGET)

# build the executable
$(TARGET): $(SRCS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)
	@echo "Built $(TARGET)"

prepare:
	@mkdir -p $(BINDIR)
	@mkdir -p demo_results

run: all
	@echo "Running ADIPE and saving output to demo_results/output.txt..."
	@$(TARGET) | tee demo_results/output.txt

check: run
	@echo "Output saved to demo_results/output.txt (tail -n 20 shown):"
	@tail -n 20 demo_results/output.txt

# remove build artifacts and results
clean:
	@echo "Cleaning build and demo results..."
	@rm -rf $(BINDIR) demo_results
	@rm -f $(SRCDIR)/*.o
	@echo "Clean done."


