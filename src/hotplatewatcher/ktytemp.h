#ifndef _KTYTEMP_H
#define _KTYTEMP_H

double temp(int inputval);
double volt_pin(double v_in, int pin_val);
double temp_kty85_110(double res);
double res_volt_divider(double v_in, double v_out, double r1_res);

#endif
