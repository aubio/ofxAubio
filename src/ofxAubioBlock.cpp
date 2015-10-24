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

#include "ofxAubioBlock.h"

void ofxAubioBlock::audioIn(float * input, int bufferSize, int nChannels)
{
    uint_t i, j;
    for (i = 0; i < bufferSize; i++) {
        // downmix into aubio_input
        aubio_input->data[curpos] = 0.;
        for (j = 0; j < nChannels; j++) {
            aubio_input->data[curpos] += input[i * nChannels + j];
        }
        aubio_input->data[curpos] /= (smpl_t)nChannels;
        // run aubio block when appropriate
        curpos += 1;
        if (curpos == hop_size)
        {
            blockAudioIn();
            curpos = 0;
        }
    }
}
