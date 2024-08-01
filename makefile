#!/usr/bin/make -f
CFLAGS = -std=c17 -Ofast -march=native -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -pedantic-errors -Wold-style-definition -g
EXEC = cdates
cc_link = -lgmp -L/usr/local/include
ifdef DEBUG
	CFLAGS += -00
else
	CFLAGS += -03 -DNDEBUG
endif

cdates: main.c
	$(CC) $^ -o $@ ${cc_link}

style:
	astyle -rv --style=linux --indent=force-tab=4 --delete-empty-lines \
	--break-closing-braces --max-code-length=80 --lineend=linux --ascii \
	"*.c"

clean:
	rm -rf build
