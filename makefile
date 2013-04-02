#Sharp Fighters makefile.
NAME=SharpFighters
CFILES := $(wildcard src/*.c)
OFILES := $(addprefix obj/,$(notdir $(CFILES:.c=.o)))
LIBS = -L./lib -lapeg -logg -ltheora -lvorbis -lalleggl -lloadpng -lalleg $(shell allegro-config --libs)
COMPILER = gcc
OPTIONS = -c -Wall
CFLAGS = $(shell allegro-config --cflags) -Iinclude


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
