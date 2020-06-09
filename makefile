# Here's the makefile

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

# Looks which OS you're compiling
$(info $(SHELL))
ifeq ($(shell uname -s), Linux)
TARGET_EXEC ?= a.out
endif
ifeq ($(shell uname -s), Darwin) # MacOS
TARGET_EXEC ?= a.out
endif
ifeq ($(OS),Windows_NT)
TARGET_EXEC ?= a.exe
endif

# Defining the build and the compiled source path
BUILD_DIR ?= "build"
SRC_DIR ?= "src"

# Defining the path of the source code
SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Defining the includes' path and their flags
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Depending on the OS we tell the compiler which version of C++ we wan to compile for and other things
ifeq ($(shell uname -s), Linux)
CPPFLAGS ?= $(INC_FLAGS) -std=c++14 -MMD -MP -g -Wall -Wextra -03 -fpermissive
endif
ifeq ($(shell uname -s), Darwin)
CPPFLAGS ?= $(INC_FLAGS) -std=c++14 -MMD -MP -g -Wall -Wextra -fpermissive
endif
ifeq ($(OS),Windows_NT)
CPPFLAGS ?= $(INC_FLAGS) -g -std=c++14 -std=gnu++14 -MMD -MP -g -Wall -Wextra -fpermissive -static -Wunused-parameter -Wstrict-aliasing
endif

# Defining the includes path and the libraries path and defining what library we are using outside the libraries path
ifeq ($(shell uname -s), Linux)
LINKER_FLAGS = -I./inc/ -L./lib/Linux/ -lGLEW -lGL -lglfw -lSOIL
endif
ifeq ($(shell uname -s), Darwin)
LINKER_FLAGS = -I./inc/ -L./lib/macOS -L/opt/local/lib -framework OpenGL -lGLEW -lglfw -lSOIL
endif

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	g++ $(OBJS) -o $@ $(LDFLAGS) $(LINKER_FLAGS)

# Compiling assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) $(LINKER_FLAGS) -c $< -o $@

# Compiling C
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	g++ -std=c++0x $(CPPFLAGS) $(CFLAGS) $(LINKER_FLAGS) -c $< -o $@

# Compiling C++
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	g++ $(CPPFLAGS) $(CXXFLAGS) $(LINKER_FLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)/$(SRC_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
