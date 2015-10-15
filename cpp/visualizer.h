//  Visualizer, a software that allows you to visualize songs live on a led-matrix
//  Copyright (C) 2015 Dominik Meier(XPerianer)
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  E-Mail: hiscore.pressthebutton()hotmail.de



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <math.h>

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

#include "ColorStruct.h"
#include "EffectCreation.h"

using namespace rgb_matrix;

#define PI 3.14159265

class Visualizer : public ThreadedCanvasManipulator{
  ColorStruct matrix[32][32];
  int sleepTime;
  int animationStatus;
  int repaintAction;
  int brightness;
  int manipulatorStep;
  EffectCreation effectCreation;

public:


  Visualizer(Canvas *canvas);
  ~Visualizer();

  virtual void Run();

  void setCommand(int command[6]);
  void display();
  void brightnessManipulator(ColorStruct pMatrix[32][32]);



};
