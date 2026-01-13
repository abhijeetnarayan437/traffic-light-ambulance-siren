#include "arm_math.h"

#define FFT_SIZE 1024

static float fftIn[FFT_SIZE];
static float fftOut[FFT_SIZE];

void DSP_RunFFT(int16_t *input)
{
    for (int i = 0; i < FFT_SIZE; i++)
        fftIn[i] = (float)input[i];

    arm_rfft_fast_instance_f32 fft;
    arm_rfft_fast_init_f32(&fft, FFT_SIZE);
    arm_rfft_fast_f32(&fft, fftIn, fftOut, 0);
}

float DSP_GetDominantFreq(void)
{
    float max = 0;
    int index = 0;

    for (int i = 10; i < FFT_SIZE/2; i++)
    {
        if (fftOut[i] > max)
        {
            max = fftOut[i];
            index = i;
        }
    }

    return (index * 16000.0f) / FFT_SIZE;
}
