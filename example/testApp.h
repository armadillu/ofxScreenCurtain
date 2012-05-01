#pragma once

#include "ofMain.h"
#include "ofxScreenCurtain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void swapMessage();
		void mousePressed(int x, int y, int button);
		
		ofxScreenCurtain curtain;
	
		string a, b;
		string* currentMessage;
	
};
