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

#include "ofxAubioBeat.h"
#include "ofLog.h"

ofEvent<float> ofxAubioBeat::gotGlobalBeat = ofEvent<float>();

ofxAubioBeat::ofxAubioBeat()
{
}

void ofxAubioBeat::setup()
{
    setup("default", 512, 256, 44100);
}

void ofxAubioBeat::setup(string method, int buf_s, int hop_s, int samplerate)
{
    ofxAubioBlock::setup(method, buf_s, hop_s, samplerate);
    tempo = new_aubio_tempo((char_t*)method.c_str(),
                            buf_size, hop_size, samplerate);
    aubio_tempo_set_silence(tempo, -40);
    if (tempo) {
        ofLogNotice() << "created ofxAubioBeat(" << method
          << ", " << buf_size
          << ", " << hop_size
          << ", " << samplerate
          << ")";
    }
}

ofxAubioBeat::~ofxAubioBeat()
{
    if (tempo) del_aubio_tempo(tempo);
    cleanup();
    ofLogNotice() << "deleted ofxAubioBeat";
}

void ofxAubioBeat::blockAudioIn()
{
    aubio_tempo_do(tempo, aubio_input, aubio_output);
    if (aubio_output->data[0]) {
        //ofLogNotice() << "found beat: " << aubio_output->data[0];
        bpm = aubio_tempo_get_bpm(tempo);
        float last_beat = aubio_tempo_get_last_s(tempo);
        ofNotifyEvent(gotBeat, last_beat, this);
        ofNotifyEvent(gotGlobalBeat, last_beat);
    }
}
