COMP = gcc
FLAGS = -Wall -Wextra -pedantic

# Target files
RAY_CASTER = caster.c
BREAKOUT = bkout.c
SNAKE = snake.c
PONG = pong.c

default:
	$(COMP) -o prog $(RAY_CASTER) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	./prog

snake:
	@$(COMP) -o prog $(SNAKE) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	@./prog

pong:
	@$(COMP) -o prog $(PONG) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	@./prog

break:
	@$(COMP) -g -o prog $(BREAKOUT) -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm
	@./prog
