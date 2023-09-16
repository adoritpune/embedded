/* 
 * File:   function.h
 * Author: MV01
 *
 * Created on March 19, 2016, 11:35 AM
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
void system_init(void);
void portpin_init(void);
void Delayms(unsigned int);
void Display(void);
void latchdata(unsigned int num);
void disp_hex_window1(unsigned int hex_data);
void disp_hex_window2(unsigned int hex_data);
void read_key(void);
void Timer0_init(void);
void key_application(unsigned char keypress);
void send_status();
unsigned char SCANENCODER1();
unsigned char SCANENCODER2();
unsigned char enc1_port();
unsigned char enc2_port();
void PWM_init();
void Update_PWM(unsigned int Current);
void capture_init();
void uart_init();
void Send_Byte(unsigned char transbyte);
void Send_Num(unsigned int transnum);
void second_order_pid();
void transmittops();

void disp_hex_window11(unsigned int hex_data);
void disp_hex_window22(unsigned int hex_data);
void detect_display_error(void);

#endif	/* FUNCTION_H */

