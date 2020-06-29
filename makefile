# project name (generate executable with this name)
TARGET   = unGame

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
INCLUDEDIR = include

CC       = g++
# compiling flags here
CFLAGS   = -std=c++2a -Wall -I$(INCLUDEDIR) -I/home/kamil/dev/libs/SDL2_gfx-1.0.1 -O0 -g3

LINKER   = g++
# linking flags here
LFLAGS   = -Wall -I. -lm -pthread -lSDL2 -lSDL2_gfx -lboost_program_options -lncurses -lSDL2_ttf

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDEDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -rf

$(BINDIR)/$(TARGET): $(OBJECTS)
	    @mkdir -p bin 
			@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
			    @echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	    @mkdir -p obj 
			$(CC) $(CFLAGS) -c $< -o $@
			    @echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(OBJDIR) $(BINDIR)
		@echo "Cleanup complete!"

