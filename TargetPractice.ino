#include <MeggyJrSimple.h>

void setup()
{
  MeggyJrSimpleSetup();
  drawCities();
  drawTargeter();
}

int xCoord=3;
int yCoord=3;
int ctyDraw[8]={0,1,2,3,4,5,6,7};
int ctyGone[8]={1,1,1,1,1,1,1,1}; 

void loop()
{  
  if(Destroyed()==false)
  {
    moveTargeter();
    drawTargeter();
    drawCities();
    Destroyed();
    DisplaySlate();
    delay(50);
    ClearSlate();
  }
  if(Destroyed()==true)
  {
    ClearSlate();
    DisplaySlate();
    delay(3000);
  }
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
    if (ReadPx(i,0)==0)
    {
      return true;
    }
  }
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
    if(yCoord<0)
    {
      yCoord=0;
    }
  }
  if(Button_Up)
  {
    yCoord=yCoord+1;
    if(yCoord>7)
    {
      yCoord=7;
    }
  }
}
