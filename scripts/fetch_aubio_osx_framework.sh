#! /bin/sh

AUBIO_VERSION=0.4.2
AUBIO_ZIPFRAM=aubio-$AUBIO_VERSION.darwin_framework.zip
AUBIO_FRAMPATH=${AUBIO_ZIPFRAM%%.zip}

set -e
set -x

rm -rf $AUBIO_ZIPFRAM example_aubioDemo/$AUBIO_FRAMPATH
curl -O http://aubio.org/bin/$AUBIO_VERSION/$AUBIO_ZIPFRAM
unzip -x $AUBIO_ZIPFRAM -d example_aubioDemo/
open example_aubioDemo/$AUBIO_FRAMPATH
