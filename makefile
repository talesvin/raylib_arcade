COMP = gcc
FLAGS = -Wall -Wextra -pedantic

# Target files
BREAKOUT = bkout.c
PONG = pong.c

default:
	$(COMP) -o prog $(BREAKOUT) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	./prog

pong:
	@$(COMP) -o prog $(PONG) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	@./prog

break:
	@$(COMP) -g -o prog $(BREAKOUT) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	@./prog
