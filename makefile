CC=gcc
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPENDS := $(patsubst %.c,%.d,$(SOURCES))

all:lagrange

#linking the executable from the object files
lagrange: $(OBJECTS)
	$(CC) -o $@ $^


#dependency rules for object files
#one file can be the target of several rules
#one file can not be target of several recipes
-include $(DEPENDS)

#rule and recipe for making object files
#The -MMD flag generates the dependency file (%.d) for each %.c file compiled by this recipe
#If you want to also depend on system headers, use -MD instead
#The -MP option adds empty dummy rules, which avoid errors should header files be removed from the filesystem
%.o: %.c makefile
	$(CC) -MMD -MP -c $< -o $@

#run cause I am too lazy to type "./lagrange"
run: lagrange
	./lagrange

clean:
	rm lagrange $(OBJECTS) $(DEPENDS)



#https://stackoverflow.com/questions/52034997/how-to-make-makefile-recompile-when-a-header-file-is-changed
