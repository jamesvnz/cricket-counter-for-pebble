#ifndef CRICKET_H_INCLUDED
#define CRICKET_H_INCLUDED

#define BALLS_PER_OVER 6

typedef struct {
    unsigned short ball;
    unsigned char wicket;
} Innings;

void innings_init(Innings *innings);

unsigned char innings_get_ball(Innings *innings);
unsigned short innings_get_over(Innings *innings);
unsigned char innings_get_wicket(Innings *innings);

void innings_decrement_ball(Innings *innings);
void innings_increment_ball(Innings *innings);

void innings_decrement_wicket(Innings *innings);
void innings_increment_wicket(Innings *innings);

#endif
