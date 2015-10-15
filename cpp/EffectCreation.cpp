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





#include "EffectCreation.h"

void EffectCreation::setAnimationStep(long pAnimationStep){
  animationStep = pAnimationStep;
}

void EffectCreation::setAnimationColor(int pr,int pg, int pb){
  r = pr;
  g = pg;
  b = pb;
}

void EffectCreation::clear(){
        fill(0,0,0);
}

void EffectCreation::fill(int r, int g, int b){
  for(int i=0;i<32;i++){
    for(int j=0;j<32;j++){
      matrix[i][j].r = r;
      matrix[i][j].g = g;
      matrix[i][j].b = b;

    }
  }
}

void EffectCreation::getMatrix(ColorStruct pMatrix[32][32]){
  for(int i=0;i<32;i++){
    for(int j=0;j<32;j++){
      pMatrix[i][j] = matrix[i][j];
    }
  }
}

void EffectCreation::stroboscope(){

        if(animationStep %2){
          fill(r,g,b);
        } else {
          clear();
        }
        animationStep++;

}

void EffectCreation::fadeIn(){
  if(!animationFinished){
      fill(r*animationStep/255,g*animationStep/255,b*animationStep/255);
      animationStep++;
      if(animationStep > 255){
        animationFinished=true;
      }
    }
}
/*
void EffectCreation::fadeOut(){
        //Always clears as uses the Fill command
        for(int i=255; i>0 && running(); i--) {
                fill(r*i/255,g*i/255,b*i/255);
                usleep(1000 * 5);
        }
}

void EffectCreation::pulseCircle(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                //dont clear
        }      else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        for(int i=0; running(); i++) {
                //DrawCircle(canvas(),15,15,i%15,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000*20);
                if(i>=255) {
                        i=0;
                }
        }
        clear();

}

void EffectCreation::lines(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        if(rate == -1) {
                rate = 10;
        }
        while(running()) {
                //DrawLine(canvas(),rand()%32,rand()%32,rand()%32,rand()%16,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000 * 10 * rate);
        }
}

void EffectCreation::randomLines(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        if(rate == -1) {
                rate = 10;
        }
        while(running()) {
                for(int i=0; i< 5; i++) {
                        //DrawLine(canvas(),rand()%32,rand()%32,rand()%32,rand()%16,Color(rand()%255,rand()%255,rand()%255));
                        usleep(1000 * 10 * rate );
                }
                clear();
        }
}




void EffectCreation::circles(){
        if(rate == -1){
          rate = 10;
        }
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        while(running()) {
                //DrawCircle(canvas(),rand()%32,rand()%32,rand()%5,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000 * 10 * rate);
        }
}

void EffectCreation::randomCircles(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        if(rate == -1) {
                rate = 10;
        }
        while(running()) {
                for(int i=0; i<5; i++) {
                        //DrawCircle(canvas(),rand()%32,rand()%32,rand()%5,Color(rand()%255,rand()%255,rand()%255));
                        usleep(1000 * 10 * rate);
                }
                clear();
        }
}

void EffectCreation::square(){
        if(r == -1) {
                r = 255;
        }
        if(b == -1) {
                b = 0;
        }
        if(g == -1) {
                g = 0;
        }
        if(rate == -1) {
                rate = 10;
        }

        for(int i=0; running(); i++) {
                //DrawLine(canvas(),i,i,31-i,i,Color(r,g,b)); //   -
                //DrawLine(canvas(),i,i,i,31-i,Color(r,g,b)); // |
                //DrawLine(canvas(),31-i,i,31-i,31-i,Color(r,g,b)); //      |
                //DrawLine(canvas(),i,31-i,31-i,31-i,Color(r,g,b)); //   -

                usleep(1000 * 2 * rate);
                clear();
                if(i>15) {
                        i=-1;
                }
        }


}

void EffectCreation::randomPixel(){
        if(r == -1) {
                r = 255;
        }
        if(b == -1) {
                b = 0;
        }
        if(g == -1) {
                g = 0;
        }
        if(rate == -1) {
                rate = 10;
        }
        while(running()) {
                //canvas()->SetPixel(rand()%32,rand()%32,rand()%255,rand()%255,rand()%255);
                usleep(1000 * rate);
                clear();
        }
}

void EffectCreation::rotateLine(){
        if(r == -1) {
                r = 255;
        }
        if(b == -1) {
                b = 0;
        }
        if(g == -1) {
                g = 0;
        }
        if(rate == -1) {
                rate = 10;
        }
        int x_1=0,y_1=0,x_2=31,y_2=31;

        while(running()) {
                if(x_1 < 31) {
                        x_1++;
                } else if(y_1 < 31) {
                        y_1++;
                } else{
                        x_1=0;
                        y_1=0;
                }

                if(x_2 > 0) {
                        x_2--;
                } else if(y_2>0) {
                        y_2--;
                } else{
                        x_2= 31;
                        y_2=31;
                }



                //DrawLine(canvas(),x_1,y_1,x_2,y_2,Color(r,g,b));
                usleep(1000 * 2* rate);
                clear();
        }

}

void EffectCreation::lightchange(){
        // Default is always clear as uses the Fill command
        int r=255,g=0,b=0;
        int animationColorStatus=0;
        while(running())
        {
                usleep(1000 * 1);
                //Get nice Rainbow Colors
                switch(animationColorStatus) {
                case 0:
                        b++; fill(r,g,b);
                        if(b >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 1:
                        r--; fill(r,g,b);
                        if(r <= 0) {
                                animationColorStatus++;
                        }
                        break;
                case 2:
                        g++; fill(r,g,b);
                        if(g >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 3:
                        b--; fill(r,g,b);
                        if(b <= 0) {
                                animationColorStatus++;
                        }
                        break;
                case 4:
                        r++; fill(r,g,b);
                        if(r >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 5:
                        g--; fill(r,g,b);
                        if(g <= 0) {
                                animationColorStatus = 0;
                        }
                        break;
                }

        }

        clear();

}
*/
