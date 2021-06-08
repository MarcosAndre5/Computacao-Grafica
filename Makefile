CC = g++
CFLAGS = -O2
XLIBS = -L/usr/X11/lib -L/usr/X11R6/lib -lX11

INCDIR = /usr/include
LIBDIR = /usr/lib

GL_LIBS = -L$(LIBDIR) -lglut -lGLU -lGL -lm $(XLIBS)

LIB_DEP = $(LIBDIR)/$(GL_LIB)

.SUFFIXES:
.SUFFIXES: .c .cpp

.c: $(LIB_DEP)
	$(CC) -I$(INCDIR) $(CFLAGS) $< -o $@ $(GL_LIBS)

clean:
	-rm *.o *~