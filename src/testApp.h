#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxTextSuite.h"

class testApp : public ofBaseApp{

	public:
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofTrueTypeFont		font;

    
        //declare Twitter related variables
        ofxTwitter twitterClient;
        vector<ofxTwitterTweet> tweet;
        int actualTweet;
        bool reloadTweet;
        bool logged;
        bool newTweets;
    
        ofImage userImage;
    
        //pick 5 tweets to display
        int t1;
        int t2;
        int t3;
        int t4;
        int t5;

    //declare RFID/serial related variables
    bool		bSendSerialMessage;			// a flag for sending serial
    char		bytesRead[12];				// data from serial, we will be trying to read 3
    char		bytesReadString[13];		// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?
    
    ofSerial	serial;
    
    //this has to be a string vector so that we can run ofContains to check for card values
    //vector<string> text;
    string serialReading;
    
    //these are the variables for tracking which card was read
    bool c0;
    bool c1;
    bool c2;
    bool c3;
    bool c4;
    bool c5;
    bool c6;
    bool c7;
    bool c8;
    bool c9;
    
    bool homeScreen;

    ofxTextBlock homeText;
   
    //these are the text elements we'll put the tweet text in
    ofxTextBlock text1;
    ofxTextBlock text2;
    ofxTextBlock text3;
    ofxTextBlock text4;
    ofxTextBlock text5;
    
    //this is the text element we fill with the question that corresponds to the last card read
    ofxTextBlock question;
    
    
    
};
