GCC = g++
INCLUDES = -Ilib\SDL2\include
LIBRARIES = -Llib\SDL2\lib
CPP_VERSION = -std=c++17
COMPILER_FLAGS = -Wall 
LDFLAGS = -lSDL2main -lSDL2 -lmingw32

BLANK =

RM = del /s /q /f
FND = dir /s /b

SRCDIR = src\$(BLANK)
OUTDIR = out\$(BLANK)

OBJ_SRC_PATHS = $(addprefix $(OUTDIR), $(shell FOR /F "tokens=6-8 delims=\" %%E IN ('dir /s /b src\*.cpp') DO @echo %%E\%%F\%%G)) 
OBJ_SRC_PATHS_STRIPPED = $(OBJ_SRC_PATHS:\=)
OBJ_DIR_PATHS = $(addprefix $(OUTDIR), $(shell FOR /F "tokens=6-7 delims=\" %%E IN ('dir /s /b /ad src') DO @echo %%E\%%F))
OBJDIRS = $(OBJ_DIR_PATHS:\=)

TARGET = main.exe
MAINOBJ = main.o

SOURCES = $(shell $(FND) $(SRCDIR)*.cpp)
OBJECTS = $(OBJ_SRC_PATHS_STRIPPED:%.cpp=%.o)

MAIN = main.exe

all: $(TARGET)
#	$(info "Compiling all.")

$(TARGET): buildrepo $(OBJECTS) main.o
#	$(info "Echoing 1...")
	$(GCC) $(CPP_VERSION) -o $@ main.o $(OBJECTS) $(COMPILER_FLAGS) $(INCLUDES) $(LIBRARIES) $(LDFLAGS)
 
main.o: 
#	$(info "Compiling main")
	g++ -std=c++17 -c main.cpp $(COMPILER_FLAGS) $(INCLUDES) $(LIBRARIES) $(LDFLAGS) -o main.o 

$(OUTDIR)\%.o: $(SRCDIR)\%.cpp
#	$(info "Compiling " $< " into " $@)
	$(GCC) $(CPP_VERSION) -c $< $(INCLUDES) $(LIBRARIES) $(COMPILER_FLAGS) $(LDFLAGS) -o $@ 

buildrepo:
	@$(call make-repo)

run:
	@$(TARGET)

clean:
	@$(RM) $(OBJECTS) main.o

distclean:
	@$(RM) $(TARGET)

define make-repo
	@FOR %%d IN ($(OBJDIRS)) DO \
		if not exist %%d cmd.exe /c "mkdir %%d"
endef

.PHONY: run clean distclean

