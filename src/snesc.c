int release = 1;  // release mode or test mode
 unsigned char background1[] = {
0,19,18,19,20,20,20,18,20,19,18,20,19,20,18,20,20,20,19,0,
18,20,19,19,19,20,18,19,18,19,19,18,20,18,19,18,20,19,19,20,
20,18,18,20,18,20,19,19,20,19,20,20,18,18,20,19,19,18,19,18,
20,18,18,20,18,20,19,19,20,19,20,20,18,18,20,19,19,18,19,18,
18,20,19,19,20,19,18,20,19,20,19,19,19,19,18,18,19,18,19,19,
20,20,20,20,20,19,19,20,19,18,20,18,18,19,19,20,19,19,18,20,
20,19,19,19,19,18,19,19,18,19,18,18,19,20,18,20,20,19,19,19,
18,20,20,19,20,20,20,20,19,20,20,18,19,18,19,20,18,20,20,19,
18,18,18,20,18,19,19,19,18,18,19,20,20,18,18,20,19,18,18,19,
20,20,20,20,19,19,18,18,19,20,18,19,19,19,19,19,20,18,19,18,
0,19,19,18,18,18,20,20,20,20,20,20,20,19,19,19,19,18,19,0,
 //1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
 };
   
   unsigned char background2[] = {
9,12,10,9,11,9,10,9,12,9,9,9,10,12,10,12,11,8,12,11,
11,8,8,11,10,10,9,10,10,11,9,11,8,11,12,8,12,9,9,12,
10,11,12,8,11,11,9,12,8,9,9,11,12,10,11,8,8,9,12,8,
9,12,9,11,9,8,12,9,12,11,8,11,10,8,10,10,9,12,12,10,
9,9,10,12,12,8,11,12,8,8,10,10,12,11,8,9,10,11,8,8,
11,10,10,12,8,12,11,12,10,9,8,10,8,9,8,10,10,10,8,11,
8,8,11,11,9,12,8,11,8,10,8,11,12,10,12,11,11,12,12,8,
10,10,8,11,10,8,11,12,9,9,12,8,8,11,11,11,12,8,11,8,
8,8,11,10,11,12,8,11,9,8,12,10,8,9,10,11,12,10,12,8,
8,8,12,8,9,12,12,9,12,8,12,11,11,11,12,11,9,10,12,9,
8,8,10,10,10,12,9,9,8,9,8,10,12,10,12,8,11,12,9,12
};

   unsigned char background3[] = {
5,8,3,4,5,8,7,3,7,7,2,7,6,6,1,2,7,2,4,8,
2,7,3,7,5,1,8,7,3,3,6,4,8,3,6,7,4,1,8,1,
4,6,4,7,4,4,7,2,3,1,7,6,5,7,6,8,2,2,4,3,
5,6,3,1,3,4,6,2,2,8,3,1,2,4,2,5,2,3,1,5,
4,4,5,7,1,6,3,6,3,2,1,3,2,4,8,8,8,4,2,8,
7,3,2,8,8,1,8,3,4,8,5,3,6,8,3,2,8,5,5,1,
8,6,6,5,6,2,8,7,2,1,3,2,3,7,5,6,6,6,5,7,
6,6,1,5,6,7,1,4,2,4,5,1,2,4,1,6,8,2,2,8,
1,3,1,3,3,5,5,3,2,1,1,7,2,6,2,7,6,3,5,5,
1,3,2,2,7,1,1,7,2,5,2,3,3,1,6,6,2,3,4,6,
4,7,3,8,4,3,4,1,2,3,7,3,6,3,4,5,2,7,1,7
};

  unsigned char padd_map[] = 
{1,2,2,2,2,2,3,4,4,4,4,4,5,2,2,2,2,2,2,7,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,     // y=10
 8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,
 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
// 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
 };



#include <string.h>
#include "snesc.h"

#define OUTLIT(x) (*((char*)0xfffe) = (x))
void write(char* s) {
  while(*s) OUTLIT(*s++);
}

