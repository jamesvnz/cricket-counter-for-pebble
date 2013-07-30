#include "pebble_os.h"
#include "cricket.h"

void innings_init(Innings *innings) {
    innings->ball = 0;
    innings->wicket = 0;
}

unsigned char innings_get_ball(Innings *innings) {
    return innings->ball % BALLS_PER_OVER;
}

unsigned short innings_get_over(Innings *innings) {
    return innings->ball / BALLS_PER_OVER;
}

unsigned char innings_get_wicket(Innings *innings) {
    return innings->wicket;
}

void innings_decrement_ball(Innings *innings) {
    if (innings->ball > 0) {
        innings->ball--;
    }
}

void innings_increment_ball(Innings *innings) {
    innings->ball++;
}

void innings_decrement_wicket(Innings *innings) {
    if (innings->wicket > 0) {
        innings->wicket--;
    }
}

void innings_increment_wicket(Innings *innings) {
    if (innings->wicket > 9) {
        innings->wicket = 0;
    } else {
        innings->wicket++;
    }
}
