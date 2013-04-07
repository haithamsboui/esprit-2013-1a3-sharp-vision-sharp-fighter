#Sharp Fighters makefile.    
NAME=SharpFighters
CFILES := $(wildcard src/*.c)
OFILES := $(addprefix obj/,$(notdir $(CFILES:.c=.o)))
LIBS = -L./lib -lftgl -lapeg -logg -ltheora -lvorbis -lalleggl -lloadpng -lalleg $(shell allegro-config --libs)
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

install-dep:
	sudo apt-get install liballegro4.4
	sudo apt-get install liballegro4.2-dev
	sudo apt-get install libloadpng4.4
	sudo apt-get install libloadpng4-dev
	sudo apt-get install libglu1-mesa-dev
	sudo apt-get install liballeggl4.4
	sudo apt-get install liballeggl4-dev
	sudo apt-get install libogg-dev
	sudo apt-get install libvorbis-dev
	sudo apt-get install libtheora-dev
	sudo apt-get install libftgl2
	sudo apt-get install libftgl-dev
	sudo apt-get install libfreetype6
	sudo apt-get install libfreetype6-dev
#	sudo apt-get install liballegro4.4-plugin-alsa

help:
	@echo "Commands :"
	@echo "	build : Builds the excutable."
	@echo "	clean : Cleans binary files."
	@echo "	run : Runs the excutable, and build if not built yet."
	@echo "	install-dep : Installs dependencies if not already installed."


	
