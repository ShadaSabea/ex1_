CC = gcc;
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = prog
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
main.o : main.c RLEList.h AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) $(EXEC)
