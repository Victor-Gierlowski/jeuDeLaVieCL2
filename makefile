cc = gcc
includes = includes/
src = src/
out = bin/gameOfLife.exe
obj = temp/

ccflags = -Wall -I$(includes)


$(src)*.c :
	$(cc) $(ccflags) -o $(addsuffix .o,$@)
