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
}



//------------------------------------------------------------------
void creature::update() {
    
}



//------------------------------------------------------------------
void creature::draw() {

    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    ofSetColor(this->adult_color.r,this->adult_color.g,this->adult_color.b);
    ofFill();
    ofBeginShape();
    for(int i=0;i<(this->adult_sides);i++){
        int cX = 100;
        int cY = 100;
        float x = cX + (float)(this->adult_size * sin((i+1) * ((2*PI) / this->adult_sides)));
        float y = cY + (float)(this->adult_size * -cos((i+1) * ((2*PI) / this->adult_sides)));
        ofVertex((int)x, (int)y);
    }
    
    ofEndShape();  
}

void creature::immaculate(){
    this->adult_size = (int)ofRandom(50, 200);
    this->adult_color.r = (int)ofRandom(255);
    this->adult_color.g = (int)ofRandom(255);
    this->adult_color.b = (int)ofRandom(255);
    this->adult_age = (int)ofRandom(10,120);
    this->adult_sides = (int)ofRandom(3,11);
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