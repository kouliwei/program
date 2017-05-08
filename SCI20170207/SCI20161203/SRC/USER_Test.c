#include "USER_Test.h"

#if	DEBUG == 0
extern void Test(void)
{
	uint8_t ch;
    uint8_t exit_flag = 0;
    uint8_t flag = 0;
    while(1)
    {
		if(0 == flag){
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
			Sci_Send("\r\n**************welcome to the menu****************\r\n",'A');
			Sci_Send("press a or A to enter the communication test\r\n",'A');
			Sci_Send("press b or B to enter the Led test\r\n",'A');
			Sci_Send("press c or C to enter the Key test \r\n",'A');
			Sci_Send("press d or D to enter the pwm test \r\n",'A');
			Sci_Send("press e or E to exit the menu\r\n",'A');
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
			Sci_Send("\r\n**************welcome to the menu****************\r\n",'B');
			Sci_Send("press a or A to enter the communication test\r\n",'B');
			Sci_Send("press b or B to enter the Led test\r\n",'B');
			Sci_Send("press c or C to enter the Key test \r\n",'B');
			Sci_Send("press d or D to enter the pwm test \r\n",'B');
			Sci_Send("press e or E to exit the menu\r\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
			Sci_Send("\r\n**************welcome to the menu****************\r\n",'C');
			Sci_Send("press a or A to enter the communication test\r\n",'C');
			Sci_Send("press b or B to enter the Led test\r\n",'C');
			Sci_Send("press c or C to enter the Key test \r\n",'C');
			Sci_Send("press d or D to enter the pwm test \r\n",'C');
			Sci_Send("press e or E to exit the menu\r\n",'C');
#endif

		flag = 1;
		}
		ch = SCI_Return();



        switch(ch){
            case 'a':
            case 'A':
                Commu_Test();
                flag = 0;
                break;
            case 'b':
            case 'B':
                Led_Test();
                flag = 0;
                break;
            case 'c':
            case 'C':
                Key_Test();
                flag = 0;
                break;
            case 'd':
            case 'D':
            	Pwm_Test();
                flag = 0;
                break;
            case 'e':
            case 'E':
            	Game_Over();
                exit_flag = 1;
                break;
        }
        if(exit_flag == 1)
            break;
    }

}

static void Led_Test(void)
 {
     uint8_t ch = 0;
     uint8_t exit_flag = 0;
     while(1){

#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
    	 Sci_Send("\r\n******welcome to the Led_Test *********\r\n",'A');
    	 Sci_Send("press a or A to the drive the led_mode1\r\n",'A');
    	 Sci_Send("press w or W to the drive the led_mode2\r\n",'A');
    	 Sci_Send("press e or E to exit the Led_Test\r\n",'A');
#endif
#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
    	 Sci_Send("\r\n******welcome to the Led_Test *********\r\n",'B');
    	 Sci_Send("press a or A to the drive the led_mode1\r\n",'B');
    	 Sci_Send("press w or W to the drive the led_mode2\r\n",'B');
    	 Sci_Send("press e or E to exit the Led_Test\r\n",'B');
#endif
#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
    	 Sci_Send("\r\n******welcome to the Led_Test *********\r\n",'C');
    	 Sci_Send("press a or A to the drive the led_mode1\r\n",'C');
    	 Sci_Send("press w or W to the drive the led_mode2\r\n",'C');
    	 Sci_Send("press e or E to exit the Led_Test\r\n",'C');
#endif
    	 ch = SCI_Return();


         switch(ch){
             case 'a':
             case 'A':
                 Led_Mode1();
                 break;
             case 'w':
             case 'W':
                 Led_Mode2();
                 break;
             case 'e':
             case 'E':
            	 Game_Over_Led();
                 exit_flag = 1;
         }
         if(exit_flag == 1)
             break;
     }
}


/**********ÅÜÂíµÆÄ£Ê½***************/
void Led_Mode1()
{
    uint8_t i = 0;
    for(i = 0;i < 4; i++)
    {
        switch(i)
        {
            case 0:
                Led_Drive(0x01);
                break;
            case 1:
                Led_Drive(0x02);
                break;
            case 2:
                Led_Drive(0x04);
                break;
            case 3:
                Led_Drive(0x08);
                break;
        }
        Delay_Nms(500);
    }
}

/*********È«ÁÁÈ«ÃðÄ£Ê½**************/
void Led_Mode2()
{
    uint8_t i = 0;
    for(i = 0;i < 4;i ++)
    {
        if(i % 2)
        {
            Led_Drive(0x0f);
        }
        else
        {
            Led_Drive(0x00);
        }
        Delay_Nms(500);
    }
}

static void Commu_Test()
{

}


static void Key_Test()
{
	uint8_t ch = 0;
	uint8_t data = 0;

#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
	Sci_Send("press e or E to exit the Key_Test\r\n",'A');
#endif
#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
	Sci_Send("press e or E to exit the Key_Test\r\n",'B');
#endif
#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	Sci_Send("press e or E to exit the Key_Test\r\n",'C');
#endif

	while(1)
	{
		if(EFF_KEY4())
		{
			data |= 0x01;
		}
		else
		{
			data &= ~(0x01);
		}
		if(EFF_KEY3())
		{
			data |= 0x02;
		}
		else
		{
			data &= ~(0x02);
		}
		if(EFF_KEY2())
		{
			data |= 0x04;
		}
		else
		{
			data &= ~(0x04);
		}
		if(EFF_KEY1())
		{
			data |= 0x08;
		}
		else
		{
			data &= ~(0x08);
		}
		Delay_Nms(1000);

#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
		TXD_USART_BIN('A',data);
		if(SciaRegs.SCIRXST.bit.RXRDY ==1)
		{
			ch = SciaRegs.SCIRXBUF.all;
			if(ch == 'e' || ch == 'E')
			{
				Game_Over_Key();
				break;
			}

		}
#endif
#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
		TXD_USART_BIN('B',data);
		if(ScibRegs.SCIRXST.bit.RXRDY ==1)
		{
			ch = ScibRegs.SCIRXBUF.all;
			if(ch == 'e' || ch == 'E')
			{
				Game_Over_Key();
				break;
			}
		}
#endif
#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
		TXD_USART_BIN('C',data);
		if(ScicRegs.SCIRXST.bit.RXRDY ==1)
		{
			ch = ScicRegs.SCIRXBUF.all;
			if(ch == 'e' || ch == 'E')
			{
				Game_Over_Key();
				break;
			}

		}
#endif
	}

}


static void Pwm_Test()
{
	 uint8_t ch = 0;
     uint8_t exit_flag = 0;
     Uint16 high_level = 3500;
     while(1){
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
    	 Sci_Send("\r\n******welcome to the Pwm_Test *********\r\n",'A');
    	 Sci_Send("press d or D to stop         \r\n",'A');
    	 Sci_Send("press w or W to forward max  \r\n",'A');
    	 Sci_Send("press s or S to backward max \r\n",'A');
    	 Sci_Send("press q or Q to slow down    \r\n",'A');
    	 Sci_Send("press r or R to speedup      \r\n",'A');
    	 Sci_Send("press e or E to exit Pwm test\r\n",'A');

#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
    	 Sci_Send("\r\n******welcome to the Pwm_Test *********\r\n",'B');
    	 Sci_Send("press d or D to stop         \r\n",'B');
    	 Sci_Send("press w or W to forward max  \r\n",'B');
    	 Sci_Send("press s or S to backward max \r\n",'B');
    	 Sci_Send("press q or Q to slow down    \r\n",'B');
    	 Sci_Send("press r or R to speedup      \r\n",'B');
    	 Sci_Send("press e or E to exit Pwm test\r\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
    	 Sci_Send("\r\n******welcome to the Pwm_Test *********\r\n",'C');
    	 Sci_Send("press d or D to stop         \r\n",'C');
    	 Sci_Send("press w or W to forward max  \r\n",'C');
    	 Sci_Send("press s or S to backward max \r\n",'C');
    	 Sci_Send("press q or Q to slow down    \r\n",'C');
    	 Sci_Send("press r or R to speedup      \r\n",'C');
    	 Sci_Send("press e or E to exit Pwm test\r\n",'C');

#endif
    	 ch = SCI_Return();


         switch(ch){
             case 'd':
             case 'D':
            	 high_level = 3500;
                 break;
             case 'w':
             case 'W':
            	 high_level = 4500;
                 break;
             case 's':
             case 'S':
            	 high_level = 2500;
                 break;
             case 'r':
             case 'R':
				high_level += 100;
				if(high_level >= 4500)
				{
					high_level = 4500;
				}
				break;
             case 'q':
             case 'Q':
				high_level -= 100;
				if(high_level <= 2500)
				{
					high_level = 2500;
				}
				break;
             case 'e':
             case 'E':
                 Game_Over_Pwm();
                 exit_flag = 1;
                 break;
         }
         EPwmSetup1(high_level);
         if(exit_flag == 1)
         {
        	 high_level = 3500;
        	 EPwmSetup1(high_level);
        	 break;
         }
     }

}

static uint8_t SCI_Return(void)
{
	uint8_t ch = 0;

#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
        while(SciaRegs.SCIRXST.bit.RXRDY !=1){}
        ch = SciaRegs.SCIRXBUF.all;
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
        while(ScibRegs.SCIRXST.bit.RXRDY !=1){}
	    ch = ScibRegs.SCIRXBUF.all;
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	    while(ScicRegs.SCIRXST.bit.RXRDY !=1){}
	    ch = ScicRegs.SCIRXBUF.all;
#endif
	    return ch;

}

static void Game_Over(void)
{
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
	Sci_Send("test over\t\n",'A');
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
	Sci_Send("test over\t\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	Sci_Send("test over\t\n",'C');
#endif
}

static void Game_Over_Led(void)
{
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
	Sci_Send("exit the Led_Test Led\r\n",'A');
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
	Sci_Send("exit the Led_Test Led\r\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	Sci_Send("exit the Led_Test Led\r\n",'C');
#endif
}

static void Game_Over_Key(void)
{
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
	Sci_Send("exit the Key_Test Led\r\n",'A');
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
	Sci_Send("exit the Key_Test Led\r\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	Sci_Send("exit the Key_Test Led\r\n",'C');
#endif
}

static void Game_Over_Pwm(void)
{
#if	DEBUG_SHOW == 'A' || DEBUG_SHOW == 'a'
	Sci_Send("exit the Pwm_Test Led\r\n",'A');
#endif

#if	DEBUG_SHOW == 'B' || DEBUG_SHOW == 'b'
	Sci_Send("exit the Pwm_Test Led\r\n",'B');
#endif

#if	DEBUG_SHOW == 'C' || DEBUG_SHOW == 'c'
	Sci_Send("exit the Pwm_Test Led\r\n",'C');
#endif
}


#endif
