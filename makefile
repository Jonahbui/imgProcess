SRC1 = imgPro.c
SRC2 = bmpheader.h
SRC3 = bmpimage.h
SRC4 = bmpfile.h
SRC5 = bmpfile.c
SRC6 = bmpfunc.h
SRC7 = bmpcolor.c
SRC8 = bmpinvert.c
SRC9 = bmpblur.c
SRC10 = bmpblack_white.c
EXE = $(SRC1:.c=.e)

all : $(SRC1)
	gcc -O3 -Wall -o $(EXE) $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6) $(SRC7) $(SRC8) $(SRC9) $(SRC10) -std=c99 -g -lpthread
