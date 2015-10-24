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
    hop_size = (uint_t)hop_s;
    buf_size = (uint_t)buf_s;
    pitch = new_aubio_pitch((char_t*)method.c_str(),
                            buf_size, hop_size, samplerate);
    aubio_pitch_set_unit(pitch, (char_t*)"midi");
    aubio_input = new_fvec(hop_size);
    aubio_output = new_fvec(1);
    curpos = 0;
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
    //if (pitch) del_aubio_pitch(Pitch);
}

void ofxAubioPitch::audioIn(float * input, int bufferSize, int nChannels)
{
    uint_t i, j;
    for (i = 0; i < bufferSize; i++) {
        // downmix into aubio_input
        aubio_input->data[curpos] = 0.;
        for (j = 0; j < nChannels; j++) {
            aubio_input->data[curpos] += input[ (curpos + i) * nChannels + j];
        }
        aubio_input->data[curpos] /= nChannels;
        // run aubio block when appropriate
        if (curpos == hop_size - 1)
        {
            blockAudioIn();
            curpos = -1;
        }
        curpos += 1;
    }
}

void ofxAubioPitch::blockAudioIn()
{
    aubio_pitch_do(pitch, aubio_input, aubio_output);
    if (aubio_output->data[0]) {
        //ofLogNotice() << "found pitch: " << aubio_output->data[0];
        latestPitch = aubio_output->data[0];
    }
}
