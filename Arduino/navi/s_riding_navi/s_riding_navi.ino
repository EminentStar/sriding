/*****************************************************************************
* File name:      s_riding_navi.ino
* Description:    [Navigation] the arduino code of S-RIDING
* Author:       junkyu park
* Date:         2016.04.26
*****************************************************************************/
#include <rgb_matrix.h>
#include <SPI.h>

//Hardware SPI
#define DATA_PIN  11
#define CLK_PIN   13

#define LATCH_PIN 6

rgb_matrix M = rgb_matrix(N_X, N_Y, DATA_PIN, CLK_PIN, LATCH_PIN);

void setup()
{
  Serial.begin(115200);
}

/*************************************************************************
*  Description:
*                         display callback function
*        Receive AT comand via serial,and then run the right comand.
*        This function can be run in sweep interval.
*        Reduce delay time at function tail if screen blink.
*        Increase delay time at function tail if screen shows a double image.
* Param:   none
* Retval:  none
**************************************************************************/
void hook(void)
{
  
  int i = 0;

  //Communicating with Android application via USB-Serial Communication 
  if (Serial.available())
  {
    byte cmd = Serial.read(); //read data sent from the android application
    if(cmd == 0x01){ //0x01 indicates going toward left 
      left_arrow(&M);
      servoState = 1;
    }else if(cmd == 0x02){ //0x02 indicates going toward straight
      straight_arrow(&M);
      servoState = 2;
    }else if(cmd == 0x03){ //0x03 indicates going toward right
      right_arrow(&M);
      servoState = 3;
    }else if(cmd == 0x04){ //0x04 indicates doing U-turn
      u_turn_test(&M);
      servoState = 4;
    }else{
      Serial.flush();
    }
    delay(200);
  }
  
}

/*************************************************************************************
*  Description:
*                         loop function
*        Display function must be called.
*        If you wanna do something after display be called,
*    you should give display function a parameter which is a pointer to a function.
* Param:   none
* Retval:  none
**************************************************************************************/
void loop()
{
  start(&M);
  M.display(hook);
}

//hasn't used,,, it is for the future.
void u_turn_test(rgb_matrix *M)
{ 
  M->clear();
  M->plot_color(7,1,1);
  M->plot_color(6,1,1);
  M->plot_color(5,1,1);
  M->plot_color(4,1,1);
  M->plot_color(3,1,1);
  M->plot_color(2,1,1);

  M->plot_color(2,2,1);
  M->plot_color(2,3,1);
  M->plot_color(2,4,1);
  M->plot_color(2,5,1);

  M->plot_color(7,6,1);
  M->plot_color(6,6,1);
  M->plot_color(5,6,1);
  M->plot_color(4,6,1);
  M->plot_color(3,6,1);
  M->plot_color(2,6,1);
}


void right_arrow(rgb_matrix *M)
{
  int i = 0;
  int colCnt = 8;
  int halfCnt = 4;
  int row;

  //Clear the matrix
  M->clear();

  //make the right turn sign with blue color
  M->plot_color(3,7,4);
  M->plot_color(4,7,4);
  M->plot_color(2,6,4);
  M->plot_color(1,5,4);
  M->plot_color(0,4,4);
  M->plot_color(3,7,4);
  M->plot_color(3,6,4);
  M->plot_color(2,5,4);
  M->plot_color(1,4,4);
  M->plot_color(0,3,4);
  
  M->plot_color(5,6,4);
  M->plot_color(6,5,4);
  M->plot_color(7,4,4);
  M->plot_color(4,6,4);
  M->plot_color(5,5,4);
  M->plot_color(6,4,4);
  M->plot_color(7,3,4);
}

void left_arrow(rgb_matrix *M)
{
  int i = 0;
  int colCnt = 8;
  int halfCnt = 4;
  int row;

  //clear the matrix
  M->clear();

  //make the left turn sign with blue color
  M->plot_color(3,0,4);
  M->plot_color(4,0,4);
  
  M->plot_color(2,1,4);
  M->plot_color(3,1,4);
  M->plot_color(4,1,4);
  M->plot_color(5,1,4);
  
  M->plot_color(1,2,4);
  M->plot_color(2,2,4);
  M->plot_color(5,2,4);
  M->plot_color(6,2,4);
  
  M->plot_color(0,3,4);
  M->plot_color(1,3,4);
  M->plot_color(6,3,4);
  M->plot_color(7,3,4);

  M->plot_color(0,4,4);
  M->plot_color(7,4,4);
}

void straight_arrow(rgb_matrix *M)
{
  int i = 0;
  int rowCnt = 8;
  int halfCnt = 4;
  int col;

  //clear the matrix
  M->clear();

  //make the straight sign with green color
  M->plot_color(0,3,2);
  M->plot_color(0,4,2);
  
  M->plot_color(1,2,2);
  M->plot_color(1,3,2);
  M->plot_color(1,4,2);
  M->plot_color(1,5,2);
  
  M->plot_color(2,1,2);
  M->plot_color(2,2,2);
  M->plot_color(2,5,2);
  M->plot_color(2,6,2);
  
  M->plot_color(3,0,2);
  M->plot_color(3,1,2);
  M->plot_color(3,6,2);
  M->plot_color(3,7,2);

  M->plot_color(4,0,2);
  M->plot_color(4,7,2);
}

void start(rgb_matrix *M)
{
  //clear the matrix
  M->clear();
  //make the initialized sign with green color
  M->plot_color(4,2,2);  
  M->plot_color(4,3,2);
  M->plot_color(4,4,2);
  M->plot_color(4,5,2);
}

