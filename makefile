SRC1 = test.c
SRC2 = bmpheader.h
SRC3 = bmpimage.h
SRC4 = bmpfile.h
SRC5 = bmpfile.c
EXE = $(SRC1:.c=.e)

all : $(SRC1)
	gcc -Wall -o $(EXE) $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) -std=c99 -g
