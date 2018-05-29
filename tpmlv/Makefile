TARGETS = mlv

##########################################################

CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

all: $(TARGETS)
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` mlv.c `pkg-config --libs-only-l MLV` -o mlv


clean:
	-rm -rf $(TARGETS)
