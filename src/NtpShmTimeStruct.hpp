/**
 * Taken from http://doc.ntp.org/current-stable/drivers/driver28.html
 */

#pragma once

struct shmTime {
    int    mode; /* 0 - if valid is set:
                  *       use values,
                  *       clear valid
                  * 1 - if valid is set:
                  *       if count before and after read of data is equal:
                  *         use values
                  *       clear valid
                  */
    volatile int    count;
    time_t          clockTimeStampSec;
    int             clockTimeStampUSec;
    time_t          receiveTimeStampSec;
    int             receiveTimeStampUSec;
    int             leap;
    int             precision;
    int             nsamples;
    volatile int    valid;
    unsigned        clockTimeStampNSec;     /* Unsigned ns timestamps */
    unsigned        receiveTimeStampNSec;   /* Unsigned ns timestamps */
    int             dummy[8];
};
