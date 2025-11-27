CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -march=native -DNDEBUG
TARGET = linear_algebra

# Source files
SRCS = main.cpp Matrix.cpp Analysis.cpp Decomposer.cpp LinearSolver.cpp \
       SparseMatrix.cpp IterativeSolvers.cpp MatrixMarket.cpp

OBJS = $(SRCS:.cpp=.o)

# Library detection
LIBS =
DEFINES =

# Check for BLAS/LAPACK
ifneq ($(shell ldconfig -p | grep -q libblas && echo $$?),0)
    HAS_BLAS := $(shell echo "int main(){return 0;}" | $(CXX) -x c++ - -lblas 2>/dev/null && echo yes || echo no)
    ifeq ($(HAS_BLAS),yes)
        LIBS += -lblas -llapack
        DEFINES += -DUSE_BLAS -DUSE_LAPACK
        $(info [INFO] BLAS/LAPACK libraries detected and will be used)
    else
        $(info [INFO] BLAS/LAPACK libraries not found, using native implementation)
    endif
endif

# Check for OpenMP
HAS_OPENMP := $(shell echo "int main(){return 0;}" | $(CXX) -x c++ -fopenmp - 2>/dev/null && echo yes || echo no)
ifeq ($(HAS_OPENMP),yes)
    CXXFLAGS += -fopenmp
    $(info [INFO] OpenMP support enabled for parallel matrix multiplication)
else
    $(info [INFO] OpenMP not available)
endif

# Default target with auto-detection
all: $(TARGET)
	@echo "Build complete. Optimizations enabled: $(DEFINES)"

# Build without optional libraries
basic:
	@echo "Building basic version without BLAS/LAPACK/OpenMP..."
	$(MAKE) DEFINES="" LIBS="" CXXFLAGS="-std=c++17 -Wall -Wextra -O3 -march=native -DNDEBUG"

# Build with all optimizations (force)
full:
	@echo "Building full version with all optimizations..."
	$(MAKE) DEFINES="-DUSE_BLAS -DUSE_LAPACK" LIBS="-lblas -llapack" CXXFLAGS="-std=c++17 -Wall -Wextra -O3 -march=native -DNDEBUG -fopenmp"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFINES) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all basic full clean
