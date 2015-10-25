ofxAubio
========

ofxAubio is an [openFrameworks](openframeworks.cc) [addon](www.ofxaddons.com)
for [aubio](aubio.org).

Install
-------

### MacOSX

Fetch `ofxAubio` and `aubio.framework` from inside your openFrameworks root:

    $ cd /path/to/of_root/addons
    $ git clone git://git.aubio.org/git/ofxAubio/
    $ cd ofxAubio
    $ ./scripts/fetch_aubio_framework.sh

Select projectGenerator, select 'update project', then select the path of
`example_aubioDemo`, `/path/to/of_root/addons/ofxAubio/example_aubioDemo`.

Open `example_aubioDemo.xcodeproject`, drag `aubio.framework` into to it,
placing it in `frameworks / 3rd party frameworks`.

Project Homepage
----------------

The home page of aubio can be found at: http://aubio.org/ofxAubio/

Copyright and License Information
---------------------------------

Copyright (C) 2003-2015 Paul Brossier <piem@aubio.org>

ofxAubio is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
