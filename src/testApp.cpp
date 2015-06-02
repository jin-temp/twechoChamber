#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(255);
    ofSetFrameRate(10);
    
    homeScreen = true;
    
    //set up the text areas on the screen so we can write tweets in them later
    text1.init("Arial.ttf", 24);
    text2.init("Arial.ttf", 24);
    text3.init("Arial.ttf", 24);
    text4.init("Arial.ttf", 24);
    text5.init("Arial.ttf", 24);
    question.init("Arial.ttf", 36);
    homeText.init("Arial.ttf", 36);

    
    //set up the serial connection
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    // 0 opens the first device retrieved in the device list
    serial.setup(0, baud);
    
    //set up variables for reading the serial connection with the RFID reader
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    memset(bytesReadString, 0, 12);
    
    //set up the Twitter client
    twitterClient.setDiskCache(true);
    twitterClient.setAutoLoadImages(true, false); // Loads images into memory as ofImage;
    
    //NOTE: you must be logged into this account in your browser. If you are logged into a different account in your browser, the application will not work
    string const CONSUMER_KEY = "nI3CVanBz7IY7VKUjCYDRDAQV";
    string const CONSUMER_SECRET = "IxShxDGFl13YQ1tWBDTz48llFfkUcXgv0Tu6u6yAbUkyCQEaNe";
    
    twitterClient.authorize(CONSUMER_KEY, CONSUMER_SECRET);

    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //if a serial connection is established
    if(serial.available() > 1) {
        //ofLog(OF_LOG_NOTICE, "we have a serial connection");
        
        // some temp variables to keep track of the serial connection
        nTimesRead = 0;
        nBytesRead = 0;
        int nRead  = 0;
        
        unsigned char bytesReturned[3];
        
        memset(bytesReadString, 0, 4);
        memset(bytesReturned, 0, 3);
        
        while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
            nTimesRead++;
            nBytesRead = nRead;
        };
        
        memcpy(bytesReadString, bytesReturned, 3);
        
        //store the reading as a string
        serialReading = ofToString(bytesReadString);
        
        //if x is the first character in the serial reading, turn on the card's boolean
        if(serialReading.find("0")== 0)c0=true;
        if(serialReading.find("1")== 0)c1=true;
        if(serialReading.find("2")== 0)c2=true;
        if(serialReading.find("3")== 0)c3=true;
        if(serialReading.find("4")== 0)c4=true;
        if(serialReading.find("5")== 0)c5=true;
        if(serialReading.find("6")== 0)c6=true;
        if(serialReading.find("7")== 0)c7=true;
        if(serialReading.find("8")== 0)c8=true;
        if(serialReading.find("9")== 0)c9=true;

    }
    
    //here we tell the program what to search query to use for each corresponding card
    
    //CARD 0
    if(c0){
        ofLog(OF_LOG_NOTICE, "the card is 0!");
        
        //set the question text for the screen
        question.setText("Who is in charge of a woman's body?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22abortion%22%20OR%20%22prolife%22%20OR%20%22birthcontrol%22%20OR%20OR%20%22women%27s%20health%22";
        //start the search
        twitterClient.startSearch(search);

        //once we have loaded tweets from the search run the newTweets function and turn the card 0 function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c0 = false;
    }
    
    //CARD 1
    if(c1){
        ofLog(OF_LOG_NOTICE, "the card is 1!");
        
        //set the question text for the screen
        question.setText("Who are we fighting in the war on drugs?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search1;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search1.query = "%22war%20on%20drugs%22%20OR%20%22marijuana%22%20OR%20%22cocaine%22%20OR%20%22heroine%22%20OR%20%22narcotics%22%20OR%20%22drugs%22";
        
        //start the search
        twitterClient.startSearch(search1);
        
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c1 = false;
    }
    
    //CARD 2
    if(c2){
        ofLog(OF_LOG_NOTICE, "the card is 2!");
        
        //set the question text for the screen
        question.setText("When do we use guns?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22gun%22%20OR%20%22gun%20control%22%20OR%20%22right%20to%20carry%22%20OR%20%22NRA%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c2 = false;
    }
    
    //CARD 3
    if(c3){
        ofLog(OF_LOG_NOTICE, "the card is 3!");
        //set the question text for the screen
        question.setText("Is everyone free to practice their religion?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22religion%22%20OR%20%22religious%20freedom%22%20OR%20%22religious%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c3 = false;
    }
    
    //CARD 4
    if(c4){
        ofLog(OF_LOG_NOTICE, "the card is 4!");
        
        //set the question text for the screen
        question.setText("Is the climate changing because of human influence?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22climate%20change%22%20OR%20%22global%20warming%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c4 = false;
    }
    
    //CARD 5
    if(c5){
        ofLog(OF_LOG_NOTICE, "the card is 5!");
        //set the question text for the screen
        question.setText("How does society treat people with mental illnesses?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22mental%20illness%22%20OR%20%22mental%20health%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c5 = false;
    }
    
    //CARD 6
    if(c6){
        ofLog(OF_LOG_NOTICE, "the card is 6!");
        
        //set the question text for the screen
        question.setText("How much should the government be allowed to 'oversee'?");
        
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22government%20oversight%22%20OR%20%22NSA%22%20OR%20%22spying%22%20OR%20OR%20%22law%20enforcement%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c6 = false;
    }
    
    //CARD 7
    if(c7){
        ofLog(OF_LOG_NOTICE, "the card is 7!");
        
        //set the question text for the screen
        question.setText("How does soceity treat immigrants?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;

        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22immigration%22%20OR%20%22immigration%20reform%22%20OR%20%22immigrant%22%20OR%20%22immigrate%22%20OR%20%22expat%22%";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c7 = false;
    }
    
    //CARD 8
    if(c8){
        ofLog(OF_LOG_NOTICE, "the card is 8!");
        
        //set the question text for the screen
        question.setText("What do we do with all of the data we're collecting?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22big%20data%22%20OR%20%22data%20mining%22%20OR%20%22data%20analysis%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c8 = false;
    }
    
    //CARD 9
    if(c9){
        ofLog(OF_LOG_NOTICE, "the card is 9!");
        //set the question text for the screen
        question.setText("Is healthcare a right or a privilege?");
        
        //if there are already tweets loaded into the array, let's clear them
        if(twitterClient.getTotalLoadedTweets()>0){
            tweet.clear();
        }
        
        // create a new Twitter search
        ofxTwitterSearch search;
        
        //define the search query --> in the url of your twitter search, copy everything after the q= and uri encode any special characters
        search.query = "%22healthcare%22%20OR%20%22obamacare%22%20OR%20%22health%20insurance%22%20OR%20%22doctor%27s%20office%22%20OR%20%22vaccine%22%20OR%20%22prescription%22";
        
        //start the search
        twitterClient.startSearch(search);
        
        //once we have loaded tweets from the search run the newTweets function and turn the card function off
        if(twitterClient.getTotalLoadedTweets()>0){
            newTweets = true;
        }
        c9 = false;

    }
    
    //when we have new tweets, store them into a vector of tweets we can access later in the program
    if(newTweets){
        
        for (int i= 0; i<twitterClient.getTotalLoadedTweets()-1; i++){
            tweet.push_back(twitterClient.getTweetByIndex(i));
            //ofLog(OF_LOG_NOTICE, tweet[i].text);
            //ofLog(OF_LOG_NOTICE, twitterClient.getTweetByIndex(i).text);
            
        }
        
        //we call a random number to pick a tweet from the results
        t1 = ofRandom(tweet.size());
        t2 = ofRandom(tweet.size());
        t3 = ofRandom(tweet.size());
        t4 = ofRandom(tweet.size());
        t5 = ofRandom(tweet.size());
        
        //we make sure none of them are the same, and if they are, we pick a new random number
        if (t2 == t1 | t2 == t3 | t2 == t4| t2 == t5)t2 = ofRandom(tweet.size());
        if (t3 == t1 | t3 == t2 | t3 == t4| t3 == t5)t3 = ofRandom(tweet.size());
        if (t4 == t1 | t4 == t2 | t4 == t3| t4 == t5)t4 = ofRandom(tweet.size());
        if (t5 == t1 | t5 == t2 | t5 == t3| t5 == t4)t5 = ofRandom(tweet.size());
        

        //turn this function off so we don't pick new tweets until another card is scanned
        newTweets = false;
    }
    


//if there are tweets in the vector, turn the logged function on, otherwise turn it off
    if (tweet.size()>0){
        logged = true;
    } else {
        logged = false;
    }
    }

//--------------------------------------------------------------
void testApp::draw(){
   //if we haven't scanned a card, show the home screen text
    if (homeScreen){
        homeText.setText("Scan a card on the tEchoChamber to continue...");
        homeText.wrapTextArea(ofGetWindowWidth()/2, 100);
        ofPushMatrix();
        homeText.setColor(0, 255, 0, 255);
        ofTranslate(ofGetWindowWidth()/4, ofGetWindowHeight()/2-50);
        homeText.draw(0,0);
        ofPopMatrix();
    }
    
    //if we have logged some tweets, we'll draw them on the screen
    if(logged) {
        homeScreen = false;
        ofLog(OF_LOG_NOTICE, "logged!");
        
        
        ofSetColor(0);
        
        
        question.wrapTextArea(ofGetWindowWidth()/2, 100);
        ofPushMatrix();
        question.setColor(255, 0, 0, 255);
        ofTranslate(ofGetWindowWidth()/4, ofGetWindowHeight()/2-50);
        question.draw(0,0);
        ofPopMatrix();
        ofSetColor(0);
        
        
        text1.setText("@"+tweet[t1].user.screen_name+":"+tweet[t1].text);
        text1.wrapTextArea(250, 300);
        ofPushMatrix();
        ofTranslate(100, 50);
        text1.draw(0, 0);
        ofPopMatrix();
        
        text2.setText("@"+tweet[t2].user.screen_name+":"+tweet[t2].text);
        text2.wrapTextArea(250, 300);
        ofPushMatrix();
        ofTranslate(2*ofGetWindowWidth()/3, 50);
        text2.draw(0, 0);
        ofPopMatrix();
        
        text3.setText("@"+tweet[t3].user.screen_name+":"+tweet[t3].text);
        text3.wrapTextArea(250, 300);
        ofPushMatrix();
        ofTranslate(50, (ofGetWindowHeight()/2)+50);
        text3.draw(0, 0);
        ofPopMatrix();

        text4.setText("@"+tweet[t4].user.screen_name+":"+tweet[t4].text);
        text4.wrapTextArea(250, 300);
        ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2-150, (ofGetWindowHeight()/2)+50);
        text4.draw(0, 0);
        ofPopMatrix();

        text5.setText("@"+tweet[t5].user.screen_name+":"+tweet[t5].text);
        text5.wrapTextArea(250, 300);
        ofPushMatrix();
        ofTranslate(ofGetWindowWidth()-350, (ofGetWindowHeight()/2)+50);
        text3.draw(0, 0);
        ofPopMatrix();
        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == 'q') {
        
        
        // Simple Query. You can find tweets containing that word.
        ofxTwitterSearch search;
        //search.query = "'abortion' or 'prolife' or 'feminism' or 'gender pay gap' or 'birth control'";
        search.query = "abortion%20OR%20prolife%20OR%20birthcontrol%20OR%20OR%20women%27s%20health";
        twitterClient.startSearch(search);
        
        //we call a random number to pick a tweet from the results
        t1 = ofRandom(29);
        t2 = ofRandom(29);
        t3 = ofRandom(29);
        t4 = ofRandom(29);
        t5 = ofRandom(29);
        
        //we make sure none of them are the same, and if they are, we pick a new random number
        if (t2 == t1 | t2 == t3 | t2 == t4| t2 == t5)t2 = ofRandom(29);
        if (t3 == t1 | t3 == t2 | t3 == t4| t3 == t5)t3 = ofRandom(29);
        if (t4 == t1 | t4 == t2 | t4 == t3| t4 == t5)t4 = ofRandom(29);
        if (t5 == t1 | t5 == t2 | t5 == t3| t5 == t4)t5 = ofRandom(29);

        
    

    }
    
    if(key == 's') {
        // Complex search. You can specify more params.
        ofxTwitterSearch search;
        search.query = "cat";
        search.count = 10;
        search.geocode = ofVec2f(41.3850640,2.1734030);
        search.geocode_radius = 2;
        search.bUseMiles = false;
        search.lang = "es";
        twitterClient.startSearch(search);
    }
    
    if(key == 'l') {
        twitterClient.loadCacheFile();
    }
    
    if(key == OF_KEY_UP) {
        if(actualTweet < twitterClient.getTotalLoadedTweets()-1) actualTweet += 1;
    }
    
    if(key == OF_KEY_DOWN) {
        if(actualTweet > 0) actualTweet -= 1;
    }
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