extern unsigned char tiles1[];
extern unsigned char tiles2[];
extern unsigned char bg1map[];
extern unsigned char bg2map[];
extern unsigned char palette[];
extern unsigned char backpal[];

unsigned int blockmap[0x400];
unsigned int backmap[0x400];
unsigned int pal[0x100];

int tick = 299210;
int current_sprite;

int bed_sprite_start = -1;
int bed_sprite_end = -1;
int sheet_sprite = -1;
int head_sprite = -1;
int head_position_x = -1;
int head_position_y = -1;

void bed_animation(bed_x, bed_y, is_idling) {
  if (bed_sprite_start == -1)
  {
    bed_sprite_start = current_sprite;
  }

  // create sheet
  int i = 0, x, y;
  int current_bed_sprite = 0;
  
  for(y = 0; y < 3; y++)
    for(x = 0; x < 5; x++)
    {
        if (x % 2)
          setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y*5), 18, 0x31);
        else
          setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y*5) - 1, 18, 0x31);
        current_bed_sprite++;
    }

  // breathing sheet
  sheet_sprite = bed_sprite_start + current_bed_sprite;
  if (tick % 2)
    setsprite(sheet_sprite, bed_x + (x * 5), bed_y + 0, 18, 0x31);
  else
    setsprite(sheet_sprite, bed_x + (x * 5), bed_y - 2, 18, 0x31);
  current_bed_sprite++;

  for (y=1; y < 2; y++)
  {
    setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y * 5), 18, 0x31);
    current_bed_sprite++;
  }
  x += 1;
  
  // head
  head_position_x = bed_x + (x * 5) + 3;
  head_position_y =  bed_y + 1;
  head_sprite = bed_sprite_start + current_bed_sprite;
  setsprite(head_sprite, head_position_x, head_position_y , 17, 0x31);
  current_bed_sprite++;
  
  // moving Z
  if (is_idling)
  {
    setsprite(bed_sprite_start + current_bed_sprite, head_position_x + 10 + (tick % 4), bed_y - 20, 80, 0x11);
    current_bed_sprite++;
    setsprite(bed_sprite_start + current_bed_sprite, head_position_x + 10 - (tick % 4) - 3, bed_y - 14, 80, 0x11);
    current_bed_sprite++;
  
    if (tick % 2)
      delay(30);
    else
      delay(50);
  }
  
  if (bed_sprite_end == -1)
  {
    bed_sprite_end = bed_sprite_start + current_bed_sprite;
    current_sprite = bed_sprite_end;
  }
}

void clearblockmap() {
  int i;
  for (i = 0x20; i < 0x400; i++)
  {
    writestring(" ", blockmap, i, 0x3F6);
  }
  setmap(0, (unsigned char*)blockmap);
}

int mouse_x = 400;
int mouse_y = 400;
int mouse_sprite[2] = {-1, -1};
int mouse_down = 0;
void check_collision();

void mouse_stage()
{
  int speed;
  if ((getjoystatus(0) & X_BUTTON) == 0)
    speed = 3;
  else
    speed = 7;
    
  if ((getjoystatus(0) & RIGHT_BUTTON) != 0) mouse_x += speed;
  if ((getjoystatus(0) & LEFT_BUTTON) != 0) mouse_x -= speed;
  if ((getjoystatus(0) & UP_BUTTON) != 0) mouse_y -= speed;
  if ((getjoystatus(0) & DOWN_BUTTON) != 0) mouse_y += speed;

  //initialize mouse sprite
  if (mouse_sprite[0] == -1) 
    mouse_sprite[0] = current_sprite++;
  if (mouse_sprite[1] == -1) 
    mouse_sprite[1] = current_sprite++;

  if (mouse_x < 305) mouse_x = 305;
  if (mouse_x > 450) mouse_x = 450;
  if (mouse_y < 355) mouse_y = 355;
  if (mouse_y > 435) mouse_y = 435;

  setsprite(mouse_sprite[1], mouse_x + 3, mouse_y + 5, 121, 0x31);

  setsprite(mouse_sprite[0], mouse_x + 3, mouse_y, 120, 0x31);
  if ((getjoystatus(0) & A_BUTTON) != 0)
  {
    setsprite(mouse_sprite[0], mouse_x + 2, mouse_y + 1, 120, 0x31);
    check_collision();
  }
  
  if (getjoystatus(0) & A_BUTTON != 0)
    mouse_down = 1;
  else
    mouse_down = 0;
}

