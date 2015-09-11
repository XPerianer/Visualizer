#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <fstream>

#include <chrono>

#include "led-matrix.h"
#include "graphics.h"
#include "threaded-canvas-manipulator.h"

//Used for Socket communication
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT "1337" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once

using namespace rgb_matrix;

struct ColorStruct{
  int r,g,b;
};

class Visualizer : public ThreadedCanvasManipulator{
  ColorStruct matrix[32][32];
  int rate;
  int animationStatus;
  int repaintAction;
  int r,g,b;


public:


  Visualizer(Canvas *canvas);
  ~Visualizer();

  virtual void Run();
  void stroboscope();
  void lightchange();
  void fadeIn();
  void fadeOut();
  void pulseCircle();
  void lines();
  void randomLines();
  void circles();
  void randomCircles();
  void square();
  void randomPixel();
  void rotateLine();
  void setCommand(int command[6]);
  void clear();


};
