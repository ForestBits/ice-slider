#ifndef AUDIODATA_H
#define AUDIODATA_H

namespace ice {

struct AudioData
{
    //[0, 1]
    double soundVolume = 1;

    //[0, 1]
    double musicVolume = 1;

    //[0, 1]
    double globalVolume = 1;
};

}

#endif