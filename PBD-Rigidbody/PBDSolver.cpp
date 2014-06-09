
#include "PBDSolver.h"

void PBDSolver::Init(){
    memset(particles, 0, sizeof(particles));
    NumType gap = 0.99 * H;
    NumType x_pos = H;
    NumType y_pos = H;
    for(int i=0; i<n; i++){
        Particle &pi = particles[i];
        pi.pos = vec2(x_pos, y_pos);
        y_pos += gap;
        if(y_pos >= SIMY - H){
            y_pos = H;
            x_pos += gap;
        }
    }
}

void PBDSolver::Update(){
    forcePredict();
    fillGrid();
    iteration();
    updateVelPos();
}

void PBDSolver::forcePredict(){
    for(int i=0; i<n; i++){
        Particle &pi = particles[i];
        pi.vel += dt * vec2(0.0, -9.8*M) / M;
        pi.tmpos = pi.pos + dt * pi.vel;
    }
}

void PBDSolver::fillGrid(){
    memset(cnt, 0, sizeof(cnt));
    //Моід
    for(int i=0; i<n; i++){
        Particle &pi = particles[i];
        int x = pi.tmpos.x / H;
        int y = pi.tmpos.y / H;
        valid(x, 0, XX);
        valid(y, 0, YY);
        int &z = cnt[x][y];
        if(z >= CELLSIZE){
            cout<<"z >= CELLSIZE"<<endl;
        }
        cell[x][y][z] = i;
        z ++;
    }
}

void PBDSolver::iteration(){
    for(int i=0; i<ITERATION; i++){
        minDis();
    }
}

void PBDSolver::minDis(){
    for(int i=0; i<n; i++){
        Particle &pi = particles[i];
        //
        int x = pi.tmpos.x / H;
        int y = pi.tmpos.y / H;
        valid(x, 0, XX);
        valid(y, 0, YY);
        for(int k=0; k<9; k++){
            int _x = x + dir[k][0];
            int _y = y + dir[k][1];
            if(!valid(_x, 0, XX) || !valid(_y, 0, YY)) continue;
            int z = cnt[_x][_y];
            for(int j=0; j<z; j++){
                int index = cell[_x][_y][j];
                if(i == index) continue;
                Particle &pj = particles[index];
                //
                float dis = (pi.tmpos - pj.tmpos).len();
                float gap = H;
                if(dis < gap){
                    vec2 tmp = (dis - gap) * (pi.tmpos - pj.tmpos) / dis;
                    pi.tmpos += -1.0 / 2.0 * tmp;
                    pj.tmpos += 1.0 / 2.0 * tmp;
                }
            }
        }
        //
        collision(pi);
    }
}

void PBDSolver::collision(Particle &pi){
    const float bedding_in = 0.1 * H;
    const float bedding_out = 1.5 * H;

    float scale = 0.5;
    float p;

    if(pi.tmpos.x < 0.0 + bedding_out){
        p = bedding_out - pi.tmpos.x;
        pi.tmpos.x = bedding_out - p / (p * p * scale + 1.0);
    }
    if(pi.tmpos.x < 0.0 + bedding_in){
        pi.tmpos.x = bedding_in;
    }
    if(pi.tmpos.y < 0.0 + bedding_out){
        p = bedding_out - pi.tmpos.y;
        pi.tmpos.y = bedding_out - p / (p * p * scale + 1.0);
    }
    if(pi.tmpos.y < 0.0 + bedding_in){
        pi.tmpos.y = bedding_in;
    }
    if(pi.tmpos.x > SIMX - bedding_out){
        p = pi.tmpos.x - SIMX + bedding_out;
        pi.tmpos.x = p / (p * p * scale + 1.0) + SIMX - bedding_out;
    }
    if(pi.tmpos.x > SIMX - bedding_in){
        pi.tmpos.x = SIMX - bedding_in;
    }
    if(pi.tmpos.y > SIMY - bedding_out){
        p = pi.tmpos.y - SIMY + bedding_out;
        pi.tmpos.y = p / (p * p * scale + 1.0) + SIMY - bedding_out;
    }
    if(pi.tmpos.y > SIMY - bedding_in){
        pi.tmpos.y = SIMY - bedding_in;
    }
}

void PBDSolver::updateVelPos(){
    for(int i=0; i<n; i++){
        Particle &pi = particles[i];
        //
        pi.vel = (pi.tmpos - pi.pos) / dt;
        pi.pos = pi.tmpos;
    }
}
