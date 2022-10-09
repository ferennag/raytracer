INCLUDEDIR=include
SRCDIR=src
OUTDIR=build
TESTDIR=test
SOURCES=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJECTS=$(SOURCES:%.c=$(OUTDIR)/%.o)
TARGET=main

CC=gcc
CFLAGS=-Wall -pedantic -ggdb --std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lSDL2 -lSDL2_image -lm

.PHONY: clean run tests

all: $(OBJECTS) $(TARGET) tests

run: all
	$(OUTDIR)/$(TARGET)

clean:
	rm -rf $(OUTDIR)
	$(MAKE) clean -C test

tests:
	$(MAKE) -C test

$(TARGET): $(OBJECTS)
	$(CC) -o $(OUTDIR)/$@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

$(OUTDIR)/%.o: %.c
	$(shell mkdir -p $(dir $@))
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
