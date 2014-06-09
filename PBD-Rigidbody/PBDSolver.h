#ifndef PBDSOLVER_H_INCLUDE
#define PBDSOLVER_H_INCLUDE

#include "particle.h"
#include <memory.h>
#include <iostream>
using namespace std;

#define MAXNUM 10000
#define CELLSIZE 200
#define SIMX 100.0
#define SIMY 100.0
#define H 1.5
#define ITERATION 3
#define XX (int)(SIMX/H+1)
#define YY (int)(SIMY/H+1)
#define M 1.0
//
#define n 1000
#define dt 0.05
//
const int dir[9][2] = {{-1,1}, {-1,0}, {-1,-1}, {0,1}, {0,0}, {0,-1}, {1,1}, {1,0}, {1,-1}};
//

class PBDSolver{
private:
    Particle particles[MAXNUM];
    int cnt[XX][YY];
    int cell[XX][YY][CELLSIZE];
    //
    void forcePredict();
    void fillGrid();
    void iteration();
    void updateVelPos();
    //
    void minDis();
    void collision(Particle &pi);
    //
    bool valid(int &x, int s, int e){
        if(x >= s && x < e) return 1;
        if(x < s) x = s;
        if(x >= e) x = e - 1;
        return 0;
    }
public:
    PBDSolver(){};
    void Init();
    void Update();
    Particle* getParticles(int &num){
        num = n;
        return particles;
    }
};

#endif //PBFSOLVER_H_INCLUDE
