/*
Original Author: Jae Yeong Bae
                 UBC ECE
                 jocker.tistory.com

Porting        : Yota EGUSA (chibiegg)
*/

#include "tetris.h"

#define TETRIS_WIDTH  (10)
#define TETRIS_HEIGHT (21)

long delays = 0;
short delay_ = 500;
long bdelay = 0;
short buttondelay = 150;
short btdowndelay = 30;
short btsidedelay = 80;
unsigned char blocktype;
unsigned char blockrotation;

int lines = 0;
boolean  block[TETRIS_WIDTH][TETRIS_HEIGHT+2]; //2 extra for rotation
boolean  pile[TETRIS_WIDTH][TETRIS_HEIGHT];
boolean  disp[TETRIS_WIDTH][TETRIS_HEIGHT];

boolean lib[10][5][7];

uint8_t updated = 0;
uint8_t paused = 0;
uint8_t is_gameover = 0;


void tetris_setup() {

lib[0][1][0] = 1;
lib[0][2][0] = 1;
lib[0][3][0] = 1;
lib[0][0][1] = 1;
lib[0][4][1] = 1;
lib[0][3][2] = 1;
lib[0][0][2] = 1;
lib[0][4][2] = 1;
lib[0][2][3] = 1;
lib[0][0][3] = 1;
lib[0][4][3] = 1;
lib[0][1][4] = 1;
lib[0][0][4] = 1;
lib[0][4][4] = 1;
lib[0][0][5] = 1;
lib[0][4][5] = 1;
lib[0][1][6] = 1;
lib[0][2][6] = 1;
lib[0][3][6] = 1;
lib[1][2][0] = 1;
lib[1][1][1] = 1;
lib[1][2][1] = 1;
lib[1][2][2] = 1;
lib[1][2][3] = 1;
lib[1][2][4] = 1;
lib[1][2][5] = 1;
lib[1][1][6] = 1;
lib[1][2][6] = 1;
lib[1][3][6] = 1;
lib[2][1][0] = 1;
lib[2][2][0] = 1;
lib[2][3][0] = 1;
lib[2][0][1] = 1;
lib[2][4][1] = 1;
lib[2][4][2] = 1;
lib[2][3][3] = 1;
lib[2][2][4] = 1;
lib[2][1][5] = 1;
lib[2][0][6] = 1;
lib[2][1][6] = 1;
lib[2][2][6] = 1;
lib[2][3][6] = 1;
lib[2][4][6] = 1;
lib[3][0][0] = 1;
lib[3][1][0] = 1;
lib[3][2][0] = 1;
lib[3][3][0] = 1;
lib[3][4][0] = 1;
lib[3][3][1] = 1;
lib[3][2][2] = 1;
lib[3][3][3] = 1;
lib[3][4][4] = 1;
lib[3][0][5] = 1;
lib[3][4][5] = 1;
lib[3][1][6] = 1;
lib[3][2][6] = 1;
lib[3][3][6] = 1;
lib[4][3][0] = 1;
lib[4][2][1] = 1;
lib[4][3][1] = 1;
lib[4][1][2] = 1;
lib[4][3][2] = 1;
lib[4][0][3] = 1;
lib[4][3][3] = 1;
lib[4][0][4] = 1;
lib[4][1][4] = 1;
lib[4][2][4] = 1;
lib[4][3][4] = 1;
lib[4][4][4] = 1;
lib[4][3][5] = 1;
lib[4][3][6] = 1;
lib[5][0][0] = 1;
lib[5][1][0] = 1;
lib[5][2][0] = 1;
lib[5][3][0] = 1;
lib[5][4][0] = 1;
lib[5][0][1] = 1;
lib[5][0][2] = 1;
lib[5][1][2] = 1;
lib[5][2][2] = 1;
lib[5][3][2] = 1;
lib[5][4][3] = 1;
lib[5][4][4] = 1;
lib[5][0][5] = 1;
lib[5][4][5] = 1;
lib[5][1][6] = 1;
lib[5][2][6] = 1;
lib[5][3][6] = 1;
lib[6][2][0] = 1;
lib[6][3][0] = 1;
lib[6][1][1] = 1;
lib[6][0][2] = 1;
lib[6][0][3] = 1;
lib[6][1][3] = 1;
lib[6][2][3] = 1;
lib[6][3][3] = 1;
lib[6][0][4] = 1;
lib[6][4][4] = 1;
lib[6][0][5] = 1;
lib[6][4][5] = 1;
lib[6][1][6] = 1;
lib[6][2][6] = 1;
lib[6][3][6] = 1;
lib[7][0][0] = 1;
lib[7][1][0] = 1;
lib[7][2][0] = 1;
lib[7][3][0] = 1;
lib[7][4][0] = 1;
lib[7][4][1] = 1;
lib[7][3][2] = 1;
lib[7][2][3] = 1;
lib[7][1][4] = 1;
lib[7][1][5] = 1;
lib[7][1][6] = 1;
lib[8][1][0] = 1;
lib[8][2][0] = 1;
lib[8][3][0] = 1;
lib[8][0][1] = 1;
lib[8][4][1] = 1;
lib[8][0][2] = 1;
lib[8][4][2] = 1;
lib[8][1][3] = 1;
lib[8][2][3] = 1;
lib[8][3][3] = 1;
lib[8][0][4] = 1;
lib[8][4][4] = 1;
lib[8][0][5] = 1;
lib[8][4][5] = 1;
lib[8][1][6] = 1;
lib[8][2][6] = 1;
lib[8][3][6] = 1;
lib[9][1][0] = 1;
lib[9][2][0] = 1;
lib[9][3][0] = 1;
lib[9][0][1] = 1;
lib[9][4][1] = 1;
lib[9][0][2] = 1;
lib[9][4][2] = 1;
lib[9][1][3] = 1;
lib[9][2][3] = 1;
lib[9][3][3] = 1;
lib[9][4][3] = 1;
lib[9][4][4] = 1;
lib[9][3][5] = 1;
lib[9][1][6] = 1;
lib[9][2][6] = 1;

  int seed =
  (analogRead(0)+1)*
  (analogRead(1)+1)*
  (analogRead(2)+1)*
  (analogRead(3)+1);
  randomSeed(seed);
  random(10,9610806);
  seed = seed *random(3336,15679912)+analogRead(random(4)) ;
  randomSeed(seed);
  random(10,98046);

  tetris_start();
}