void GameTitle()
{
  writestring("TEAM SONY", blockmap, 0x084, 0x3F6);
  writestring("presents", blockmap, 0x0A7, 0x3F6);
  writestring("A NINTENDO GAME", blockmap, 0x169, 0x3F6);
  writestring("developed at", blockmap, 0x250, 0x3F6);
  writestring("MICROSOFT PHILIPPINES", blockmap, 0x288, 0x3F6);

  enablescreen();
  resettimer();
  //while (getjoystatus(0) == 0) continue;
  if (release){
    delay(60 * 5);
    clearjoy(0);
  }
  clearblockmap();

  writestring("DAILY RITUAL", blockmap, 0x06A, 0x3F6);

  int bed_x = 90;
  int bed_y = 130;
  current_sprite = 0;

start_menu:
  bed_animation(bed_x, bed_y, 1);

  if ((getjoystatus(0) & UP_BUTTON) != 0 ||
      (getjoystatus(0) & START_BUTTON) != 0 ||
      release == 0)
  {
    clearblockmap();
    goto bed_animation_transition;
  }

  tick += 3;
  clearjoy(0);
  delay(3);
  goto start_menu;
  
bed_animation_transition:
  current_sprite = bed_sprite_end - 2;  // remove the two Zs
  setsprite(current_sprite, 0,0,0, 0x11);
  setsprite(current_sprite+1, 0,0,0, 0x11);
  

  tick += 1;
  clearjoy(0);
  delay(1);
  
  if (release == 0)
    bed_y = 60;

  bed_animation(bed_x, bed_y, 0);
  bed_y -= 1;

  if (bed_y <= 60)
  {
  
  // move head
    setsprite(head_sprite, head_position_x, head_position_y - 10, 0, 0x31);
    setsprite(sheet_sprite, head_position_x, head_position_y - 10, 0, 0x31);
    setsprite(current_sprite++, head_position_x, head_position_y - 10, 127, 0x31);
    setsprite(current_sprite++, head_position_x - 10, head_position_y - 10, 126, 0x31);
    setsprite(current_sprite++, head_position_x, head_position_y , 128, 0x31);
    setsprite(current_sprite++, head_position_x - 10, head_position_y , 129, 0x31);
    return;
  }
  goto bed_animation_transition;
}

int prev_rand = 1;
int random(min, max)
{
  tick++;
  int r = min + ((tick * prev_rand) % (max - min));
  prev_rand = r % 1024;
  return r;
}

int random_x()
{
  // returns a random number between the tablet width
  // range: 305 - 450 
  // padding: 12
  return random(305 + 12, 450 - 12);
}

int random_y()
{
  // returns a random number between the tablet height
  // range: 355 - 435 
  // padding: 12
  return random(355 + 12, 435 - 12);  
}

void start_mouse_stage()
{
}

int clickables_left[6], clickables_right[6];
int clickables_x[12], clickables_y[12];
int energy = 20;
int dog_energy_icon;

void draw_dogg()
{
  int i;
  for (i = 0; i < 6; i++)
  {
    int sprite = clickables_left[i];
    setsprite(sprite+0, clickables_x[i] - 0, clickables_y[i] - 0, 122, 0x11 + 64);
    setsprite(sprite+1, clickables_x[i] - 8, clickables_y[i] - 0, 123, 0x11 + 64);
    setsprite(sprite+2, clickables_x[i] - 0, clickables_y[i] + 8, 124, 0x11 + 64);
    setsprite(sprite+3, clickables_x[i] - 8, clickables_y[i] + 8, 125, 0x11 + 64);
  }

  for (i = 0; i < 6; i++)
  {
    int sprite = clickables_right[i];
    setsprite(sprite+0, clickables_x[i + 6] + 0, clickables_y[i + 6] + 0, 122, 0x11 );
    setsprite(sprite+1, clickables_x[i + 6] + 8, clickables_y[i + 6] + 0, 123, 0x11 );
    setsprite(sprite+2, clickables_x[i + 6] + 0, clickables_y[i + 6] + 8, 124, 0x11 );
    setsprite(sprite+3, clickables_x[i + 6] + 8, clickables_y[i + 6] + 8, 125, 0x11 );
  }
}

