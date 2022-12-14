/*
 * LSM6DS33.h
 *
 *  Created on: 4 Ara 2022
 *      Author: kayra
 */

#ifndef INC_LSM6DS33_H_
#define INC_LSM6DS33_H_


#include "stm32f4xx_hal.h"
#include "stdint.h"
#include <math.h>

extern I2C_HandleTypeDef hi2c1;

void LSM6DS33_init(void);

int LSM6DS33_test(void);
int LSM6DS33_testID(void);

float LSM6DS33_Gyro_X(void);
float LSM6DS33_Gyro_Y(void);
float LSM6DS33_Gyro_Z(void);
float LSM6DS33_Acc_X(void);
float LSM6DS33_Acc_Y(void);
float LSM6DS33_Acc_Z(void);

float acc_total_vector(void);
float angle_pitch_acc(void);
float angle_roll_acc(void);


#endif /* INC_LSM6DS33_H_ */
