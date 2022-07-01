#include<math.h>
// LCD module connections
sbit LCD_RS at PORTD2_bit;
sbit LCD_EN at PORTD3_bit;
sbit LCD_D4 at PORTD4_bit;
sbit LCD_D5 at PORTD5_bit;
sbit LCD_D6 at PORTD6_bit;
sbit LCD_D7 at PORTD7_bit;

sbit LCD_RS_Direction at DDD2_bit;
sbit LCD_EN_Direction at DDD3_bit;
sbit LCD_D4_Direction at DDD4_bit;
sbit LCD_D5_Direction at DDD5_bit;
sbit LCD_D6_Direction at DDD6_bit;
sbit LCD_D7_Direction at DDD7_bit;
// End LCD module connections

char txt1[] = "Welcome to SEDMACH";
char txt2[] = "Continuity Tester";
char txt3[] = "Demonstration";
char txt4[] = "By Mr. Vivek Sutar";



void Move_Delay() {                  // Function used for text moving
  Delay_ms(100);                     // You can change the moving speed here
}



void main()
{
  int pc, i; int in,m,shifter,tmp1,tmp2,counter,loc[8]={0},cross;
  char ch[10];


  Lcd_Init();                        // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  DDRB = 0b11111111; // set portB as output port to send data
  DDRC = 0b00000000; // set portC as input port to scan pinx
  DDRA = 0b11111111;


  Lcd_Out(1,1,txt1);                 // Write text in first row
  Lcd_Out(2,1,txt2);                 // Write text in second row
  Delay_ms(100);
  Lcd_Cmd(_LCD_CLEAR);               // Clear display

  Lcd_Out(1,1,txt3);                 // Write text in first row
  Lcd_Out(2,1,txt4);                 // Write text in second row
  Delay_ms(100);
  Lcd_Cmd(_LCD_CLEAR);               // Clear display

  Lcd_Out(1,1,"Please connect ");                 // Write text in first row
  Lcd_Out(2,1,"Harness**");                 // Write text in first row
  Delay_ms(100);
  Lcd_Cmd(_LCD_CLEAR);

   PORTA = 0x00;  //clearing port a
  while(1)
  {
                portc = 0xff;

                    portb = 0b00000000;
                    pc = pinc;
                          if(pc == 0x00)
                          {             tmp1 = 0x01;
                                        counter = 0;
                                        for(i=0;i<8;i++)
                                        {
                                          portb = tmp1<<i;
                                         // porta = portb;
                                            if(pinc == portb)
                                            {
                                             //Lcd_Cmd(_LCD_CLEAR);
                                             inttostr(i+1,ch);
                                             Lcd_Out(1,1,"Please wait.. !");                 // Write text in second row
                                             Lcd_Out(2,i,"...");
                                             delay_ms(10);
                                          //   Lcd_Cmd(_LCD_CLEAR);
                                             if(i==7)
                                             {Lcd_Out(3,1,"all ok!");                 // Write text in second row
                                             Lcd_Out(4,1,"Waiting for next!");
                                             Delay_ms(10);                                             }
                                             //Lcd_Cmd(_LCD_CLEAR);
                                            }

                                            else
                                            {
                                                  tmp1 = pinc^portb;
                                                  
                                                  shifter = 0x01;
                                                  counter = 0;
                                                  //tmp1 = m;
                                                  for(i=0;i<8;i++)
                                                  {
                                                      tmp2 = (tmp1>>i) & shifter;
                                                      if(tmp2 == 0x1)
                                                      {
                                                      cross = tmp2;
                                                      counter++;
                                                      loc [i] = counter*tmp2;
                                                      }
                                                      else
                                                      { counter = counter+1; loc[i] = counter*tmp2;}
                                                  }

                                                  
                                                  in = 0;
                                                   for(i=0;i<8;i++)
                                                   {
                                                    if(loc[i] !=0)
                                                    {
                                                        in =  loc[i];
                                                      //  porta = in;
                                                        IntToStr(in,ch);
                                                     // Lcd_Cmd(_LCD_CLEAR);
                                                        Lcd_Out(3,1,"crossed at :");

                                                        Lcd_Out(3,13,ch);                 // Write text in second row
                                                        delay_ms(100);

                                                    }

                                                   }
                                            }

                                        
                                        }
                                        
                                        


                          }
                    else
                    {
                     m = pinc;
                        shifter = 0x01;
                        counter = 0;
                        tmp1 = m;
                        for(i=0;i<8;i++)
                        {
                            tmp1 = (m>>i) & shifter;
                            if(tmp1 == 0x1)
                            {counter++;}
                            else
                            {counter = counter; }
                        }
                         IntToStr(counter,ch);
                          //if(pc == m)
                          {
                          //Lcd_Cmd(_LCD_CLEAR);
                          Lcd_Out(1,1,"Faulty");                 // Write text in second row
                          Lcd_Out(2,1,"No faults");
                          Lcd_Out(2,11,ch);                 // Write text in second row
                          Delay_ms(100);
                         // Lcd_Cmd(_LCD_CLEAR);
                          }

                        shifter = 0x01;
                        counter = 0;
                        tmp1 = m;
                        for(i=0;i<8;i++)
                        {
                            tmp1 = (m>>i) & shifter;
                            if(tmp1 == 0x1)
                            {
                            counter++;
                            loc [i] = counter*tmp1;
                            }
                            else
                            {counter = counter+1; loc[i] = counter*tmp1;}
                        }

                         in = 0;
                         for(i=0;i<8;i++)
                         {
                          if(loc[i] !=0)
                          {
                              in =  loc[i];
                              porta = in;
                              IntToStr(in,ch);
                           // Lcd_Cmd(_LCD_CLEAR);
                              Lcd_Out(3,1,"Location:");
                              Lcd_Out(3,11,ch);                 // Write text in second row
                              Delay_ms(90);

                          }
                          //Lcd_Cmd(_LCD_CLEAR);
                         }
                          Lcd_Cmd(_LCD_CLEAR);
                      }

    }
  }