void check_collision()
{
  int i;

  if (mouse_down == 0)
    for (i = 0; i < 6; i++)
    {
      if (clickables_x[i] + 16 > mouse_x &&
          clickables_x[i] < mouse_x + 8 &&
          clickables_y[i] + 16 > mouse_y &&
          clickables_y[i] < mouse_y + 8)
      {
          energy += 2;
          if (random(1, 2) == 1)
            clickables_x[i] -= 5;
          else
            clickables_x[i] += 5;
          if (random(1, 2) == 1)
            clickables_y[i] -= 5;
          else
            clickables_y[i] += 5;

          break;
      }
    }
}

int main() {
  snesc_init();

  //settiles(0, tiles1, 0xF00 + (16*3) );
  settiles(0, tiles1, 0x10FF);
  settiles(1, tiles2, 0x250);
  
  memcpy(pal, palette, 0x200);
  setmap(0, (unsigned char*)blockmap);
  setpalette((unsigned char*)pal);

  GameTitle();

// map:
  //memcpy(blockmap, bg1map, 0x800);
  //memcpy(backmap, bg2map, 0x800);
  //memcpy(blocks, map, 0x64);
  memcpy(pal, palette, 0x200);

  unsigned int y, x, i=0;  
  //int start_y = 0x1F2;  //498
  unsigned int start_y = 390;
  
  for (y=0; y<12; y++) {
    unsigned long pos = start_y + (y<<5);
    for (x=0; x<20; x+=1) {
      blockmap[pos+x] = padd_map[i];
      backmap[pos+x] = background1[i];
      
      //color
      blockmap[pos+x] += 0x400 * 0;
      backmap[pos+x] += 0x400 * 2;
      
      i++;
    }
  }
  
  setmap(0, (unsigned char*)blockmap);
  setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);
  writestring("Starting PADD  ", blockmap, 779, 0x3F6);

  if (release == 1) delay(130);

 for (y=0; y<12; y++) {
    unsigned long pos = start_y + (y<<5);
    for (x=0; x<20; x+=1) {
      backmap[pos+x] -= 0x400 * 1;
    }
  }
  setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);
  writestring("Loading BARRKER (tm)", blockmap, 774, 0x3F6);
  
// dog energy icon
  x = 180;
  y = 200;
  dog_energy_icon = current_sprite;
  setsprite(current_sprite++, x - 0, y - 0, 122, 0x11 + 64);
  setsprite(current_sprite++, x - 8, y - 0, 123, 0x11 + 64);
  setsprite(current_sprite++, x - 0, y + 8, 124, 0x11 + 64);
  setsprite(current_sprite++, x - 8, y + 8, 125, 0x11 + 64);
  setmap(0, (unsigned char*)blockmap);
  
    
  if (release == 1) {
    sync(1);
    delay(160);
  }
  writestring(" REBARK the BARRKS! ", blockmap, 774, 0x3F6);

// dog energy icon
  x = 170;
  y = 60;
  current_sprite = dog_energy_icon;
  setsprite(current_sprite++, x - 0, y - 0, 122, 0x11 + 64);
  setsprite(current_sprite++, x - 8, y - 0, 123, 0x11 + 64);
  setsprite(current_sprite++, x - 0, y + 8, 124, 0x11 + 64);
  setsprite(current_sprite++, x - 8, y + 8, 125, 0x11 + 64);

