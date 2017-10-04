#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "keyboard/keyboard.h"

typedef struct {
    int s[5][5];
}shape_t;

struct pos{
    int x;
    int y;
};

struct pos t = {.x=5, .y=0};

#define H 20
#define W 10

#define BC 0
#define FC 5

int background[H][W] = {};

shape_t shape_arr[7] = {
    { 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 },
    { 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 }
};
int cur = 0;
int next = 0;

void draw_element(int x, int y, char c)
{
    x++;
    y++;
    x *= 2;
    printf("\033[%d;%dH\033[3%dm\033[4%dm[]", y, x, c, c);
    printf("\033[?25l\033[0m");
    fflush(stdout);
}

void draw_back( void )
{
    int i, j;

    for (i=0; i<H; i++) {
        for (j=0; j<W; j++) {
            if ( background[i][j] == 0 )
                draw_element(j, i, BC);
            else
                draw_element(j, i, FC);
        }
    }
}

void draw_shape(int x, int y, shape_t p, char c)
{
    int i, j;

    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            if ( p.s[i][j] == 1 ) {
                draw_element(x+j, y+i, c);
            }
        }
    }
}

int can_move(int x, int y, shape_t p)
{
    int i, j;

    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            if ( p.s[i][j] == 0 ) continue;
            if ( x+j >= W ) return 0;
            if ( y+i >= H ) return 0;
            if ( x+j < 0 ) return 0;
            if ( background[y+i][x+j] != 0 ) return 0;
        }
    }
    return 1;
}

void set_back(struct pos *t)
{
    int i, j;

    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            if ( shape_arr[cur].s[i][j] != 0 ) {
                background[t->y+i][t->x+j] = 1;
            }
        }
    }
}

void clean_line()
{
    int i, j;
    int k;

    for (i=0; i<H; i++) {
        k = 0;
        for (j=0; j<W; j++) {
            if ( background[i][j] != 0 )
                k++;
        }
        if ( k == W ) {
            int t;
            for (t=i; t>0; t--) {
                memcpy(background[t], background[t-1], sizeof(background[t]));
            }
            memset(background[0], 0x00, sizeof(background[0]));
        }
    }

    for (i=0; i<W; i++) {
        if ( background[1][i] != 0 ) {
            printf("game over!\n");
            recover_keyboard();
            exit(0);
        }
    }
}

void show_next()
{
    int i, j;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            if ( shape_arr[next].s[i][j] == 0 ) {
                draw_element(W+j+2, 2+i, BC);
            } else {
                draw_element(W+j+2, 2+i, FC);
            }
        }
    }
}


void tetris_timer(struct pos *t)
{
    draw_shape(t->x, t->y, shape_arr[cur], BC);
    if ( can_move(t->x, t->y+1, shape_arr[cur]) ) {
        t->y++;
        draw_shape(t->x, t->y, shape_arr[cur], FC);
    } else {
        set_back(t);
        clean_line();
        draw_back();
        cur = next;
        next = rand()%7;
        show_next();
        t->y = 0;
    }
}

void handler(int s)
{
    tetris_timer(&t);
}

shape_t turn_90(shape_t sh)
{
    int i, j;
    shape_t tmp;
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) {
            tmp.s[i][j] = sh.s[4-j][i];
        }
    }
    return tmp;
}

void tetirs(struct pos *t)
{
    int c;
    c = get_key();
    if ( is_up(c) ) {
        draw_shape(t->x, t->y, shape_arr[cur], BC);
        shape_arr[cur] = turn_90(shape_arr[cur]);
        if ( can_move(t->x, t->y, shape_arr[cur]) == 0 ) {
            shape_arr[cur] = turn_90(shape_arr[cur]);
            shape_arr[cur] = turn_90(shape_arr[cur]);
            shape_arr[cur] = turn_90(shape_arr[cur]);
        }
        draw_shape(t->x, t->y, shape_arr[cur], FC);
    } else if ( is_down(c) ) {
        draw_shape(t->x, t->y, shape_arr[cur], BC);
        if ( can_move(t->x, t->y+1, shape_arr[cur]) ) {
            t->y++;
            draw_shape(t->x, t->y, shape_arr[cur], FC);
        }
    } else if ( is_left(c) ) {
        draw_shape(t->x, t->y, shape_arr[cur], BC);
        if ( can_move(t->x-1, t->y, shape_arr[cur]) ) {
            t->x--;
            draw_shape(t->x, t->y, shape_arr[cur], FC);
        }
    } else if ( is_right(c) ) {
        draw_shape(t->x, t->y, shape_arr[cur], BC);
        if ( can_move(t->x+1, t->y, shape_arr[cur]) ) {
            t->x++;
            draw_shape(t->x, t->y, shape_arr[cur], FC);
        }
    }
}

int main( void )
{
    draw_back();

    struct itimerval it;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 1;
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_usec = 0;

    srand(time(NULL));
    next = rand() % 7;
    cur = rand() % 7;
    show_next();
    signal(SIGALRM, handler);
    setitimer(ITIMER_REAL, &it, NULL);

    init_keyboard();

    while ( 1 ) {
        tetirs(&t);
    }

    recover_keyboard();
}


