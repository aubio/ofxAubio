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

#include "ofxAubioOnsetClass.h"
#include "ofLog.h"

ofEvent<int> ofxAubioOnsetClass::gotGlobalOnsetClass = ofEvent<int>();

ofxAubioOnsetClass::ofxAubioOnsetClass()
    : bands(NULL)
{
    lag = 3;
}

ofxAubioOnsetClass::~ofxAubioOnsetClass()
{
}

void ofxAubioOnsetClass::setup()
{
    setup("default", 512, 256, 44100);
}
void ofxAubioOnsetClass::setup(string method, int buf_s, int hop_s, int samplerate)
{
    //setup("default", 512, 256, 44100);
}

void ofxAubioOnsetClass::setBands(ofxAubioMelBands & _bands) {
    bands = &_bands;
}

void ofxAubioOnsetClass::setOnset(ofxAubioOnset & _onset) {
    onset = &_onset;
    ofAddListener(onset->gotOnset, this, &ofxAubioOnsetClass::onsetEvent);
}

void ofxAubioOnsetClass::audioIn()
{
    energies.push_back(bands->energies);
    if (energies.size() > lag - 1) {
        energies.erase (energies.begin());
    }
    // hack to add a counter to delay lag * blockSize frames
    if (startSelection > 0) {
        startSelection--;
        if (startSelection == 1) {
            onsetClassify();
        }
    }
}

void ofxAubioOnsetClass::onsetEvent(float & time)
{
    //ofLog() << "ofxAubioOnsetClass got onset at " << time;
    // hack to add a counter to delay lag * blockSize frames
    int delay = 0;
    startSelection = lag + delay;
}

void ofxAubioOnsetClass::onsetClassify() {
    if (energies.size() == lag - 1) {
        int max_band = 0;
        float max_energy = 0;
        for (int i = 0; i < bands->nBands; i ++) {
            float band_sum = 0;
            for (int j = 0; j < energies.size(); j ++) {
                band_sum += energies[j][i];
            }
            if (max_energy < band_sum) {
                max_energy = band_sum;
                max_band = i;
            }
        }
        currentClass = max_band;
        ofNotifyEvent(gotOnsetClass, currentClass, this);
        ofNotifyEvent(gotGlobalOnsetClass, currentClass);
    }
}
