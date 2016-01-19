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

using namespace std;

class ofxAubioMelBands : public ofxAubioBlock {

    public:

       ofxAubioMelBands();
       ~ofxAubioMelBands();

       void setup();
       void setup(string method, int buf_s, int hop_s, int samplerate);

       int nBands;
       float *energies;

    private:
       void blockAudioIn();
       // aubio stuff
       aubio_pvoc_t *pv;
       cvec_t *spectrum;
       aubio_filterbank_t *fb;
       fvec_t *bands;
};
