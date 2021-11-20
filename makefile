libs = include/
SRCPATH  = src/
OBJPATH = obj/

VERSION  = 1.1.3

CC = gcc
CCFLAGS = -Wall -I${libs} -g


vpath %.c $(SRCPATH)
vpath %.o $(OBJPATH)
vpath %.h $(libs)
vpath jeu_de_la_vie bin

targets = $(subst $(SRCPATH),$(OBJPATH), $(subst .c,.o,$(wildcard $(SRCPATH)*.c)))



all: jeu_de_la_vie


$(OBJPATH)%.o : $(SRCPATH)%.c
	$(CC) $(CCFLAGS) -c $< -o $@

dist:
	tar -cf $(VERSION).tar src makefile
	xz $(VERSION).tar

docs:
	doxygen Doxyfile -g

ifeq ($(OS),Windows_NT)
jeu_de_la_vie : $(targets)
	$(CC) $(CCFLAGS) $(targets) -o jeu_de_la_vie.exe
	move $@.exe bin/
clean :
	del /q obj bin
else
jeu_de_la_vie : $(targets)
	$(CC) $(CCFLAGS) $(targets) -o jeu_de_la_vie
	move $@ bin/
clean :
	rm -f obj/ bin/
endif
