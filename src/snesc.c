int release = 0;  // release mode or test mode



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

int tick = 0;
int current_sprite;

int bed_sprite_start = -1;
int bed_sprite_end = -1;

void bed_animation(bed_x, bed_y, is_idling) {
  if (bed_sprite_start == -1)
  {
    bed_sprite_start = current_sprite;
  }

  // create sheet
  int i = 0, x, y;
  int current_bed_sprite = 0;
  
  for(y = 0; y < 3; y++)
    for(x = 0; x < 8; x++)
    {
        if (x % 2)
          setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y*5), 18, 0x31);
        else
          setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y*5) - 1, 18, 0x31);
        current_bed_sprite++;
    }

  // breathing sheet
  if (tick % 2)
    setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + 1, 18, 0x31);
  else
    setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + - 1, 18, 0x31);
  current_bed_sprite++;

  for (y=1; y < 2; y++)
  {
    setsprite(bed_sprite_start + current_bed_sprite, bed_x + (x * 5), bed_y + (y * 5), 18, 0x31);
    current_bed_sprite++;
  }
  x += 1;
  
  // head
  int head_position_x = bed_x + (x * 5) + 3;
  setsprite(bed_sprite_start + current_bed_sprite, head_position_x, bed_y + 1, 17, 0x31);
  current_bed_sprite++;
  
  // moving Z
  setsprite(bed_sprite_start + current_bed_sprite, head_position_x + 10 + (tick % 4), bed_y - 20, 80, 0x31);
  current_bed_sprite++;
  setsprite(bed_sprite_start + current_bed_sprite, head_position_x + 10 - (tick % 4) - 3, bed_y - 14, 80, 0x31);
  current_bed_sprite++;
  
  if (is_idling)
  {
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
int mouse_speed = 1;
int mouse_sprite[2] = {-1, -1};

void mouse_stage()
{
  if ((getjoystatus(0) & RIGHT_BUTTON) != 0) mouse_x += mouse_speed;
  if ((getjoystatus(0) & LEFT_BUTTON) != 0) mouse_x -= mouse_speed;
  if ((getjoystatus(0) & UP_BUTTON) != 0) mouse_y -= mouse_speed;
  if ((getjoystatus(0) & DOWN_BUTTON) != 0) mouse_y += mouse_speed;

  //initialize mouse sprite
  if (mouse_sprite[0] == -1) 
    mouse_sprite[0] = current_sprite++;
  if (mouse_sprite[1] == -1) 
    mouse_sprite[1] = current_sprite++;

  setsprite(mouse_sprite[0], mouse_x + 3, mouse_y, 120, 0x31);
  if ((getjoystatus(0) & A_BUTTON) != 0)
    setsprite(mouse_sprite[0], mouse_x + 2, mouse_y + 1, 120, 0x31);
  setsprite(mouse_sprite[1], mouse_x + 3, mouse_y + 5, 121, 0x31);
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
  tick += 1;
  clearjoy(0);
  delay(1);
  
  if (release == 0)
    bed_y = 60;

  bed_animation(bed_x, bed_y, 0);
  bed_y -= 1;

  if (bed_y <= 60)
    return;
  goto bed_animation_transition;
}

void start_mouse_stage()
{
}

int main() {
  snesc_init();

  //settiles(0, tiles1, 0xF00 + (16*3) );
  settiles(0, tiles1, 0xFFF );
  settiles(1, tiles2, 0x250);
  
  memcpy(pal, palette, 0x200);
  setmap(0, (unsigned char*)blockmap);
  setpalette((unsigned char*)pal);

  GameTitle();

  unsigned char map[] = 
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
 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
 };
  
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
      blockmap[pos+x] = map[i++];
    }
  }
  
  setmap(0, (unsigned char*)blockmap);
  //setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);

stage1:
  tick += 1;
  clearjoy(0);
  delay(1);

  mouse_stage();
    
  goto stage1;

  //sync(1);
}
