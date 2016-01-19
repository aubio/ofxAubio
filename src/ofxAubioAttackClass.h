/*
  Copyright (C) 2015 Paul Brossier <piem@aubio.org>

  This file is part of ofxAubio.

  ofxAubio is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  aubio is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with aubio.  If not, see <http://www.gnu.org/licenses/>.

*/

#pragma once

#include <iostream>
#include <aubio/aubio.h>
#include "ofEvents.h"
#include "ofxAubioBlock.h"
#include "ofxAubioOnset.h"
#include "ofxAubioBeat.h"
#include "ofxAubioMelBands.h"

class ofxAubioAttackClass : public ofxAubioBlock {

    public:

       ofxAubioAttackClass();
       ~ofxAubioAttackClass();

       ofEvent<int> gotOnsetClass;
       static ofEvent<int> gotGlobalOnsetClass;
       void onsetEvent(float & time);

       ofEvent<int> gotBeatClass;
       static ofEvent<int> gotGlobalBeatClass;
       void beatEvent(float & time);

       ofxAubioOnset *onset;
       void setOnset(ofxAubioOnset & onset);
       ofxAubioBeat *beat;
       void setBeat(ofxAubioBeat & beat);
       ofxAubioMelBands *bands;
       void setBands(ofxAubioMelBands & bands);

       int currentClass;
       std::vector<float *>energies;

       void setup();
       void setup(std::string method, int buf_s, int hop_s, int samplerate);

       void audioIn(float *input, int bufferSize, int nChannels);

       void onsetClassify();
       void beatClassify();

       int lag_onset;
       int lag_beat;
       int min_band_onset;
       int min_band_beat;
    private:
       int startOnsetSelection;
       int startBeatSelection;
       void blockAudioIn();
};
