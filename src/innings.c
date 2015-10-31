#include <pebble.h>
#include "cricket.h"

void innings_init(Innings *innings) {
    innings->ball = 0;
    innings->widesAndNb = 0;
    innings->over = 1;
    innings->lastBall=' ';
}

unsigned char innings_get_ball(Innings *innings) {
//    return innings->ball % BALLS_PER_OVER;
  return innings->ball;
}

unsigned short innings_get_over(Innings *innings) {
   // return innings->ball / BALLS_PER_OVER;
  return innings->over;
}

unsigned char innings_get_widesAndNb(Innings *innings) {
    return innings->widesAndNb;
}

void innings_decrement_ball(Innings *innings) {
  
    if(innings->lastBall=='w' && innings->widesAndNb > 0) {
      innings->widesAndNb--;
    }
  
    if (innings->ball > 0) {
        innings->ball--;
    }
  
    innings->lastBall=' ';
}

void innings_increment_ball(Innings *innings) {
  char isWideOrNb = 0;
  internal_innings_increment_ball(innings, isWideOrNb);
}

void internal_innings_increment_ball(Innings *innings, char isWideOrNb) {
    innings->ball++;
    if (innings->ball == 6) {
      vibes_double_pulse();
      innings->ball=0;
      innings->over++;
      innings->widesAndNb=0;
    }
    if (!isWideOrNb){
      innings->lastBall='b';
    }
}

void innings_decrement_widesAndNb(Innings *innings) {
    if (innings->widesAndNb > 0) {
        innings->widesAndNb--;
    }
}

void innings_increment_widesAndNb(Innings *innings) {
    if (innings->widesAndNb >= 2) {
        innings->widesAndNb++;
        char isWideOrNb = 1;
        internal_innings_increment_ball(innings,isWideOrNb);
    } else {
        innings->widesAndNb++;
    }
    innings->lastBall='w';

}

/* vim: set cin ai et ts=4 sw=4: */
