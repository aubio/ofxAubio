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

using namespace std;

class ofxAubioPitch {

    public:

       ofxAubioPitch();
       ~ofxAubioPitch();

       void setup();
       void setup(string method, int buf_s, int hop_s, int samplerate);

       void audioIn(float *input, int bufferSize, int nChannels);

       float latestPitch;

    private:
       void blockAudioIn();
       // aubio stuff
       uint_t buf_size;
       uint_t hop_size;
       fvec_t * aubio_input;
       fvec_t * aubio_output;
       aubio_pitch_t * pitch;
       uint_t curpos;

};
