LIBSDL = -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL -lSDL_image -lpthread

PROG = testSDL
CC = g++
INCLS = -I/usr/include 

#source codes
SRCS = $(PROG).cpp setvideo.cpp drawpixel.cpp loadimage.cpp waitevent.cpp pthreads_demo.cpp \
	   sdlthread_demo.cpp ppmviewer.cpp proconsumer.cpp tplayer.cpp waitevent1.cpp
#substitute .c by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o)  
#$< evaluates to the target's dependencies,
#$@ evaluates to the target
 
$(PROG): $(OBJS) 
	echo  $(OBJS)  
	$(CC) -o $@ $(PROG).o  $(LIBSDL) 
	$(CC) -o setvideo setvideo.o $(LIBSDL)
	$(CC) -o drawpixel drawpixel.o $(LIBSDL)
	$(CC) -o loadimage loadimage.o $(LIBSDL)
	$(CC) -o waitevent waitevent.o $(LIBSDL)
	$(CC) -o waitevent1 waitevent1.o $(LIBSDL)
	$(CC) -o pthreads_demo pthreads_demo.o $(LIBSDL)
	$(CC) -o sdlthread_demo sdlthread_demo.o $(LIBSDL)
	$(CC) -o ppmviewer ppmviewer.o $(LIBSDL)
	$(CC) -o proconsumer proconsumer.o $(LIBSDL)
	$(CC) -o tplayer tplayer.o $(LIBSDL)

$(OBJS):
	$(CC) -c  $*.cpp $(INCLS) 
                                                                                
clean:
	rm $(OBJS)
