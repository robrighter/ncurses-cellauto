
#ifndef CONWAY_H
#define CONWAY_H
#define CONWAY_CHANGE_SLEEP_SECONDS 10
#define MATRIX_HEIGHT 400
#define MATRIX_WIDTH 400


class Conway {
  public:
    Conway();
    bool getValueAtLocation(int x, int y);
    void processNextCycle();
    void seedTheCanvas();
    int  getIteration();

  private:
    void setValueAtLocation(bool toset, int x, int y);
    bool calculateValueAtLocation(int x, int y);
    bool canvas[MATRIX_HEIGHT][MATRIX_WIDTH] =  { {false}, {false} };
    bool neighbors[8];
    int iteration = 0;
};


#endif
