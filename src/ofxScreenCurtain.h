/**
 Use it to handle "fade to black" situations... Think of it as of a theather curtain.
 It draws a rectangle as big as u specify in the color u specify, and fades its alpha in and out 
 */

#ifndef ofxScreenCurtain_h__
#define ofxScreenCurtain_h__

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

class ofxScreenCurtain {

	public:

		ofxScreenCurtain();	//screenSize in GL units (usually 320 x 240 or 640 x 480) 
		~ofxScreenCurtain(){};

		//basics
		void setup(ofColor curtainColor, ofRectangle screenSize);
		void update( float dt );
		void draw();
		
		//main actions
		bool dropAndRaiseCurtain( float dropDuration, float downDuration, float raiseDuration, bool regardless = false );
		bool dropCurtain( float duration , bool regardless = false);
		bool raiseCurtain( float duration , bool regardless = false);
		
		//status
		bool isReady(){ return ready_; }	/// is curtain ready to be moved (return false if it's being moved already)
		bool curtainIsDown(){ return alpha_.val() >= targetAlpha * 0.999f; /* hack, doesnt work on windows otherwise! TODO */ }
		
		/// use only after calling dropAndRaiseCurtain().
		/// will tell if curtain has already hit bottom (and its waiting to go back up)
		bool weAreBeyondFirstDrop(){ return transitionCounter_ == 1;}
		
		/// use only after calling dropAndRaiseCurtain().
		/// this will return true (only once per drop-raise) once the curtain has hit bottom, 
		///to use with shameful polling to trigger stuff once when curtain is down
		bool hasReachedBottom();
		
		void setAlphaWhenDown(float a){ targetAlpha = a;}
		void setAnimationCurve(AnimCurve c){ alpha_.setCurve(c); }
		
	private:

		enum CurtainMode { DOWN_THEN_UP = 0, DOWN = 1, UP = 2 } ;

		ofRectangle screenRect;		//2D
		ofColor curtainColor_;
		ofxAnimatableFloat alpha_;
		CurtainMode mode_;
		float targetAlpha;

		float dropDuration_, downDuration_, raiseDuration_;
		int transitionCounter_; //use this to know in which phase of DOWN_THEN_UP we are, [0..2]
		
		bool ready_;
		bool havereportedCurtainDown;

};

#endif // ofxScreenCurtain_h__