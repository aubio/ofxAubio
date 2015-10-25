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
#include "ofxAubioBlock.h"

class ofxAubioPitch : public ofxAubioBlock {

    public:

       ofxAubioPitch();
       ~ofxAubioPitch();

       void setup();
       void setup(std::string method, int buf_s, int hop_s, int samplerate);

       float latestPitch;
       float pitchConfidence;

    protected:
       void blockAudioIn();
       // aubio stuff
       aubio_pitch_t * pitch;
};
