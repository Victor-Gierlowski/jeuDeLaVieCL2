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

jeu_de_la_vie : $(targets)
	echo $(targets)
	$(CC) $(CCFLAGS) -o jeu_de_la_vie $(targets)
	mv $@ bin/


$(OBJPATH)%.o : $(SRCPATH)%.c
	echo a
	$(CC) $(CCFLAGS) -c $< -o $@

clean :
	rm -f obj/ bin/
