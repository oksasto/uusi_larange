CC=gcc
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPENDS := $(patsubst %.c,%.d,$(SOURCES))

all:lagrange

#linking the executable from the object files
lagrange: $(OBJECTS)
	$(CC) -o $@ $^


#recipes for object files?
-include $(DEPENDS)

#rule for making object files
%.o: %.c makefile
	$(CC) -MMD -MP -c $< -o $@




clean:
	rm lagrange $(OBJECTS) $(DEPENDS)

