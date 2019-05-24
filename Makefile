#-*-makefile-*-

TARGETS = \
    reuzenrad

all All: $(TARGETS)

################################################################################
INCPATH = -I/usr/local/include
LIBPATH = -L. -L/usr/local/lib/hpux32
LIBS = -lglut -lGLU -lGL  -lXt -lXext -lX11 -ljpeg


SRCS = \
	reuzenrad.c InitJPG.c

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

.c.o:
	cc -c $<


reuzenrad:  clean $(OBJS)
	LDOPTS= \
	cc -o reuzenrad $(OBJS) $(LIBPATH) $(LIBS)

clean:
	rm -f reuzenrad $(OBJS) core
