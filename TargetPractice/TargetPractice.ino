#include <MeggyJrSimple.h>
boolean gameOver = false;
void setup()
{
  MeggyJrSimpleSetup();
  drawCities();
  drawTargeter();
  Serial.begin(9600); //this code keeps the dots on the screen
}

int xCoord=3;
int yCoord=3;
int ctyDraw[8]={0,1,2,3,4,5,6,7};
int ctyGone[8]={1,1,1,1,1,1,1,1}; 

void loop()
{
  if (gameOver) //this means if it is true
  {
    ClearSlate();
    DisplaySlate();
    delay(3000);
  }
  else
  {
    drawCities();
    moveTargeter();//move targeter comes before draw because you want the targeter to mvoe on screen
    drawTargeter();
  }
  gameOver = Destroyed();//set this so it only reads the boolean statement once
  DisplaySlate();
  delay(50);
  ClearSlate();
}
void drawTargeter()
{
  DrawPx(xCoord-1,yCoord,5);
  DrawPx(xCoord+1,yCoord,5);
  DrawPx(xCoord,yCoord-1,5);
  DrawPx(xCoord,yCoord+1,5); 
}

boolean Destroyed()
{
  for (int i = 0; i < 8; i++)
  {
    if (ReadPx(i,0)>0)
    {
      return false;
    }
  }
  return true;
}
void drawCities()
{
  for(int city=0; city<8; city++)
  {
    if(ctyGone[city]==1)
    {
      DrawPx(ctyDraw[city],0,Green);
    }
  }
}
void moveTargeter()
{
  CheckButtonsPress();
  if(Button_Right)
  {
    xCoord=xCoord+1;
    if(xCoord>7)
    {
      xCoord=7;
    }
  }
  if(Button_Left)
  {
    xCoord=xCoord-1;
    if(xCoord<0)
    {
      xCoord=0;
    }
  }
  if(Button_Down)
  {
    yCoord=yCoord-1;
    if(yCoord<1)
    {
      yCoord=1;
    }
  }
  if(Button_Up)
  {
    yCoord=yCoord+1;
    if(yCoord>6)
    {
      yCoord=6;
    }
  }
}