void tetris_start() {
  lines = 0;
  is_gameover = 0;
  memset(block, 0, sizeof(block));
  memset(pile, 0, sizeof(pile));
  memset(disp, 0, sizeof(disp));
  blocktype = random(7);
  newBlock();
  RefreshDisplay();
  delays = millis() + delay_;
}

void tetris_loop() {

  //buttun actions
  int button = readBut();

  if (is_gameover) {
    if (button == 10 || delays < millis()) {
      tetris_start();
    }
    return;
  }

  if (delays < millis() && !paused)
   {
     delays = millis() + delay_;
     movedown();
   }

  if (button == 1) //up=rotate
    rotate();
  if (button == 2) //right=moveright
    moveright();
  if (button == 3) //left=moveleft
    moveleft();
  if (button == 4) //down=movedown
    movedown();
  if (button == 10) // pause=togglepause
    togglepause();
}

void togglepause()
{
  paused = !paused;
}

boolean moveleft()
{
  Serial.println("moveleft()");
  if (space_left())
  {
    int i;
    int j;
    for (i=0;i<(TETRIS_WIDTH-1);i++)
    {
      for (j=0;j<TETRIS_HEIGHT;j++)
      {
        block[i][j]=block[i+1][j];
      }
    }

    for (j=0;j<TETRIS_HEIGHT;j++)
    {
      block[TETRIS_WIDTH-1][j]=0;
    }

    updateLED();
    RefreshDisplay();
    return 1;
  }

  return 0;
}

