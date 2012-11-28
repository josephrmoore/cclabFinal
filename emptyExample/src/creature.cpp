//
//  creature.cpp
//  emptyExample
//
//  Created by Joseph Moore on 11/28/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "creature.h"

//------------------------------------------------------------------
void creature::setup() {
    this->top_speed = (int)ofRandom(10,50);
    this->start_size = 10;
    this->start_sides = 3;
    this->start_color.r = 0;
    this->start_color.g = 0;
    this->start_color.b = 0;
    this->curr_size = 10;
    this->curr_sides = 3;
    this->curr_color.r = 0;
    this->curr_color.g = 0;
    this->curr_color.b = 0;
}



//------------------------------------------------------------------
void creature::update() {
    this->curr_age = (int)((ofGetElapsedTimeMillis() - this->born_on)/1000);
    if(this->curr_age < this->adult_age){
        float percent = (((ofGetElapsedTimeMillis() - this->born_on)/1000)/(float)this->adult_age);
        this->curr_size = ((this->adult_size-this->start_size)*percent)+this->start_size;
        this->curr_sides = ((this->adult_sides-this->start_sides)*percent)+this->start_sides;
//        if(this->curr_color.r<this->adult_color.r){
            this->curr_color.r = (int)(this->adult_color.r*percent);
//        } else if (this->curr_color.g<this->adult_color.g){
            this->curr_color.g = (int)(this->adult_color.g*percent);
//        } else {
            this->curr_color.b = (int)(this->adult_color.b*percent);
//        }
    } else {
        this->curr_color = this->adult_color;
        this->curr_size = this->adult_size;
        this->curr_sides = this->adult_sides;
    }
}



//------------------------------------------------------------------
void creature::draw() {
    cout << "born: " << this->born_on << endl;
    cout << "age: " << this->curr_age << endl;
    cout << "color: " << this->curr_color << endl;
    cout << "sides: " << this->curr_sides << endl;
    cout << "size: " << this->curr_size << endl;
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofSetColor(this->curr_color.r,this->curr_color.g,this->curr_color.b);
    ofFill();
    ofBeginShape();
    for(int i=0;i<(this->curr_sides);i++){
        int cX = 300;
        int cY = 300;
        float x = cX + (float)(this->curr_size * sin((i+1) * ((2*PI) / this->curr_sides)));
        float y = cY + (float)(this->curr_size * -cos((i+1) * ((2*PI) / this->curr_sides)));
        ofVertex((int)x, (int)y);
    }
    
    ofEndShape();  
}

void creature::immaculate(){
    this->setup();
    this->adult_size = (int)ofRandom(50, 200);
    this->adult_color.r = (int)ofRandom(255);
    this->adult_color.g = (int)ofRandom(255);
    this->adult_color.b = (int)ofRandom(255);
    this->adult_age = (int)ofRandom(10,30);
    this->adult_sides = (int)ofRandom(3,11);
    this->born_on = ofGetElapsedTimeMillis();
}

void creature::livebirth(creature mom, creature dad){
    float percentage_mom, percentage_dad;
    creature baby;
    percentage_mom = ofRandom(1);
    percentage_dad = 1-percentage_mom;
    baby.adult_size = (int)mom.adult_size*percentage_mom + (int)dad.adult_size*percentage_dad;
    percentage_mom = ofRandom(1);
    percentage_dad = 1-percentage_mom;
    baby.adult_age = (int)mom.adult_age*percentage_mom + (int)dad.adult_age*percentage_dad;
    percentage_mom = ofRandom(1);
    percentage_dad = 1-percentage_mom;
    baby.adult_color.r = (int)mom.adult_color.r*percentage_mom + (int)dad.adult_color.r*percentage_dad;
    percentage_mom = ofRandom(1);
    percentage_dad = 1-percentage_mom;
    baby.adult_color.g = (int)mom.adult_color.g*percentage_mom + (int)dad.adult_color.g*percentage_dad;
    percentage_mom = ofRandom(1);
    percentage_dad = 1-percentage_mom;
    baby.adult_color.b = (int)mom.adult_color.b*percentage_mom + (int)dad.adult_color.b*percentage_dad;
}