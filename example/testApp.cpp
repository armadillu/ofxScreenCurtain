#include "testApp.h"


void testApp::setup(){

	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(128, 128, 128, 255);

	//setup two messages
	a = "Hello!";
	b = "GoodBye!";	
	currentMessage = &a;
	
	//set curtain animation curve
	curtain.setAnimationCurve( EASE_IN_EASE_OUT );
}


void testApp::update(){

	curtain.update( 0.016666f );
	
	//once curtain hits the bottom, swap the message!
	if ( curtain.hasReachedBottom() ){
		swapMessage();
	}
	
	//once curtain is fully back up, print!
	if (curtain.hasReachedTop()){
		printf("completed curtain Drop and Raise!\n");
	}
}


void testApp::draw(){

	ofSetColor(255);
	ofPushMatrix();
		ofTranslate(100, ofGetHeight()/2);
		ofScale(10, 10);
		ofDrawBitmapString(*currentMessage, 0, 0);
	ofPopMatrix();
	
	curtain.draw();
	ofSetColor(255,255,255);
	curtain.drawDebug();
	
	ofSetColor(255, 0, 0);
	ofDrawBitmapString("Click Mouse to Drop Curtain", 10,15);
	
}


void testApp::swapMessage(){
	if ( currentMessage == &a) {
		currentMessage = &b;
	}else{
		currentMessage = &a;
	}	
}


void testApp::mousePressed(int x, int y, int button){

	if (curtain.isReady()){
		curtain.dropAndRaiseCurtain(
									0.25 /*drop duration*/, 
									0.1 /*stay down duration*/, 
									0.25 /*rise duration*/
									);
	}
}
