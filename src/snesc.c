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
unsigned char blocks[0x64], map[0x64] = 
{1,1,1,1,1,1,1,1,1,1,
 8,7,8,7,8,8,7,8,7,8,
 8,8,7,8,7,7,8,7,8,8,
 8,8,8,1,3,3,1,8,8,8,
 8,0,4,8,8,8,8,4,0,8,
 8,0,8,8,5,5,8,8,0,8,
 8,0,4,8,8,8,8,4,0,8,
 8,8,8,1,3,3,1,8,8,8,
 8,8,6,8,6,6,8,6,8,8,
 1,1,1,1,1,1,1,1,1,1};

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

int mouse_x = 450;
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
start_menu:
  current_sprite = 0;

  bed_animation(bed_x, bed_y, 1);

  if ((getjoystatus(0) & UP_BUTTON) != 0 ||
      (getjoystatus(0) & START_BUTTON) != 0 ||
      release == 0)
  {
    clearblockmap();
    current_sprite -= 2;  // remove the two Zs
    goto bed_animation_transition;
  }

  tick += 3;
  clearjoy(0);
  delay(3);
  goto start_menu;
  
bed_animation_transition:
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
  
//  memcpy(blockmap, bg1map, 0x800);
//  memcpy(backmap, bg2map, 0x800);
//  memcpy(blocks, map, 0x64);
  memcpy(pal, palette, 0x200);
  setmap(0, (unsigned char*)blockmap);
//  setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);

  GameTitle();
/*
  unsigned char blocks[0x64], map[0x64] = 
{7,8,8,8,8,8,8,8,8,7,
 8,7,8,7,8,8,7,8,7,8,
 8,8,7,8,7,7,8,7,8,8,
 8,8,8,1,3,3,1,8,8,8,
 8,0,4,8,8,8,8,4,0,8,
 8,0,8,8,5,5,8,8,0,8,
 8,0,4,8,8,8,8,4,0,8,
 8,8,8,1,3,3,1,8,8,8,
 8,8,6,8,6,6,8,6,8,8,
 7,7,7,7,8,8,7,7,7,7};
  
  memcpy(blockmap, bg1map, 0x800);
  memcpy(backmap, bg2map, 0x800);
  memcpy(blocks, map, 0x64);
  memcpy(pal, palette, 0x200);
    int j, i,a, c, b=0, blockcount=0;
  for (j=0;j<10;j++) {
    for (i=0;i<20;i+=2) {
      a = blocks[b];
      if (a < 8) {
        c = (j<<5)+i; blockcount++;
        blockmap[0x62+c] = 13+(a<<10);
        blockmap[0x63+c] = 14+(a<<10);
        backmap[0x83+c] += 0x400;
        backmap[0x84+c] += 0x400;
      }
      b++;
    }
  }
*/
stage1:
  tick += 1;
  clearjoy(0);
  delay(1);

  mouse_stage();
    
  goto stage1;