boolean moveright()
{
  Serial.println("moveright()");
  if (space_right())
  {
    int i;
    int j;
    for (i=(TETRIS_WIDTH-1);i>0;i--)
    {
      for (j=0;j<TETRIS_HEIGHT;j++)
      {
        block[i][j]=block[i-1][j];
      }
    }

    for (j=0;j<TETRIS_HEIGHT;j++)
    {
      block[0][j]=0;
    }

   updateLED();
   RefreshDisplay();
   return 1;

  }
  return 0;
}

int readBut()
{
  if (Serial.available() == 0) {
    return 0;
  }

  if (bdelay > millis())
  {
    while(Serial.available()){
      Serial.read();
    }
    return 0;
  }

  int c = Serial.read();

  if (c == 'a')
  {
    //left
    bdelay = millis() + btsidedelay;
    return 3;
  }

  if (c == 's')
  {
    //down
    bdelay = millis() + btdowndelay;
    return 4;
  }
  if (c == 'd')
  {
    //right
    bdelay = millis() + btsidedelay;
    return 2;
  }
  if (c == 'w')
  {
    //up
    bdelay = millis() + buttondelay;
    return 1;
  }

  if (c == 'p')
  {
    //pause
    bdelay = millis() + buttondelay;
    return 10;
  }

  return 0;
}

void updateLED()
{
  int i;
  int j;
  for (i=0;i<TETRIS_WIDTH;i++)
  {
    for (j=0;j<TETRIS_HEIGHT;j++)
    {
      disp[i][j] = block[i][j] | pile[i][j];
    }
  }
  updated = 1;
}

