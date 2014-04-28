#!/bin/bash

#@ Step 1. Generate .class and .h
# javac Retrieve.java
# javah -jni Retrieve

#@ Step 2. Compile shared library 
#g++ -Wall -shared -I$JAVA_HOME/include/linux -I$JAVA_HOME/include -I../include FileRecur.cpp GetInvar.cpp Retrieve.cpp Stat.cpp -o libRetrieve.so liblshkit.a -L/usr/lib/ -lgsl -lgslcblas -lm -lboost_program_options-mt -lboost_system -lboost_filesystem-mt -lopencv_core -lopencv_imgproc -lopencv_highgui

#@ Step 2.5 Test .so dependence
#ldd -d libRetrieve.so

#@ Step 3. Run
# -Djava.library.path=. System.getProperty("java.library.path")
java Retrieve