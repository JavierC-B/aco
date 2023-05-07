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
OBJECTS		=	my.o utility.o sph_functs.o

# and it might be the best to actually put all those auxiliary files into a single library
MY_LIBRARY	=	libSPH.a

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
sph:	sph_main.c $(MY_LIBRARY)              # we are first constructing our own library and then using it during linking
	$(COMPILER) $(FLAGS) -o sph_main sph_main.c $(MY_LIBRARY) $(LIBRARIES)

# our very own library
my.o:		my.c
	$(COMPILER) $(FLAGS) -c my.c $(LIBRARIES)

utility.o:		utility.c
	$(COMPILER) $(FLAGS) -c utility.c $(LIBRARIES)

sph_functs.o:	sph_functs.c sph_functs.h
	$(COMPILER) $(FLAGS) -c sph_functs.c $(LIBRARIES)

libSPH.a: $(OBJECTS)
	ar -r libSPH.a $(OBJECTS)

# remove everything that is not needed and allow for a fresh compilation of everything
clean:
	rm -rf *.o libSPH.a *.dSYM rm -f sph_main
