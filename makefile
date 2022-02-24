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

#run cause I hate to type ./lagrange
run: lagrange
	./lagrange

clean:
	rm lagrange $(OBJECTS) $(DEPENDS)

