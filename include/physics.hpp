#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <math.h>

double time = 3;
double dt = 1/(4096.0*time);
double G = 6.674*pow(10,-11);;
double BM = 1000000000000;


// double G = 6.674*pow(10,-11);
int flag = 0;

class stellarObject{
    public:
        stellarObject(Vector3 velocity, Vector3 position, Vector3 acceleration, double mass, std::string name, double radius){
            this->velocity = velocity;
            this->position = position;
            this->acceleration = acceleration;
            this->mass = mass;
            this->name = name;
            this->radius = radius;
        }
        stellarObject(){
        }
        Vector3 velocity;
        Vector3 position;
        Vector3 acceleration;
        double mass;
        double radius;
        std::string name; 

    private:

};

std::vector<stellarObject> stellarEntities;

double distX(stellarObject m1, stellarObject m2){

    return m1.position.x-m2.position.x;

}

double distY(stellarObject m1, stellarObject m2){

    return m1.position.y-m2.position.y;

}

double distZ(stellarObject m1, stellarObject m2){

    return m1.position.z-m2.position.z;

}

Vector3 getGravForce(stellarObject m1, stellarObject m2){

    Vector3 force = {0,0,0};

    double dist = sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2) + pow(distZ(m1,m2),2));

    if(dist == 0){return {0,0,0};}

    double f = (G*m1.mass*m2.mass)/pow(dist,2);


    force.x = f*distX(m2,m1)/sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2));
    force.y = f*distY(m2,m1)/sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2));
    force.z = f*distZ(m2,m1)/dist;

    if(distX(m1,m2) == 0){force.x=0;}
    if(distY(m1,m2) == 0){force.y=0;}
    if(distZ(m1,m2) == 0){force.z=0;}

    return force;

}

double ttt(stellarObject m1, stellarObject m2){

    Vector3 force = {0,0,0};

    double dist = sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2) + pow(distZ(m1,m2),2));

    // if(dist == 0){return {0,0,0};}

    double f = (G*m1.mass*m2.mass)/pow(dist,2);

    force.x = f*distX(m1,m2)/sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2));
    force.y = f*distY(m1,m2)/sqrt(pow(distX(m1,m2),2) + pow(distY(m1,m2),2));
    force.z = f*distZ(m1,m2)/dist;

    if(distX(m1,m2) == 0){force.x=0;}
    if(distY(m1,m2) == 0){force.y=0;}
    if(distZ(m1,m2) == 0){force.z=0;}

    return force.z;

}


Vector3 acceleration(stellarObject self){
    Vector3 acceleration = {0,0,0};
    for(int i = 0; i<stellarEntities.size(); i++){
        if(stellarEntities[i].name == self.name){continue;}
        acceleration.x += getGravForce(self, stellarEntities[i]).x/self.mass;
        acceleration.y += getGravForce(self, stellarEntities[i]).y/self.mass;
        acceleration.z += getGravForce(self, stellarEntities[i]).z/self.mass;
    }
    return acceleration;
}

void move(stellarObject* self){

    self->acceleration = acceleration(*self);
    self->velocity.x += self->acceleration.x * dt;
    self->velocity.y += self->acceleration.y * dt;
    self->velocity.z += self->acceleration.z * dt;

    self->position.x += self->velocity.x * dt;
    self->position.y += self->velocity.y * dt;
    self->position.z += self->velocity.z * dt;
    
    flag++;

}


void calculatePhysics(){
    for(int i = 0; i<stellarEntities.size(); i++){
        move(&stellarEntities[i]);
        std::cout<<"here";
    }
}