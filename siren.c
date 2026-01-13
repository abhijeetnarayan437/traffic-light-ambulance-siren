#include "siren.h"
#include "dsp.h"

static uint32_t sirenTime = 0;
static uint8_t sirenDetected = 0;

void Siren_ProcessAudio(int16_t *buffer)
{
    DSP_RunFFT(buffer);
    float freq = DSP_GetDominantFreq();

    if (freq > 500 && freq < 2000)
    {
        sirenTime += 100; // assuming 100ms buffer
        if (sirenTime >= 3000)
            sirenDetected = 1;
    }
    else
    {
        sirenTime = 0;
        sirenDetected = 0;
    }
}

uint8_t Siren_IsDetected(void)
{
    return sirenDetected;
}
