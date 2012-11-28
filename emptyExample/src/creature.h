//
//  creature.h
//  emptyExample
//
//  Created by Joseph Moore on 11/28/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _creature
#define _creature


#include "ofMain.h"


class creature {
	
public:
    void setup();
    void update();
    void draw();
    void immaculate();
    void livebirth(creature mom, creature dad);
    
    int adult_size, adult_sides, top_speed, adult_age;
    int start_size, start_sides;
    int curr_size, curr_sides, curr_age;
    int born_on;
    float xpos, ypos, xvel, yvel, xacc, yacc;
    ofColor adult_color, curr_color, start_color;
};

#endif
