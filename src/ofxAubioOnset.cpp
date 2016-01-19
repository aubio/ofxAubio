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

#include "ofxAubioOnset.h"
#include "ofLog.h"

ofEvent<float> ofxAubioOnset::gotGlobalOnset = ofEvent<float>();

ofxAubioOnset::ofxAubioOnset()
{
}

void ofxAubioOnset::setup()
{
    setup("default", 512, 256, 44100);
}

void ofxAubioOnset::setup(string method, int buf_s, int hop_s, int samplerate)
{
    ofxAubioBlock::setup(method, buf_s, hop_s, samplerate);
    onset = new_aubio_onset((char_t*)method.c_str(),
                            buf_size, hop_size, samplerate);
    if (onset) {
        threshold = aubio_onset_get_threshold(onset);
        ofLogNotice() << "created ofxAubioOnset(" << method
          << ", " << buf_size
          << ", " << hop_size
          << ", " << samplerate
          << ")";
    }
}

ofxAubioOnset::~ofxAubioOnset()
{
    if (onset) del_aubio_onset(onset);
    cleanup();
    ofLogNotice() << "deleted ofxAubioOnset";
}

void ofxAubioOnset::blockAudioIn()
{
    aubio_onset_do(onset, aubio_input, aubio_output);
    if (aubio_output->data[0]) {
        //ofLogNotice() << "found onset";
        float last_onset = aubio_onset_get_last_s(onset);
        ofNotifyEvent(gotOnset, last_onset, this);
        ofNotifyEvent(gotGlobalOnset, last_onset);
    }
    novelty = aubio_onset_get_descriptor(onset);
    thresholdedNovelty = aubio_onset_get_thresholded_descriptor(onset);
}

void ofxAubioOnset::setThreshold(float newThreshold)
{
    aubio_onset_set_threshold(onset, newThreshold);
    threshold = newThreshold;
}
