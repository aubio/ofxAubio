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

#include "ofxAubioMelBands.h"
#include "ofLog.h"

ofxAubioMelBands::ofxAubioMelBands()
{
}

void ofxAubioMelBands::setup()
{
    setup("default", 512, 256, 44100);
}

void ofxAubioMelBands::setup(string method, int buf_s, int hop_s, int samplerate)
{
    ofxAubioBlock::setup(method, buf_s, hop_s, samplerate);
    nBands = 40;
    pv = new_aubio_pvoc(buf_s, hop_s);
    spectrum = new_cvec(buf_s);
    fb = new_aubio_filterbank(nBands, buf_s);
    aubio_filterbank_set_mel_coeffs_slaney(fb, samplerate);
    bands = new_fvec(nBands);
    energies = bands->data;

    if (pv && fb) {
        ofLogNotice() << "created ofxAubioMelBands(" << method
          << ", " << buf_size
          << ", " << hop_size
          << ", " << samplerate
          << ")";
    }
}

ofxAubioMelBands::~ofxAubioMelBands()
{
    if (spectrum) del_cvec(spectrum);
    if (pv) del_aubio_pvoc(pv);
    if (bands) del_fvec(bands);
    if (fb) del_aubio_filterbank(fb);
    cleanup();
    ofLogNotice() << "deleted ofxAubioMelBands";
}

void ofxAubioMelBands::blockAudioIn()
{
    aubio_pvoc_do(pv, aubio_input, spectrum);
    aubio_filterbank_do(fb, spectrum, bands);
}
