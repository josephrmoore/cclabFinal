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
    this->start_size = 5;
    this->start_sides = 3;
    this->start_color.r = 0;
    this->start_color.g = 0;
    this->start_color.b = 0;
    this->curr_size = 5;
    this->curr_sides = 3;
    this->curr_color.r = 0;
    this->curr_color.g = 0;
    this->curr_color.b = 0;
    this->xpos = ofRandom(ofGetWidth());
    this->ypos = ofRandom(ofGetHeight());
    this->xvel = ofRandom(5);
    this->yvel = ofRandom(5);
    this->circle.setPhysics(3.0, 0.53, 0.1);
    this->hasUser = false;
    this->colliding = false;
    this->justPushed = false;
    this->curr_decay = 0;
    this->underCreation = false;
    this->underDestruction = false;
    this->total_children = ofRandom(10);
}



//------------------------------------------------------------------
void creature::update() {
    this->curr_age = ofGetElapsedTimeMillis() - this->born_on;
    if(this->curr_age < this->adult_age){
        float percent = ((float)(ofGetElapsedTimeMillis() - this->born_on)/(float)this->adult_age);
        this->curr_size = ((this->adult_size-this->start_size)*percent)+this->start_size;
            this->curr_color.r = (int)(this->adult_color.r*percent);
            this->curr_color.g = (int)(this->adult_color.g*percent);
            this->curr_color.b = (int)(this->adult_color.b*percent);
    } else if(this->curr_age > this->longevity){
        // death fx
        this->curr_size = 0;
    } else if(this->curr_age>this->decline) {
        // dying fx
        if(this->curr_decay>=this->decayRate){
            this->curr_size -= 2;
            this->curr_color.setSaturation(this->curr_color.getSaturation()-10);
            this->curr_decay = 0;
        } else {
            this->curr_decay++;
        }
    } else {
        this->curr_color = this->adult_color;
        this->curr_size = this->adult_size;
    }
}



//------------------------------------------------------------------
void creature::draw() {
    ofFill();
    ofSetColor(this->curr_color);
    this->circle.setRadius(this->curr_size);
    this->circle.draw();
}

void creature::immaculate(b2World* world, int i){
    this->setup();
    this->adult_size = (int)ofRandom(10, 50);
    this->adult_color.r = (int)ofRandom(255);
    this->adult_color.g = (int)ofRandom(255);
    this->adult_color.b = (int)ofRandom(255);
    this->adult_age = (int)ofRandom(5,10)*1000;
    this->longevity = (int)ofRandom(3,6)*this->adult_age;
    this->decline = this->longevity-this->adult_age;
    this->decayRate = (int)ofRandom(5,15);
    this->adult_sides = (int)ofRandom(3,11);
    this->born_on = ofGetElapsedTimeMillis();
    this->circle.setup(world, this->xpos, this->ypos, this->curr_size/2);
    this->circle.setVelocity(this->xvel, this->yvel);
    this->userId = i;
}

void creature::livebirth(creature me, creature partner, b2World* world, int i){
//    float percentage_me, percentage_partner;
//    percentage_me = ofRandom(1);
//    percentage_partner = 1-percentage_me;
//    creature baby;
//    baby.setup();
//    baby.adult_size = (int)me.adult_size*percentage_me + (int)partner.adult_size*percentage_partner;
//    baby.adult_color.r = (int)me.adult_color.r*percentage_me + (int)partner.adult_color.r*percentage_partner;
//    baby.adult_color.g = (int)me.adult_color.g*percentage_me + (int)partner.adult_color.g*percentage_partner;
//    baby.adult_color.b = (int)me.adult_color.b*percentage_me + (int)partner.adult_color.b*percentage_partner;
//    baby.adult_age = (int)me.adult_age*percentage_me + (int)partner.adult_age*percentage_partner;
//    baby.longevity = (int)me.longevity*percentage_me + (int)partner.longevity*percentage_partner;
//    baby.decline = (int)me.decline*percentage_me + (int)partner.decline*percentage_partner;
//    baby.decayRate = (int)me.decayRate*percentage_me + (int)partner.decayRate*percentage_partner;
//    baby.adult_sides = (int)me.adult_sides*percentage_me + (int)partner.adult_sides*percentage_partner;
//    baby.born_on = ofGetElapsedTimeMillis();
//    baby.circle.setup(world, 0, 0, 5);
//    baby.circle.setVelocity(baby.xvel, baby.yvel);
//    baby.userId = i;
//    npc.push_back(baby);
}