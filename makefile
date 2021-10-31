libs = include/
SRCPATH  = src/
OBJPATH = obj/


CC = gcc
CCFLAGS = -Wall -I${libs} -g


vpath %.c $(SRCPATH)
vpath %.o $(OBJPATH)
vpath %.h $(libs)
vpath jeu_de_la_vie bin

targets = $(subst $(SRCPATH),$(OBJPATH), $(subst .c,.o,$(wildcard $(SRCPATH)*.c)))






$(OBJPATH)%.o : $(SRCPATH)%.c
	$(CC) $(CCFLAGS) -c $< -o $@



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