void rotate()
{
  Serial.println("rotate()");
  //skip for square block(3)
  if (blocktype == 3) return;

  int xi;
  int yi;
  int i;
  int j;
  //detect left
  for (i=TETRIS_WIDTH-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_HEIGHT;j++)
    {
      if (block[i][j])
      {
        xi = i;
      }
    }
  }

  //detect up
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
      if (block[j][i])
      {
        yi = i;
      }
    }
  }

  if (blocktype == 0)
  {
    if (blockrotation == 0)
    {


      if (!space_left())
      {
        if (space_right3())
        {
          if (!moveright())
            return;
          xi++;
        }
        else return;
      }
      else if (!space_right())
      {
        if (space_left3())
        {
          if (!moveleft())
            return;
          if (!moveleft())
            return;
          xi--;
          xi--;
        }
        else
          return;
      }
      else if (!space_right2())
      {
        if (space_left2())
        {
          if (!moveleft())
            return;
          xi--;
        }
        else
          return;
      }





      block[xi][yi]=0;
      block[xi][yi+2]=0;
      block[xi][yi+3]=0;

      block[xi-1][yi+1]=1;
      block[xi+1][yi+1]=1;
      block[xi+2][yi+1]=1;

      blockrotation = 1;
    }
    else
    {
      block[xi][yi]=0;
      block[xi+2][yi]=0;
      block[xi+3][yi]=0;

      block[xi+1][yi-1]=1;
      block[xi+1][yi+1]=1;
      block[xi+1][yi+2]=1;

      blockrotation = 0;
    }
  }

  //offset to mid
  xi ++;
  yi ++;

  if (blocktype == 1)
  {
    if (blockrotation == 0)
    {
      block[xi-1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi-1] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }
      xi--;

      block[xi][yi-1] = 0;
      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;

      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi+1][yi+1] = 1;

      blockrotation = 2;
    }
    else if (blockrotation == 2)
    {
      yi --;

      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;

      block[xi][yi-1] = 1;
      block[xi][yi+1] = 1;
      block[xi-1][yi+1] = 1;

      blockrotation = 3;
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi+1] = 0;

      block[xi-1][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;

      blockrotation = 0;
    }
  }



  if (blocktype == 2)
  {
    if (blockrotation == 0)
    {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi+1] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }
      xi--;

      block[xi][yi-1] = 0;
      block[xi+1][yi+1] = 0;
      block[xi][yi+1] = 0;

      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi-1][yi+1] = 1;

      blockrotation = 2;
    }
    else if (blockrotation == 2)
    {
      yi --;

      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi-1][yi+1] = 0;

      block[xi][yi-1] = 1;
      block[xi][yi+1] = 1;
      block[xi-1][yi-1] = 1;

      blockrotation = 3;
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi-1] = 0;

      block[xi+1][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;

      blockrotation = 0;
    }
  }

  if (blocktype == 4)
  {
    if (blockrotation == 0)
    {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;

      block[xi+1][yi] = 1;
      block[xi+1][yi+1] = 1;

      blockrotation = 1;
    }
    else
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }
      xi--;

      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;

      block[xi-1][yi] = 1;
      block[xi+1][yi-1] = 1;

      blockrotation = 0;
    }
  }


  if (blocktype == 5)
  {
    if (blockrotation == 0)
    {
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] = 1;
      block[xi+1][yi] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 1;
    }
    else if (blockrotation == 1)
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }
      xi--;

      block[xi][yi-1] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;

      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 2;
    }
    else if (blockrotation == 2)
    {
      yi --;

      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;

      block[xi][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 3;
    }
    else
    {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi][yi+1] = 0;

      block[xi][yi-1] = 1;
      block[xi-1][yi] = 1;
      block[xi+1][yi] = 1;

      blockrotation = 0;
    }
  }

  if (blocktype == 6)
  {
    if (blockrotation == 0)
    {
      block[xi-1][yi-1] = 0;
      block[xi][yi-1] = 0;

      block[xi+1][yi-1] = 1;
      block[xi][yi+1] = 1;

      blockrotation = 1;
    }
    else
    {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }
      xi--;

      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;

      block[xi-1][yi-1] = 1;
      block[xi][yi-1] = 1;

      blockrotation = 0;
    }
  }

  //if rotating made block and pile overlap, push rows up
  while (!check_overlap())
  {
    for (i=0;i<TETRIS_HEIGHT+2;i++)
    {
      for (j=0;j<TETRIS_WIDTH;j++)
      {
         block[j][i] = block[j][i+1];
      }
    }
    delays = millis() + delay_;
  }


  updateLED();
  RefreshDisplay();
}

void movedown()
{
  Serial.println("movedown()");
  if (space_below())
  {
    //move down
    int i;
    for (i=TETRIS_HEIGHT-1;i>=0;i--)
    {
      int j;
      for (j=0;j<TETRIS_WIDTH;j++)
      {
        block[j][i] = block[j][i-1];
      }
    }
    for (i=0;i<TETRIS_WIDTH-1;i++)
    {
      block[i][0] = 0;
    }
  }
  else
  {
    //merge and new block
    int i;
    int j;
    for (i=0;i<TETRIS_WIDTH;i++)
    {
     for(j=0;j<TETRIS_HEIGHT;j++)
     {
       if (block[i][j])
       {
         pile[i][j]=1;
         block[i][j]=0;
       }
     }
    }
    newBlock();
  }
  updateLED();
  RefreshDisplay();
}

boolean check_overlap()
{
  int i;
  int j;
  for (i=0;i<TETRIS_HEIGHT;i++)
  {
    for (j=0;j<TETRIS_WIDTH-1;j++)
    {
       if (block[j][i])
       {
         if (pile[j][i])
           return false;
       }
    }
  }
  for (i=TETRIS_HEIGHT;i<TETRIS_HEIGHT+2;i++)
  {
    for (j=0;j<TETRIS_WIDTH-1;j++)
    {
       if (block[j][i])
       {
         return false;
       }
    }
  }
  return true;
}

