CC = gcc
RLELIST= /home/mtm/public/2122b/ex1/RLEList
OBJS = RLEList.o tool/AsciiArtTool.o tool/main.o
EXEC = AsciiArtTool
DEBUG_FLAG =
COMP_FLAG = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic -errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(OBJS) -o $@
RLEList.o : RLEList.c $(RLELIST).h
	$(CC) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.c -o $@
tool/AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h $(RLELIST).h
	$(CC) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.c -o $@
tool/main.o : tool/main.c $(RLELIST).h tool/AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $(DEBUG_FLAG) $*.c -o $@
clean:
	rm -f $(OBJS) $(EXEC)
