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

#include <math.h>
#define LIN2DB(v) (20.0*log10f(v))

#include "ofxAubioFilterDetect.h"
#include "ofLog.h"

ofxAubioFilterDetect::ofxAubioFilterDetect()
    : bands(NULL)
{
    lag = 50;
}

ofxAubioFilterDetect::~ofxAubioFilterDetect()
{
}

void ofxAubioFilterDetect::setup()
{
    setup("default", 512, 256, 44100);
}
void ofxAubioFilterDetect::setup(string method, int buf_s, int hop_s, int samplerate)
{
    hop_size = hop_s;
    buf_size = buf_s;
}

void ofxAubioFilterDetect::setBands(ofxAubioMelBands & _bands) {
    bands = &_bands;
}

void ofxAubioFilterDetect::audioIn(float * input, int bufferSize, int nChannels)
{
    uint_t i;
    for (i = 0; i < bufferSize; i++) {
        // run aubio block when appropriate
        curpos += 1;
        if (curpos == hop_size)
        {
            blockAudioIn();
            curpos = 0;
        }
    }
}

void ofxAubioFilterDetect::blockAudioIn() {
    energies.push_back(bands->energies);
    if (energies.size() > lag) {
        energies.erase (energies.begin());
    }
    filterDetect();
}

void ofxAubioFilterDetect::filterDetect() {
    if (energies.size() >= lag) {
        max_low_cutoff = 0;
        for (int i = 0; i < bands->nBands; i ++) {
            float band_sum = 0;
            for (int j = 0; j < lag; j ++) {
                band_sum += (energies[energies.size() - j - 1][i]);
            }
            if (band_sum < 0.01) {
                max_low_cutoff = i;
            } else {
                break;
            }
        }
        min_high_cutoff = 0;
        for (int i = bands->nBands - 1; i >= 0; i --) {
            float band_sum = 0;
            for (int j = 0; j < lag; j ++) {
                band_sum += (energies[energies.size() - j - 1][i]);
            }
            if (band_sum < 0.0001) {
                min_high_cutoff = bands->nBands - 1 - i;
            } else {
                break;
            }
        }
        //ofLog() << "got min_high_cutoff: " << min_high_cutoff
        //    << " max_low_cutoff: " << max_low_cutoff;
    }
}
