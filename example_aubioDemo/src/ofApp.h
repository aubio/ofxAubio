#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void exit();

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

        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut();

        void onsetEvent(float & time);
        void beatEvent(float & time);
        void tatumEvent(int & t);
        void onsetClassEvent(int & t);
        void beatClassEvent(int & t);

    private:
        ofxAubioOnset onset;
        ofxAubioPitch pitch;
        ofxAubioBeat beat;
        ofxAubioMelBands bands;
        ofxAubioAttackClass attackClass;
        int currentOnsetClass;
        int currentBeatClass;

        ofxPanel pitchGui;
        ofxFloatSlider midiPitch;
        ofxFloatSlider pitchConfidence;

        ofxPanel beatGui;
        bool gotBeat;
        bool gotTatum;
        ofxIntSlider bpm_tatumSignature;
        ofxFloatSlider bpm;

        ofxPanel onsetGui;
        bool gotOnset;
        ofxFloatSlider onsetThreshold;
        ofxFloatSlider onsetNovelty;
        ofxFloatSlider onsetThresholdedNovelty;

        ofxPanel bandsGui;
        ofPolyline bandPlot;
};
