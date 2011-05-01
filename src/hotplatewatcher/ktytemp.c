#include <stdio.h>

#include "ktytemp.h"

#define BUFFER_SIZE 5

int main (int argc, char **argv)
{
     char buffer[BUFFER_SIZE];
          
     for(;;)
     {
          printf("Value at the pin of the Arduino:");
          fgets(buffer, BUFFER_SIZE, stdin);
          printf("The temperature is %f\n", temp(atoi(buffer)));
     }
  
     return 0;
}

/*
  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1240316856
*/

double temp(int pinval)
{
     double v_in = 5.0;
     double v_out = volt_pin(v_in, pinval);
     double res = res_volt_divider(v_in, v_out, 10000);
                                   
     return temp_kty85_110(res);
}

/*
  Returns the voltage mesured by the Arduino
  given the voltage in input and the 0 to 1024
  integer value measured at the pin.
 */
double volt_pin(double v_in, int pin_val)
{
     return (v_in / 1024) * pin_val;
}


/*
  The KTY85-110 is a thermistor whose resistance
  augments linearly with the temperature.

  We take the values between 0 and 120°C of the technical sheet
  and apply a linear regression, for instance
  with Wolfram Alpha, like this:
  
  linear fit {820, 0}, {889, 10}, {962, 20}, {1000, 25}, {1039, 30},
  {1118, 40}, {1202, 50}, {1288, 60}, {1379, 70}, {1472, 80}, {1569, 90},
  {1670, 100}, {1774, 110}, {1882, 120}
  
  or with the Matlab polyfit function.

  This gives the slope and intercept of the line
  and allows to calculate the temperature given
  the resistance value.
 */
double temp_kty85_110(double res)
{
     double slope = 0.112504;
     double intercept = -87.6624;
          
     return res * slope + intercept;
}

/*
  The thermistor and the other 10K resistance forms
  a voltage divider. We calculate the value
  of the thermistor's resistance base on the
  input voltage at the pin.

  See: http://en.wikipedia.org/wiki/Voltage_divider
  
  The 10K resistance is connected to the ground
 */

/* Returns the value of the resistance connected
   to v_in in a voltage divider, given
   the voltage value between the two resistances.
*/
double res_volt_divider(double v_in, double v_out, double r2_res)
{
     return r2_res * ((v_in / v_out) - 1);
}


