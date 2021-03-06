 #include <MeggyJrSimple.h>
boolean gameOver = false;
int gameTimer=0;
void setup()
{
  MeggyJrSimpleSetup();
  drawCities();
  drawTargeter();
  Serial.begin(9600); //this code keeps the dots on the screen
  gameTimer=millis();
}

int xCoord=3;
int yCoord=3;
int ctyDraw[8]={0,1,2,3,4,5,6,7};
int ctyGone[8]={1,1,1,1,1,1,1,1}; 
//int createEnemy[50];
int level=0;
int numEnemy=3;
int enemyX[10];
int enemyY[10];//the ten means how many dots there can be
int enemyNum=0;//
int enemyDestroyed[10]={1,1,1,1,1,1,1,1,1,1};
int tmrTarget=0;
int goEnemy=0;
int goEnemyTmr=0;
int enemyStart=0;
int EnemyDrop=0;
int EnemyDropStart=0;
int screenClear=0;
int screenClearWait=0;



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
    drawEnemy();
    moveTargeter();//move targeter comes before draw because you want the targeter to mvoe on screen
    drawTargeter();
    if(gameTimer>30000)
    {
      for(int c=0; c<8; c++)
      {
        ctyGone[c]=0;
      }
      gameTimer=millis();
    }
  }
  gameOver = Destroyed();//set this so it only reads the boolean statement once
  DisplaySlate();
  delay(50);
  ClearSlate();
}
void drawTargeter()
{
  CheckButtonsDown();
  if(Button_A)
  {
    //DrawPx(xCoord-1,yCoord,Blue);
    DrawPx(xCoord,yCoord,Blue);
  }
  else
  {
    DrawPx(xCoord,yCoord,Yellow);
    //WADrawPx(xCoord-1,yCoord,Yellow);
  }
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
void drawEnemy()
{
  for(int i=0; i<enemyNum; i++)
    {
    if(ReadPx(enemyX[i],enemyY[i])==Blue)
    {
      enemyDestroyed[i]=0;
    }
  }
  if(enemyStart==0)
  {
    goEnemyTmr=millis();
    goEnemy=random(250,1000);
    enemyStart=1;
  }
  if(EnemyDropStart==0)
  {
    EnemyDrop=millis();
    EnemyDropStart++;
  }
  if(millis()-goEnemyTmr>goEnemy)
  {
    if(enemyNum<10)
    {
      enemyY[enemyNum]=7;
      enemyX[enemyNum]=random(0,7);
      if(enemyNum<10)
      {
        enemyNum++;
      }
      else
      {
        enemyNum=100;
      }
      enemyStart=0;
    }
    else
    {
      if(screenClear==0)
      {
        screenClearWait=millis();
        screenClear=1;
      }
      if(millis()-screenClearWait>7000)
      {
        for(int reset=0; reset<10; reset++)
        {
          enemyDestroyed[reset]=1;
        }
        enemyNum=0;
        enemyStart=0;
        EnemyDropStart=0;
        screenClear=0;
      }
    }
  }
  if(millis()-EnemyDrop>1000)
  {
     for(int i=0; i<enemyNum; i++)
    {
      if(ReadPx(enemyX[i],enemyY[i]-1)==Blue)
      {
        enemyDestroyed[i]=0;
      }
      if(ReadPx(enemyX[i],enemyY[i]-1)==Green)
      {
        ctyGone[enemyX[i]]=0;
        enemyDestroyed[i]=0;
      }
      else
      {
        if(enemyY[i]==0)
        {
          enemyDestroyed[i]=0;
        }
        else
        {
          if(enemyDestroyed[i]==1)
          {
            enemyY[i]=enemyY[i]-1;
          }
        }
      }
    }

    EnemyDropStart=0;
  }
  for(int i=0; i<enemyNum; i++)
  {
    if(enemyDestroyed[i]==1)
    {
      DrawPx(enemyX[i], enemyY[i], Red);
    }
  }
  /*for(int n=0; n<=numEnemy; n++)
  {
    if(createEnemy[n]<=numEnemy&&millis()-tmrTarget==goEnemy)
    {  
      createEnemy[n]=7;
      DrawPx(random(7),createEnemy[n],Red);
      tmrTarget=millis();
      goEnemy=random(1000);
    }
  }*/
}
