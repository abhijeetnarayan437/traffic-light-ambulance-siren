#define AUDIO_BUF_SIZE 1024

static int16_t audioBuf[AUDIO_BUF_SIZE];
static volatile uint8_t bufferReady = 0;

void Audio_Start(void)
{
    HAL_I2S_Receive_DMA(&hi2s2, (uint16_t*)audioBuf, AUDIO_BUF_SIZE);
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    bufferReady = 1;
}

uint8_t Audio_BufferReady(void)
{
    if (bufferReady)
    {
        bufferReady = 0;
        return 1;
    }
    return 0;
}

int16_t* Audio_GetBuffer(void)
{
    return audioBuf;
}
