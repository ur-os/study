#include "text.h"


void text::run() {
    if(*gdy_local < *way_local * 0.75)   {*gdx_local = *wax_local / 4;}
    if(*gdy_local > *way_local * 0.75)   {*gdx_local -= 3;}
    if(*gdy_local > *way_local * 0.8725) {*gdx_local += 6;}
    if(*gdy_local >= *way_local - 30) {
        *gdy_local = 0;
        *gdx_local = *wax_local / 4;
    }
    *gdy_local += 2;
}

text::text(int *gdx, int *gdy, int *way, int *wax) {
    gdx_local = gdx;
    gdy_local = gdy;
    wax_local = wax;
    way_local = way;

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &text::run);
    timer->start(40);
}

