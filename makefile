#Sharp Fighters makefile.    
NAME=SharpFighters
ARCH := $(shell getconf LONG_BIT)
CFILES := $(wildcard src/*.c)
OFILES := $(addprefix obj/,$(notdir $(CFILES:.c=.o)))
ALLEGROLIBS := $(shell allegro-config --libs)
LIBS = -L./lib -lftgl -lapeg$(ARCH) -logg -ltheora -lvorbis -lalleggl -lloadpng -lm -lGL -lGLU $(ALLEGROLIBS:alleg-4.2.2=alleg)
COMPILER = gcc
OPTIONS = -c -Wall
CFLAGS = $(shell freetype-config --cflags) $(shell allegro-config --cflags) -Iinclude

build: obj $(OFILES)
	$(COMPILER) -o $(NAME) $(OFILES) $(LIBS)

obj/%.o: src/%.c
	$(COMPILER) $(CFLAGS) $(OPTIONS) -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf obj
	rm -f $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME):
	@if [ -f $(NAME) ]; then \
		echo "Starting $(NAME) ..."; \
	else \
		echo "$(NAME) not found. Rebuilding..."; \
		$(MAKE) build; \
	fi


help:
	@echo "Commands :"
	@echo "	build : Builds the excutable."
	@echo "	clean : Cleans binary files."
	@echo "	run : Runs the excutable, and build if not built yet."
