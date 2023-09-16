Hi i am a control engineer here is a simple anti wind up pid algorithm

int PID(int error_new)
{
//PID parameters
double Kp = 1//proportion term.
double Kd = 0.01// derivative
double Ki = 0.1// integral
double Tsampling = 0.001// 1kHz frequency, you must call this function by a timer interrupt or delays but i prefer interrupts allways
// you must set this sampling value correct if you want to match simulation results in real systems 
static int error_old = 0;
static double integral_old = 0;
int controller_out;// if pwm is not less than 16 bit resolution then this and return type can be long int (or simply multiply them by 2, 
// max int value 2^15 - 1 but pwm max is 2^16-1, so multiply controller output by 2 )

integral_new = integral_old + Ki*(error_new + error_old)*Tsampling/2 // Area of the trapezoid
if((integral_new > integral_max) || (integral_new < integral_min))// This is anti wind up protect
integral_new = integral_old;// in a control system if a parameter gets satured integral term winds up despite no change on the parameter
//for example you are driving a dc motor with a 48V power supply.
//In this case dc motor input voltage is saturated at +-48V.
//There is no meaning but worse results of keeping integral summing the error when H bridge is at full pwm.
//You can simply limit integral term rather than checking all system parameters saturation status that will result an integral wind up.

controller_out = Kp*error_new + Kd*(error_new-error_old)/Tsampling + integral_new;

integral_old = integral_new;
error_old = error_new;

return controller_out;// the sign of the controller output determines (for example) the transistor couples in conduct in an H bridge
// so in this case motor direction 
// absolute value must be taken before assigning pwm output 
}

If your feedback is analog then you need a digital low pass filter

#define alpha 0.01// when alpha close to 0 it is a very good but slow settlement time low pass filter
// to decrease settlement time you must sample adc input as fast as possible and so this filter algorithm
double filter_out_new;
static double filter_out_old = 0;
unsigned int adc_input_new;
static unsigned int adc_input_old = 0;

adc_input_new = ADC1BUF0;// depends on application
// i am new to dspic33f as i know so far using DMA will be a clever step for fastest possible sampling, i am studying DMA atm
// but this will do the trick i guarantee

filter_out_new = alpha * adc_input_old + (1-alpha)*filter_old;

filter_out_old = filter_out_new;//this is the filtered analog signal output (error_new = reference - filter_out_new)
adc_input_old = adc_input_new;
