SRC1 = imgPro.c
SRC2 = bmpheader.h
SRC3 = bmpimage.h
SRC4 = bmpfile.h
SRC5 = bmpfile.c
SRC6 = bmpfunc.h
SRC7 = bmpcolor.c
SRC8 = bmpinvert.c
EXE = $(SRC1:.c=.e)

all : $(SRC1)
	gcc -Wall -o $(EXE) $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6) $(SRC7) $(SRC8) -std=c99 -g