bool check_gameover()
{
  int i;
  int j;
  int cnt=0;;

  for(i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    cnt=0;
    for (j=0;j<TETRIS_WIDTH;j++)
    {
      if (pile[j][i])
      {
        cnt ++;
      }
    }
    if (cnt == TETRIS_WIDTH)
    {
        lines++;
      for (j=0;j<TETRIS_WIDTH;j++)
      {
        pile[j][i]=0;
      }
      updateLED();
      RefreshDisplay();
      delay(50);

      int k;
      for(k=i;k>0;k--)
      {
        for (j=0;j<TETRIS_WIDTH;j++)
        {
          pile[j][k] = pile[j][k-1];
        }
      }
      for (j=0;j<TETRIS_WIDTH;j++)
      {
        pile[j][0] = 0;
      }
      updateLED();
      RefreshDisplay();
      delay(50);
      i++;
    }
  }


  for(i=0;i<TETRIS_WIDTH;i++)
  {
    if (pile[i][0]){
      gameover();
      return true;
    }
  }
  return false;
}

void gameover()
{
  Serial.println("gameover()");
  int i;
  int j;

  //close blind
  for (i=0;i<TETRIS_WIDTH;i++)
  {
     for (j=0;j<TETRIS_HEIGHT;j++)
     {
       if (j%2)
       {
         disp[i][j]=1;
       }
       else
       {
         disp[7-i][j]=1;
       }
     }
     delay(60);
  }
}

void copyBlock(uint8_t type, boolean  dest[TETRIS_WIDTH][TETRIS_HEIGHT+2]){

}

void newBlock()
{
  Serial.println("newBlock()");
  if(check_gameover()){
    is_gameover = 1;
    delays = millis() + 10000;
    return;
  }

  for(uint8_t x=0; x<3; x++){
    for(uint8_t y=0; y<4; y++){
      block[x+2][y] = blockpatterns[blocktype][y][x];
    }
  }

  blockrotation = 0;

  // Update next blocktype
  blocktype = random(7);
}

boolean space_below()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (i == TETRIS_HEIGHT-1)
           return false;
         if (pile[j][i+1])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_left2()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1)
           return false;
         if (pile[j-1][i] | pile[j-2][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_left3()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1 ||j == 2 )
           return false;
         if (pile[j-1][i] | pile[j-2][i]|pile[j-3][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_left()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == 0)
           return false;
         if (pile[j-1][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_right()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == TETRIS_WIDTH-1)
           return false;
         if (pile[j+1][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_right3()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == TETRIS_WIDTH-1||j == TETRIS_WIDTH-2||j == TETRIS_WIDTH-3)
           return false;
         if (pile[j+1][i] |pile[j+2][i] | pile[j+3][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}

boolean space_right2()
{
  int i;
  int j;
  for (i=TETRIS_HEIGHT-1;i>=0;i--)
  {
    for (j=0;j<TETRIS_WIDTH;j++)
    {
       if (block[j][i])
       {
         if (j == TETRIS_WIDTH-1 || j == TETRIS_WIDTH-2)
           return false;
         if (pile[j+1][i] |pile[j+2][i])
         {
           return false;
         }
       }
    }
  }
  return true;
}



void RefreshDisplay()
{

    if(updated == 0) return;
    updated = 0;
    int i;
    int k;
    for (k=0;k<TETRIS_HEIGHT;k++)
    {
      for(i=0;i<TETRIS_WIDTH;i++)
      {

        if(disp[i][k]){
          // flipdot.drawPixel(k, 6-i, FLIPDOT_YELLOW);
          flipdot.drawPixel(i, k, FLIPDOT_YELLOW);
        }else{
          // flipdot.drawPixel(k, 6-i, FLIPDOT_BLACK);
          flipdot.drawPixel(i, k, FLIPDOT_BLACK);
        }
      }
    }
    flipdot.display();

}
