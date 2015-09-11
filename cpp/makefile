RGB_INCDIR= ../matrix-library/include
RGB_LIBDIR= ../matrix-library/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

CXX := g++
CXXFLAGS := -Wall -O3 -g -std=c++0x
OBJECTS := visualizer.o


visualizer.app : $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# (FYI: Make sure, there is a TAB-character in front of the $(MAKE))
$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

visualizer.o : visualizer.cpp visualizer.h socket.cpp
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR)  visualizer.cpp -c -o  $@
