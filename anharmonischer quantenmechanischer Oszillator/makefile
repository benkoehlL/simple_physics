CC      = gcc
# X11
XLIB = -lX11

schroedinger : schroedinger.o Xgraphics.o
	$(CC) -o schroedinger schroedinger.o Xgraphics.o $(XLIB)

schroedingerauto : schroedingerauto.o
	$(CC) -o schroedingerauto schroedingerauto.o $(LDFLAGS)


clean :
	rm *.o *~
