#include "visualizer.h"
#include "socket.cpp"




int main(int argc, char *argv[]) {

        GPIO gpio;
        gpio.Init();
        RGBMatrix matrix(&gpio);
        Visualizer *visualizer = new Visualizer(&matrix);
        int command[]={2,0,0,0,0,0,0}; //Array with length 7 to get Information from the Webfile

        socketConnection();
        socketfunction(command); //Wait for the first command
        while(true) {

                Visualizer *visualizer = new Visualizer(&matrix);
                visualizer->setCommand(command);
                visualizer->Start(); // Start doing things.
                socketfunction(command); //change animation as needed
                visualizer->Stop();
        }

        getchar();
        close(sockfd);
        delete visualizer;

}


Visualizer::Visualizer(Canvas *canvas) : ThreadedCanvasManipulator(canvas){
        //std::cout << "Initalisation begins" << std::endl; //Very annoying if so often needed
        animationStatus = 2; //Let the Strobe begin


}

Visualizer::~Visualizer(){
        canvas()->Clear();
}

void Visualizer::clear(){
        canvas()->Clear();
}

void Visualizer::stroboscope(){
        //Always clears as uses the Fill command
        if(r == -1) {
                r = 255;
        }
        if(b == -1) {
                b = 255;
        }
        if(g == -1) {
                g = 255;
        }
        while(running()) {
                canvas()->Fill(r,g,b);
                usleep(1000 * 50);
                canvas()->Clear();
                usleep(1000 * 50);
        }

}

void Visualizer::fadeIn(){
        //Always clears as uses the fill command
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
                rate = 5;
        }
        for(int i=0; i<255 && running(); i++) {
                canvas()->Fill(r*i/255,g*i/255,b*i/255);
                usleep(1000 * rate);
        }
}
void Visualizer::fadeOut(){
        //Always clears as uses the Fill command
        for(int i=255; i>0 && running(); i--) {
                canvas()->Fill(r*i/255,g*i/255,b*i/255);
                usleep(1000 * 5);
        }
}

void Visualizer::pulseCircle(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                //dont clear
        }      else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        for(int i=0; running(); i++) {
                DrawCircle(canvas(),15,15,i%15,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000*20);
                if(i>=255) {
                        i=0;
                }
        }
        canvas()->Clear();

}

void Visualizer::lines(){
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        if(rate == -1) {
                rate = 10;
        }
        while(running()) {
                DrawLine(canvas(),rand()%32,rand()%32,rand()%32,rand()%16,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000 * 10 * rate);
        }
}

void Visualizer::randomLines(){
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
                        DrawLine(canvas(),rand()%32,rand()%32,rand()%32,rand()%16,Color(rand()%255,rand()%255,rand()%255));
                        usleep(1000 * 10 * rate );
                }
                clear();
        }
}




void Visualizer::circles(){
        if(rate == -1){
          rate = 10;
        }
        if(repaintAction == -1 || repaintAction == 4) {// Set default behavior for the animation
                clear();
        } else if(  repaintAction == 0  || repaintAction == 2) {//Command to Clear
                clear();
        }
        while(running()) {
                DrawCircle(canvas(),rand()%32,rand()%32,rand()%5,Color(rand()%255,rand()%255,rand()%255));
                usleep(1000 * 10 * rate);
        }
}

void Visualizer::randomCircles(){
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
                        DrawCircle(canvas(),rand()%32,rand()%32,rand()%5,Color(rand()%255,rand()%255,rand()%255));
                        usleep(1000 * 10 * rate);
                }
                clear();
        }
}

void Visualizer::square(){
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
                DrawLine(canvas(),i,i,31-i,i,Color(r,g,b)); //   -
                DrawLine(canvas(),i,i,i,31-i,Color(r,g,b)); // |
                DrawLine(canvas(),31-i,i,31-i,31-i,Color(r,g,b)); //      |
                DrawLine(canvas(),i,31-i,31-i,31-i,Color(r,g,b)); //   -

                usleep(1000 * 2 * rate);
                clear();
                if(i>15) {
                        i=-1;
                }
        }


}

void Visualizer::randomPixel(){
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
                canvas()->SetPixel(rand()%32,rand()%32,rand()%255,rand()%255,rand()%255);
                usleep(1000 * rate);
                clear();
        }
}

void Visualizer::rotateLine(){
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



                DrawLine(canvas(),x_1,y_1,x_2,y_2,Color(r,g,b));
                usleep(1000 * 2* rate);
                clear();
        }

}

void Visualizer::lightchange(){
        // Default is always clear as uses the Fill command
        int r=255,g=0,b=0;
        int animationColorStatus=0;
        while(running())
        {
                usleep(1000 * 1);
                //Get nice Rainbow Colors
                switch(animationColorStatus) {
                case 0:
                        b++; canvas()->Fill(r,g,b);
                        if(b >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 1:
                        r--; canvas()->Fill(r,g,b);
                        if(r <= 0) {
                                animationColorStatus++;
                        }
                        break;
                case 2:
                        g++; canvas()->Fill(r,g,b);
                        if(g >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 3:
                        b--; canvas()->Fill(r,g,b);
                        if(b <= 0) {
                                animationColorStatus++;
                        }
                        break;
                case 4:
                        r++; canvas()->Fill(r,g,b);
                        if(r >= 255) {
                                animationColorStatus++;
                        }
                        break;
                case 5:
                        g--; canvas()->Fill(r,g,b);
                        if(g <= 0) {
                                animationColorStatus = 0;
                        }
                        break;
                }

        }

        canvas()->Clear();

}

void Visualizer::setCommand(int command[6]){
        animationStatus = command[0];
        repaintAction = command[1];
        if(repaintAction >= -1 && repaintAction <= 1) {
                rate = -1;
                r = -1;
                g = -1;
                b = -1;
        }else {
                rate = command[2];
                r = command[3];
                g = command[4];
                b = command[5];
        }

        std::cout << "rate: " << rate << std::endl << "r: " << r << std::endl;
}

void Visualizer::Run(){
        //std::cout << animationStatus << "...";

        switch(animationStatus) {
        case 0: clear(); break;
        case 1: stroboscope(); break;
        case 2: lightchange(); break;
        case 3: fadeIn(); break;
        case 4: pulseCircle(); break;
        case 5: lines(); break;
        case 6: circles(); break;
        case 7: randomLines(); break;
        case 8: square(); break;
        case 9: randomPixel(); break;
        case 10: rotateLine(); break;
        }
        return;

}
