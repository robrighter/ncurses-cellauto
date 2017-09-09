#include "conway.h"
#include <ctime>
#include <cstdlib>

Conway::Conway(){
    for(int i=0; i<MATRIX_HEIGHT; i++){
        for(int t=0; t<MATRIX_WIDTH; t++){
            canvas[i][t] = false;
        }
    }
    iteration = 0;
}

bool Conway::getValueAtLocation(int x, int y){
    if( (x < MATRIX_WIDTH) && (y < MATRIX_HEIGHT) ){
        return canvas[y][x];
    }
    else{
        return false;
    }
}

    

void Conway::processNextCycle(){
    int x=0;
    int y=0;
    
    bool nextcanvas[MATRIX_HEIGHT][MATRIX_WIDTH];
    
    //calculate the new values
    for(x=0; x<MATRIX_WIDTH; x++){
        for(y=0; y<MATRIX_HEIGHT; y++){
            nextcanvas[y][x] = calculateValueAtLocation(x,y);
        }
    }
    
    //now copy the new values onto the canvas
    for(x=0; x<MATRIX_WIDTH; x++){
        for(y=0; y<MATRIX_HEIGHT; y++){
            canvas[y][x] = nextcanvas[y][x] ? true : false;
        }
    }
    iteration++;
}

int Conway::getIteration() {
    return iteration;
}

void Conway::setValueAtLocation(bool toset, int x, int y){
    if( (x < MATRIX_WIDTH) && (y<MATRIX_HEIGHT) ){
        canvas[y][x] = toset;
    }
}

bool Conway::calculateValueAtLocation(int x, int y){
    int top_y = (y == 0) ? MATRIX_HEIGHT-1 : y-1;
    int middle_y = y;
    int bottom_y = ((y+1)<MATRIX_HEIGHT) ? y+1 : 0;
    int left_x = (x == 0) ? MATRIX_WIDTH-1 : x-1;
    int middle_x = x;
    int right_x = ((x+1)<MATRIX_WIDTH) ? x+1 : 0;
    
    
    
    neighbors[0] = getValueAtLocation(left_x, top_y);
    neighbors[1] = getValueAtLocation(middle_x, top_y);
    neighbors[2] = getValueAtLocation(right_x, top_y);
    neighbors[3] = getValueAtLocation(left_x, middle_y);
    neighbors[4] = getValueAtLocation(right_x, middle_y);
    neighbors[5] = getValueAtLocation(left_x, bottom_y);
    neighbors[6] = getValueAtLocation(middle_x, bottom_y);
    neighbors[7] = getValueAtLocation(right_x, bottom_y);
    bool is_on = getValueAtLocation(middle_x, middle_y);
    
    int neighbors_on = 0;
    int neighbors_off = 0;
    
    for(int i = 0; i<8; i++){
        if(neighbors[i]){
            neighbors_on++;
        }
        else{
            neighbors_off++;
        }
    }


    //RULES
    //1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
    if( is_on && (neighbors_on<2) ){
        return false;
    }
    //2. Any live cell with two or three live neighbours lives on to the next generation.
    if( is_on && ((neighbors_on == 2) || (neighbors_on == 3)) ){
        return true;
    }
    //3. Any live cell with more than three live neighbours dies, as if by overpopulation.
    if( is_on && (neighbors_on>3) ){
        return false;
    }
    //4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    if( (!is_on) && (neighbors_on == 3) ){
        return true;
    }
    //everything else just return the same dead cell that was there last round.
    return is_on;
}

void Conway::seedTheCanvas(){
    int number_on = rand()%150;
    int x = 0;
    int y = 0;
    for(int i=0; i<number_on; i++){
        y = i%MATRIX_HEIGHT;
        x = i%MATRIX_WIDTH;
        canvas[y][x] = true;
    }
}
