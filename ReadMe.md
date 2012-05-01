Use it to handle "fade to black" situations... Think of it as a theather curtain.

It draws a rectangle as big as u specify in the color u specify, and fades its alpha in and out.

Requires ofxAnimatable addon.


Let's see how to make a screen fade to black and back, triggering an action when the curtain is fully down.

	ofxScreenCurtain curtain;

	update(){
		curtain.update( 0.016666f );

		//once curtain hits the bottom, change the contents
		if ( curtain.hasReachedBottom() ){
			doYourThingie();
		}
	}

	draw(){
		curtain.draw();
	}

	mousePressed(){		
		if (curtain.isReady()){
			curtain.dropAndRaiseCurtain(
										0.25 /*go down duration*/, 
										0.1 /*stay down duration*/, 
										0.25 /*go up duration*/
										);
		}
	}

