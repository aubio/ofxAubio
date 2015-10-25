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

#include "ofxAubioPitch.h"
#include "ofLog.h"

ofxAubioPitch::ofxAubioPitch()
{
}

void ofxAubioPitch::setup()
{
    setup("default", 2048, 256, 44100);
}

void ofxAubioPitch::setup(string method, int buf_s, int hop_s, int samplerate)
{
    ofxAubioBlock::setup(method, buf_s, hop_s, samplerate);
    pitch = new_aubio_pitch((char_t*)method.c_str(),
                            buf_size, hop_size, samplerate);
    aubio_pitch_set_unit(pitch, (char_t*)"midi");
    //aubio_pitch_set_tolerance(pitch, 0.7);
    if (pitch) {
        ofLogNotice() << "created ofxAubioPitch(" << method
          << ", " << buf_size
          << ", " << hop_size
          << ", " << samplerate
          << ")";
    }
}

ofxAubioPitch::~ofxAubioPitch()
{
    if (pitch) del_aubio_pitch(pitch);
    cleanup();
    ofLogNotice() << "deleted ofxAubioPitch";
}

void ofxAubioPitch::blockAudioIn()
{
    aubio_pitch_do(pitch, aubio_input, aubio_output);
    //ofLogNotice() << "found pitch: " << aubio_output->data[0];
    pitchConfidence = aubio_pitch_get_confidence(pitch);
    latestPitch = aubio_output->data[0];
}