//stage1_load:
  mouse_stage();

  for (i = 0; i < 12; i++)
  {
    clickables_x[i] = random_x();
    clickables_y[i] = random_y();
  }

  for (i = 0; i < 6; i++)
  {
    clickables_left[i] = current_sprite;
    current_sprite += 4;
    clickables_right[i] = current_sprite;
    current_sprite += 4;
  }
  
stage1:
  draw_dogg();

  int r, speed;
  for (i = 0; i < 12; i++)
  {
    r = random(0, 2);
    speed = random(-2,4);
    if (r == 0)
      clickables_x[i] += speed;
    else
      clickables_x[i] -= speed;
      
    r = random(0, 2);
    speed = random(-1,2);
    if (r == 0)
      clickables_y[i] += speed;
    else
      clickables_y[i] -= speed;
    
  // range: 305 - 450 
  // padding: 12
  // range: 355 - 435   
    while (clickables_x[i] < 305 || clickables_x[i] > 448)
      clickables_x[i] = random_x();
    while (clickables_y[i] < 355 || clickables_y[i] > 435)
      clickables_y[i] = random_y();
  }

  tick += 3;
  clearjoy(0);
  delay(1);

  mouse_stage();

  //writenum(current_sprite, 8, blockmap, 0x136, 0x426);
  writestring("Energy x ", blockmap, 0x0B2, 0x3F6);
  if (tick % 60 == 0)
    energy -= 3;
  if (tick % 70 == 0)
    energy -= 2;
    
  if (energy <= -10)
    energy = -9;
    
  if (energy > 0)
  {
    writestring("  ", blockmap, 0x117, 0x3F6);
    writenum(energy, 8, blockmap, 0x112, 0x426);
  }
  else
  {
    writestring(" -", blockmap, 0x117, 0x3F6);
    writenum(energy * -1, 8, blockmap, 0x112, 0x426);
  }
  setmap(0, (unsigned char*)blockmap);

  if (energy > 105) goto victory;
  if (energy < 2) goto lost;
  
  goto stage1;
  //sync(1);

victory:
  clearblockmap();
  unsigned int start_y = 390;
i=0;  
  for (y=0; y<12; y++) {
    unsigned long pos = start_y + (y<<5);
    for (x=0; x<20; x+=1) {
      blockmap[pos+x] = padd_map[i];
      backmap[pos+x] = background1[i];
      
      //color
      blockmap[pos+x] += 0x400 * 0;
      backmap[pos+x] += 0x400 * 4;
      
      i++;
    }
  }
  
  setmap(0, (unsigned char*)blockmap);
  setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);
  for (i = 0; i < current_sprite; i++)
    setsprite(i, 0, 0, 0, 0x31);

  writestring("           ", blockmap, 0x0B2, 0x3F6);
  writestring("                      ", blockmap, 774, 0x3F6);
  writestring("       ", blockmap, 0x117, 0x3F6);
  
  writestring("Congratulations!\n You are now awake!", blockmap, 0x084, 0x3F6);
  writestring("Have a good day!", blockmap, 0x104, 0x3F6);
  writestring("Thank you for playing!", blockmap, 0x245, 0x3F6);
  setmap(0, (unsigned char*)blockmap);
  goto endloop;
  
lost:
  clearblockmap();
  for (i = 0; i < current_sprite; i++)
    setsprite(i, 0, 0, 0, 0x31);

  writestring("           ", blockmap, 0x0B2, 0x3F6);
  writestring("                      ", blockmap, 774, 0x3F6);
  writestring("       ", blockmap, 0x117, 0x3F6);
  
  writestring("Oh noes! You spent too much time on Barrker.", blockmap, 0x084, 0x3F6);
  writestring("Maybe its time to switch to another social media?", blockmap, 0x0E4, 0x3F6);
  writestring("To be continued in\n\n  Morning Ritual 2:\n  RaceBook", blockmap, 0x207, 0x3F6);
  setmap(0, (unsigned char*)blockmap);
  goto endloop;

endloop:

  sync(1);
  goto endloop;
}
