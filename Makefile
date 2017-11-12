TARGET = malom
LIBS =
CC = gcc
CFLAGS = -g -Wall

SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

.PHONY: default all clean

all: dir $(BUILDDIR)/$(TARGET)
dir:
	mkdir -p $(BUILDDIR)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LIBS)

.PRECIOUS: $(TARGET)

clean:
	-rm -rf $(BUILDDIR)
