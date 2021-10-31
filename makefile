<<<<<<< HEAD
cc = gcc
includes = includes/
src = src/
out = bin/gameOfLife.exe
obj = temp/

ccflags = -Wall -I$(includes)


$(src)*.c :
	$(cc) $(ccflags) -o $(addsuffix .o,$@)
=======
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
>>>>>>> 39f798722180db529e1cc3f2e81ce1c4435837e5
