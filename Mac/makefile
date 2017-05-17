# Dan Fincher
# Ultra Universal Remote makefile


# Define compiler and flag variables
JC = javac
JFLAGS = -cp
.SUFFIXES: .java .class .jar
.java.class:
	$(JC) $(JFLAGS) $(JARFILE) $(CLASSES)


# Default make target entry
default: classes
	

JARFILE = bluecove.jar
CLASSES = UltraUniversalRemote.java UURLocalDevice.java 



classes: $(CLASSES:.java=.class)

# Remove class files
clean: 
	$(RM) *.class



