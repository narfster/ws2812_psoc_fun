/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define GREEN 4
#define LIGHTGREEN 28
#define YELLOW 0
#define LIGHTRED 40 
#define RED 72
#define BLACK 24

/* Customized brightness lookup */
uint32 CustomLookup[256] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000028,0x0000002C,0x00000031,0x00000035,0x00000039,0x0000003E,0x00000042,0x00000046,0x0000004A,0x0000004F,0x00000053,0x00000057,0x0000005C,0x00000060,0x00000064,0x00000069,0x0000006D,0x00000071,0x00000075,0x0000007A,0x0000007E,0x00000082,0x00000087,0x0000008B,0x0000008F,0x00000094,0x00000098,0x0000009C,0x000000A0,0x000000A5,0x000000A9,0x000000AD,0x000000B2,0x000000B6,0x000000BA,0x000000BF,0x000000C3,0x000000C7,0x000000CB,0x000000D0,0x000000D4,0x000000D8,0x000000DD,0x000000E1,0x000000E5,0x000000EA,0x000000EE,0x000000F2,0x000000F6,0x000000FF,0x00000010,0x00000011,0x00000013,0x00000014,0x00000016,0x00000017,0x00000018,0x0000001A,0x0000001B,0x0000001C,0x0000001E,0x0000001F,0x00000021,0x00000022,0x00000023,0x00000025,0x00000026,0x00000027,0x00000029,0x0000002A,0x0000002C,0x0000002D,0x0000002E,0x00000030,0x00000031,0x00000033,0x00000034,0x00000035,0x00000037,0x00000038,0x00000039,0x0000003B,0x0000003C,0x0000003E,0x0000003F,0x00000040,0x00000042,0x00000043,0x00000044,0x00000046,0x00000047,0x00000049,0x0000004A,0x0000004B,0x0000004D,0x0000004E,0x0000004F,0x00000051,0x00000052,0x00000055,0x000000,0x00000505,0x00000A0A,0x00000F0F,0x00001414,0x00001A1A,0x00001F1F,0x00002424,0x00002929,0x00002E2E,0x00003333,0x00003838,0x00003D3D,0x00004242,0x00004747,0x00004D4D,0x00005252,0x00005757,0x00005C5C,0x00006161,0x00006666,0x00006B6B,0x00007070,0x00007575,0x00007A7A,0x00008080,0x00008585,0x00008A8A,0x00008F8F,0x00009494,0x00009999,0x00009E9E,0x0000A3A3,0x0000A8A8,0x0000ADAD,0x0000B3B3,0x0000B8B8,0x0000BDBD,0x0000C2C2,0x0000C7C7,0x0000CCCC,0x0000D1D1,0x0000D6D6,0x0000DBDB,0x0000E0E0,0x0000E6E6,0x0000EBEB,0x0000F0F0,0x0000F5F5,0x0000FFFF,0x00001000,0x00001100,0x00001300,0x00001400,0x00001600,0x00001700,0x00001800,0x00001A00,0x00001B00,0x00001C00,0x00001E00,0x00001F00,0x00002100,0x00002200,0x00002300,0x00002500,0x00002600,0x00002700,0x00002900,0x00002A00,0x00002C00,0x00002D00,0x00002E00,0x00003000,0x00003100,0x00003300,0x00003400,0x00003500,0x00003700,0x00003800,0x00003900,0x00003B00,0x00003C00,0x00003E00,0x00003F00,0x00004000,0x00004200,0x00004300,0x00004400,0x00004600,0x00004700,0x00004900,0x00004A00,0x00004B00,0x00004D00,0x00004E00,0x00004F00,0x00005100,0x00005200,0x00005500,0x00001400,0x00001900,0x00001D00,0x00002200,0x00002700,0x00002C00,0x00003000,0x00003500,0x00003A00,0x00003E00,0x00004300,0x00004800,0x00004C00,0x00005100,0x00005600,0x00005B00,0x00005F00,0x00006400,0x00006900,0x00006D00,0x00007200,0x00007700,0x00007B00,0x00008000,0x00008500,0x00008A00,0x00008E00,0x00009300,0x00009800,0x00009C00,0x0000A100,0x0000A600,0x0000AA00,0x0000AF00,0x0000B400,0x0000B900,0x0000BD00,0x0000C200,0x0000C700,0x0000CB00,0x0000D000,0x0000D500,0x0000D900,0x0000DE00,0x0000E300,0x0000E800,0x0000EC00,0x0000F100,0x0000F600,0x0000FF00};


void WritetoLED(uint8 row, uint8 value);

extern const uint32 StripLights_CLUT[ ];
extern uint32  StripLights_ledArray[StripLights_ROWS][StripLights_COLUMNS];

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void user_btn_isr()
{
    USER_BTN_ClearInterrupt();
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void run_display1()
{
    uint32_t color = 0x0;
    for(int i = 0; i < 64; ++i)
    {
        //StripLights_DisplayClear(getColor(color));
        StripLights_Pixel(i,0,getColor(color));
        StripLights_Trigger(1);
        CyDelay(20);
        
        color += 1;
        if(color > StripLights_CWHEEL_SIZE)
        {
            color = 0;
        }
    }

}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void run_display2()
{
    
    uint32_t color = 0x0;
    for (int i = 0; i < 100; ++i)
    {
        StripLights_MemClear(getColor(color));
        StripLights_Trigger(1);
        while( StripLights_Ready() == 0);
        
        color += 1;
        if(color > StripLights_CWHEEL_SIZE)
        {
            color = 0;
        }
        
        CyDelay(20);
    }
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int main()
{
	
	/* Start Neopixel driver */
	StripLights_Start();
    
    isr_1_StartEx(user_btn_isr);

	StripLights_Dim(StripLights_DimLevel_4);
	/* Enable All interrupts */
    CyGlobalIntEnable; 
    
    for(;;)
    {
        static int i = 0;
        switch (i)
        {
            case 0:
                run_display1();
            break;
            
            case 1:
                run_display2();
            break;
        }

        i++;
        i = i % 2;
        

        // Clear screen
        StripLights_MemClear(getColor(BLACK));
        StripLights_Trigger(1);
        while( StripLights_Ready() == 0);

        StripLights_Stop();
        CySysPmDeepSleep();
        StripLights_Start();
        StripLights_Dim(StripLights_DimLevel_4);

	}
}