/*  
  char st[17]="PLAYER 1\n\n READY", st2[10]="GAME OVER", st3[6]="PAUSE", st4[9]="        ";
  unsigned int i, j, a, b=0, c, obx, oby, bx=5, by=11, py=0, x=94, y=109;
  signed int dx=2, dy=1, px=80, xdir[4]={-2,-1,1,2}, ydir[4]={-1,-2,-2,-1};
  unsigned int blockcount=0;
  unsigned long long score=0, hiscore=50000;
  unsigned int level2=1;
  unsigned int color=0, level=0, lives=4;
  
  memcpy(blockmap, bg1map, 0x800);
  memcpy(backmap, bg2map, 0x800);
  memcpy(blocks, map, 0x64);
  memcpy(pal, palette, 0x200);
  
  for (j=0;j<10;j++) {
    for (i=0;i<20;i+=2) {
      a = blocks[b];
      if (a < 8) {
        c = (j<<5)+i; blockcount++;
        blockmap[0x62+c] = 13+(a<<10);
        blockmap[0x63+c] = 14+(a<<10);
        backmap[0x83+c] += 0x400;
        backmap[0x84+c] += 0x400;
      }
      b++;
    }
  }

  writenum(lives, 8, blockmap, 0x136, 0x426);
  writestring(st, blockmap, 0x248, 0x3F6);

  setmap(0, (unsigned char*)blockmap);
  setmap(1, (unsigned char*)backmap);
  setpalette((unsigned char*)pal);

  enablescreen();

  // main sprites
  setsprite(0, x, y, 20, 0x31);
  setsprite(1, px, 200, 15, 0x31);
  setsprite(2, px+8, 200, 16, 0x31);
  setsprite(3, px+16, 200, 16, 0x31+64);
  setsprite(4, px+24, 200, 17, 0x31);

  // shadow sprites
  setsprite(5, x+3, y+3, 21, 0x11);
  setsprite(6, px+4, 204, 18, 0x11);
  setsprite(7, px+12, 204, 19, 0x11);
  setsprite(8, px+20, 204, 19, 0x11+64);
  setsprite(9, px+28, 204, 18, 0x11+64);
  delay(50); 
  while (getjoystatus(0) == 0) continue;

  writestring(st4, blockmap, 0x248, 0x3F6);
  writestring(st4, blockmap, 0x289, 0x3F6);
  setmap(0, (unsigned char*)blockmap);

label1:
  resettimer();
  
  if ((getjoystatus(0) & START_BUTTON) != 0) {
    writestring(st3, blockmap, 0x269, 0x3F6);
    setmap(0, (unsigned char*)blockmap);  
    while (getjoystatus(0) != 0) { clearjoy(0); delay(5); } 
    while ((getjoystatus(0) & START_BUTTON) == 0) continue;
    while (getjoystatus(0) != 0) { clearjoy(0); delay(5); } 
    writestring(st4, blockmap, 0x269, 0x3F6);
    setmap(0, (unsigned char*)blockmap);
  }

  if ((getjoystatus(0) & A_BUTTON) != 0) {
    if ((getjoystatus(0) & RIGHT_BUTTON) != 0) px += 4;
    if ((getjoystatus(0) & LEFT_BUTTON) != 0) px -= 4;
  } else {
    if ((getjoystatus(0) & RIGHT_BUTTON) != 0) px += 2;
    if ((getjoystatus(0) & LEFT_BUTTON) != 0) px -= 2;
  }
  clearjoy(0);  

  if (px < 16) px = 16;
  if (px > 144) px = 144;

  x += dx; y += dy;
  if (x > 171) {
    dx = -dx; x = 171;
  } else if (x < 16) {
    dx = -dx; x = 16;
  }

  if (y < 15) { 
    dy = -dy; 
  } else if (y > 195) {
    if (y < 203) {
      if ((x >= px) && (x <= px+27)) {
        a = (x-px)/7; dx = xdir[a]; dy = ydir[a];
      }
    } else if (y > 224) {
        // death
        if (lives == 0) {
          writestring(st2, blockmap, 0x267, 0x3F6);
          setmap(0, (unsigned char*)blockmap);
          lose: goto lose;
        }
        lives--; x=94; y=109; px=80;
        writenum(lives, 8, blockmap, 0x136, 0x426);
        writestring(st, blockmap, 0x248, 0x3F6);
        setmap(0, (unsigned char*)blockmap);

        // main sprites
        setsprite(0, x, y, 20, 0x31);
        setsprite(1, px, 200, 15, 0x31);
        setsprite(2, px+8, 200, 16, 0x31);
        setsprite(3, px+16, 200, 16, 0x31+64);
        setsprite(4, px+24, 200, 17, 0x31);

        // shadow sprites
        setsprite(5, x+3, y+3, 21, 0x11);
        setsprite(6, px+4, 204, 18, 0x11);
        setsprite(7, px+12, 204, 19, 0x11);
        setsprite(8, px+20, 204, 19, 0x11+64);
        setsprite(9, px+28, 204, 18, 0x11+64);
        delay(50);
        while (getjoystatus(0) == 0) continue;

        writestring(st4, blockmap, 0x248, 0x3F6);
        writestring(st4, blockmap, 0x289, 0x3F6);
        setmap(0, (unsigned char*)blockmap);
    }
  } 
  else if (y < 112) {
    obx = bx; oby = by;
    bx = (x-14)>>4; by = (y-14)>>3;
    b = bx+(by<<3)+(by<<1)-10;
    if ((b >= 0) && (b<100)) {
      if (blocks[b] != 8) {
        blockcount--; 
        for (i=0;i<=level;i++)
          score += blocks[b]+1;
        if (oby != by) dy = -dy;
        if (obx != bx) dx = -dx;
        blocks[b] = 8; b = (by<<5)+(bx<<1);
        blockmap[0x42+b] = 0;
        blockmap[0x43+b] = 0;
        backmap[0x63+b] -= 0x400;
        backmap[0x64+b] -= 0x400;
        writenum(score, 8, blockmap, 0xF5, 0x426);
        if (score > hiscore) {
          hiscore = score;
          writenum(score, 8, blockmap, 0x95, 0x426);
        }
        setmap(0, (unsigned char*)blockmap);
        setmap(1, (unsigned char*)backmap);
        if (blockcount == 0) {
          // new level
          level++; level2++; x=94; y=109; px=80;
          writenum(level2, 8, blockmap, 0x2D6, 0x426);
          writestring(st, blockmap, 0x248, 0x3F6);
          memcpy(backmap, bg2map+0x800*(level&3), 0x800);
          memcpy(blocks, map, 0x64);
          if (color<6) { color++; } else color=0;
          memcpy(pal+16, backpal+color*16, 0x10);
          b=0;
          for (j=0;j<10;j++) {
            for (i=0;i<20;i++,i++) {
              a = blocks[b];
              if (a < 8) {
                c = (j<<5)+i; blockcount++;
                blockmap[0x62+c] = 13+(a<<10);
                blockmap[0x63+c] = 14+(a<<10);
                backmap[0x83+c] += 0x400;
                backmap[0x84+c] += 0x400;
              }
              b++;
            }
          }
          setpalette((unsigned char*)pal);
          setmap(0, (unsigned char*)blockmap);
          setmap(1, (unsigned char*)backmap);

          // main sprites
          setsprite(0, x, y, 20, 0x31);
          setsprite(1, px, 200, 15, 0x31);
          setsprite(2, px+8, 200, 16, 0x31);
          setsprite(3, px+16, 200, 16, 0x31+64);
          setsprite(4, px+24, 200, 17, 0x31);

          // shadow sprites
          setsprite(5, x+3, y+3, 21, 0x11);
          setsprite(6, px+4, 204, 18, 0x11);
          setsprite(7, px+12, 204, 19, 0x11);
          setsprite(8, px+20, 204, 19, 0x11+64);
          setsprite(9, px+28, 204, 18, 0x11+64);
          delay(50);
          while (getjoystatus(0) == 0) continue;

          writestring(st4, blockmap, 0x248, 0x3F6);
          writestring(st4, blockmap, 0x289, 0x3F6);
          setmap(0, (unsigned char*)blockmap);
        }
      }
    }
  }

  // main sprites
  setsprite(0, x, y, 20, 0x31);
  setsprite(1, px, 200, 15, 0x31);
  setsprite(2, px+8, 200, 16, 0x31);
  setsprite(3, px+16, 200, 16, 0x31+64);
  setsprite(4, px+24, 200, 17, 0x31);

  // shadow sprites
  setsprite(5, x+3, y+3, 21, 0x11);
  setsprite(6, px+4, 204, 18, 0x11);
  setsprite(7, px+12, 204, 19, 0x11);
  setsprite(8, px+20, 204, 19, 0x11+64);
  setsprite(9, px+28, 204, 18, 0x11+64);
*/
  //sync(1);
  //goto label1;
}
