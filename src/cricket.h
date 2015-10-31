#ifndef CRICKET_H_INCLUDED
#define CRICKET_H_INCLUDED

#define BALLS_PER_OVER 6

typedef struct {
    unsigned short ball;
    unsigned char widesAndNb;
    unsigned short over;
    unsigned char lastBall;
} Innings;

void innings_init(Innings *innings);

unsigned char innings_get_ball(Innings *innings);
unsigned short innings_get_over(Innings *innings);
unsigned char innings_get_widesAndNb(Innings *innings);

void innings_decrement_ball(Innings *innings);
void innings_increment_ball(Innings *innings);
void internal_innings_increment_ball(Innings *innings, char isWideOrNb);

void innings_decrement_widesAndNb(Innings *innings);
void innings_increment_widesAndNb(Innings *innings);

#endif

/* vim: set cin ai et ts=4 sw=4: */
