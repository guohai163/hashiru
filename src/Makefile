CC = /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j
BINS = main.gb

all:	$(BINS)

%.o:	%.c
	$(CC) -c -o $@ $<

%.gb:	main.o game_role.o mario.o
	$(CC) -Wl-yp0x143=0x80 -o $@ $^

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm