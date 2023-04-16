##################################
# simple Makefile for ACO course #
##################################

# pick your favourite compiler
COMPILER	=	gcc

# flags you want to use when compiling
FLAGS		=	-O2 -fopenmp 

# system-wide libraries you like to link to
LIBRARIES	=	-lm 

# your code might be split into several C-files; here you specify which...
OBJECTS		=	utility.o my.o

# and it might be the best to actually put all those auxiliary files into a single library
MY_LIBRARY	=	libACO.a

##########################################################################################
# general syntax for the 'rules':                                                        #
#                                                                                        #
# rulename: all_the files_the_rule depends_on $(OBJECTS)                                 #
#   "TAB"  $(COMPILER) $(FLAGS) -o outputname name_of_C_file.c   $(OBJECTS) $(LIBRARIES) #
#          ^^^^^^^^^^^^^^^^^^^^                                  ^^^^^^^^^^^^^^^^^^^^^^^ #
#           compilation stuff                                         linking stuff      #
#                                                                                        #
#                                                                                        #
# objectfile.o: all_the files_the_objectfile depends_on                                  #
#   "TAB"  $(COMPILER) $(FLAGS) -c name_of_C_file.c   $(LIBRARIES)                       #
#                                                                                        #
##########################################################################################

# the rules for how to make all the relevant files

test00:	mandelbrot_main.c
	$(COMPILER) $(FLAGS) -o mandelbrot_main mandelbrot_main.c $(LIBRARIES)

# remove everything that is not needed and allow for a fresh compilation of everything
clean:
	rm -rf *.o libACO.a *.dSYM rm -f mandelbrot_main 
