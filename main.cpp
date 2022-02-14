/*  Moving point
*   Draws a point at the centre of the screen, its position changes
*   in accordance with user input (via the joystick).
*
*   Author: Andrew Knowles 2021 / Updated by Dr Tim Amsdon Feb 2022
*/

#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"

//                  y     x
Joystick joystick(PC_3, PC_2);  //attach and create joystick object

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

//set initial position of point to (42,24)
float y_pos = 24;
float x_pos = 42;

void boundary(int x, int y);

int main(){
    joystick.init();
    lcd.init();
    lcd.setContrast(0.4);      //set contrast to 40%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    
    while (1) {
        lcd.clear();
        lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);   //draws screen boarder
        lcd.drawRect(x_pos,y_pos,2,2,FILL_BLACK);   //draws point at position (x,y)

        /*  read the direction of the joystick and create new co-ordinates for the point.
        *   y-- : decrement the y co-ordinate of the point thus moving it towards the top of the screen 
        *   x-- : decrement the x co-ordinate of the point thus moving it towards the left hand side of the screen 
        */

        if(joystick.get_direction() == N){
            y_pos--;
            printf(" Direction: N\n");

        }else if(joystick.get_direction() == S){
            y_pos++;
            printf(" Direction: S\n");
        
        }else if(joystick.get_direction() == E){
            x_pos++;
            printf(" Direction: E\n");

        }else if(joystick.get_direction() == W){
            x_pos--;
            printf(" Direction: W\n");

        }else if(joystick.get_direction() == NE){
            y_pos--;
            x_pos++;
            printf(" Direction: NE\n");

        }else if(joystick.get_direction() == NW){
            y_pos--;
            x_pos--;
            printf(" Direction: NW\n");

        }else if(joystick.get_direction() == SE){
            y_pos++;
            x_pos++;
            printf(" Direction: SE\n");

        }else if(joystick.get_direction() == SW){
            y_pos++;
            x_pos--;
            printf(" Direction: SW\n");
        } else {
            printf(" Direction: Centre\n");
        }



        boundary(x_pos, y_pos); //pass the new x,y position to function
            
        lcd.refresh();
        ThisThread::sleep_for(30ms);
    }
}

//check that the point remains on the screen
void boundary(int x, int y){
    if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        x_pos = 1;
    }else if (x > 81){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        x_pos = 81;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        y_pos = 1;
    }else if(y > 45){   //ensure that the point doesnt pass beyond the bottom of the screen
        y_pos = 45;
    }
}
