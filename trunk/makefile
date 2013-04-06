#Sharp Fighters makefile.
NAME=SharpFighters
CFILES := $(wildcard src/*.c)
OFILES := $(addprefix obj/,$(notdir $(CFILES:.c=.o)))
LIBS = -L./lib -lftgl -lapeg -logg -ltheora -lvorbis -lalleggl -lloadpng -lalleg $(shell allegro-config --libs)
COMPILER = gcc
OPTIONS = -c -Wall
CFLAGS = $(shell freetype-config --cflags) $(shell allegro-config --cflags) -Iinclude

verif:
	apt-get install libloadpng4.4
	apt-get install libloadpng4-dev
	apt-get install liballegro4.4
	apt-get install liballegro4.2-dev
	apt-get install liballeggl4.4
	apt-get install liballeggl4-dev
	apt-get install liballegro4.4-plugin-alsa
	apt-get install libglu1-mesa-dev
	apt-get install libogg-dev
	apt-get install libvorbis-dev
	apt-get install libtheora-dev
	apt-get install libftgl2
	apt-get install libftgl-dev
	apt-get install libfreetype6
	apt-get install libfreetype6-dev
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
