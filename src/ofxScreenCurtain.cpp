
#include "ofxScreenCurtain.h"


ofxScreenCurtain::ofxScreenCurtain(){
	setup( ofColor::black, ofRectangle(0,0, ofGetWidth(), ofGetHeight()) );
}

void ofxScreenCurtain::setup(ofColor curtainColor, ofRectangle screen){
	alpha_.reset(0.0f);
	alpha_.setCurve(TANH);
	screenRect = screen;
	curtainColor_ = curtainColor;	
	ready_ = true;
	targetAlpha = 1.0f;
}

void ofxScreenCurtain::update( float dt ){

	if ( ready_ == false ){	//something is going on
		
		alpha_.update(dt);

		switch( mode_ ){

			case DOWN_THEN_UP:
				
				if ( alpha_.hasFinishedAnimating() ){

					switch( transitionCounter_ ){

						case 0:	//curtain is down, has to stay down for downDuration_ seconds
							alpha_.setDuration(downDuration_);
							alpha_.animateTo( targetAlpha );
							transitionCounter_ ++;
							break;

						case 1:
							alpha_.setDuration(raiseDuration_);
							alpha_.animateTo( 0.0f );
							transitionCounter_ ++;
							break;

						case 2:
							ready_ = true;
							transitionCounter_ = 0;
							break;
					}
				}

				break;

			case DOWN:
			case UP:

				if ( alpha_.hasFinishedAnimating() ){
					ready_ = true;
				}
				break;
		}	
	}
}


void ofxScreenCurtain::draw(){

	if ( alpha_.val() > 0.0f ){
		ofSetColor( curtainColor_.r, curtainColor_.g, curtainColor_.b, 255 * alpha_.val() );
		ofRect( screenRect );
	}
}


bool ofxScreenCurtain::dropAndRaiseCurtain( float dropDuration, float downDuration, float raiseDuration , bool regardless ){

 	if ( ready_ || regardless ){
		havereportedCurtainDown = false;
		ready_ = false;
		mode_ = DOWN_THEN_UP;
		transitionCounter_ = 0;
		downDuration_ = downDuration;
		raiseDuration_ = raiseDuration;
 		alpha_.reset( 0.0f );
		alpha_.setDuration( dropDuration );
		alpha_.animateTo( targetAlpha );
		return true;

	}else{
		return false;	//we cant do it now, we are not ready
	}
}

bool ofxScreenCurtain::dropCurtain( float duration , bool regardless){

	
	if ( ready_ || regardless ){
		havereportedCurtainDown = true;
		ready_ = false;
		mode_ = DOWN;
		alpha_.setDuration( duration );
		alpha_.animateTo( targetAlpha );
		return true;
	}else
		return false;	//we cant do it now, we are not ready
}


bool ofxScreenCurtain::raiseCurtain( float duration, bool regardless ){

	
	if ( ready_  || regardless ){
		havereportedCurtainDown = true;
		ready_ = false;
		mode_ = UP;
		alpha_.setDuration( duration);
		alpha_.animateTo( 0.0f );
		return true;
	}else
		return false;	//we cant do it now, we are not ready
}

bool ofxScreenCurtain::hasReachedBottom(){
	if ( !havereportedCurtainDown ){
		if (weAreBeyondFirstDrop()){
			havereportedCurtainDown = true;
			return true;
		}
	}
	return false;
}