.PHONY: all clean test

CC        = cc
BUILDDIR  = build
PRODUCT   = $(BUILDDIR)/radio
SOURCEDIR = src
SOURCES   = $(wildcard $(SOURCEDIR)/*.c)
OBJECTS   = $(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
INCLUDES  = $(foreach d, $(SOURCEDIR), -I$d)
LIBS      = liquid

CFLAGS  = -Wall
CFLAGS += -Wno-unused-label
CFLAGS += -O0
CFLAGS += -std=c99

all: $(BUILDDIR) $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	$(CC) $^  $(foreach d, $(LIBS), -l$d) -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build:
	$(shell mkdir -p build)

clean:
	rm -f $(PRODUCT)
	rm -rf $(BUILDDIR)

test: $(PRODUCT)
	$(PRODUCT)
