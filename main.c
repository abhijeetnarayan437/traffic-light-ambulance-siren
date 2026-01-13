#include "main.h"
#include "audio.h"
#include "siren.h"
#include "traffic_fsm.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2S2_Init();
    MX_DMA_Init();
    MX_TIM2_Init();
    MX_IWDG_Init();

    Audio_Start();
    TrafficFSM_Init();

    while (1)
    {
        IWDG_Refresh();  // failsafe

        if (Audio_BufferReady())
        {
            Siren_ProcessAudio(Audio_GetBuffer());
        }

        TrafficFSM_Update();
    }
}
