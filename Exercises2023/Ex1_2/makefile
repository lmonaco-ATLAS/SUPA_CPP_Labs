CC =g++ #Name of the compiler
FLAGS = -std=c++20 -w  #compiler flags. We set the C++ standard to C++20, and -w is suppressing all the warnings
TARGET = AnalyseData #Final executable name
OBJECTS = AnalyseData.o CustomFunctions.o #Intermediate object files. These files need to be linked together to create the executable

#First target in MakeFile is what gets made by default. This means that the default target is what is executed when you run make without any arguments. It depends on the object files listed in the OBJECTS variable.
${TARGET}:${OBJECTS} #Make target from objects.
	@echo "Linking..."    	# Using @command lets you run pretty much any shell command. So, @echo prints a "Linking..." message. The @ symbol suppresses the command from being printed
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}    	# compiles the object files into the final executable.
	@make clean 	#Calls the clean target to remove the object files. This ensures that the object files are deleted after they have been linked into the executable.

#These rules specify how to create the object files from the corresponding source files. 
AnalyseData.o : AnalyseData.cpp CustomFunctions.h  #The target CustomFunctionExample.o depends on CustomFunctionExample.cxx and CustomFunctions.h, meaning that if either of these files changes, make will recompile CustomFunctionExample.o.
	${CC} ${FLAGS} -c AnalyseData.cpp  	    # This command compiles the source file into an object file without linking (-c flag).

CustomFunctions.o : CustomFunctions.cpp CustomFunctions.h
	${CC} ${FLAGS} -c CustomFunctions.cpp

clean: #No targets just run shell command to rm object files and emacs backups
	@rm -f *.o *~

cleantarget: #Delete the executable
	@rm -f ${TARGET}