/*
 * LSM6DS33.c
 *
 *  Created on: 4 Ara 2022
 *      Author: kayra
 */

#include "LSM6DS33.h"


int LSM6DS33_test(void){
	HAL_StatusTypeDef status;

		status = HAL_I2C_IsDeviceReady(&hi2c1,(0x6B)<<1 , 4, 300);
		if(HAL_OK == status){
			return 1;
		}
		else{
			return 0;
		}

}


int LSM6DS33_testID(void){
	uint8_t buffer1[1];
	HAL_I2C_Mem_Read(&hi2c1, (0x6B)<<1, 0x0F, 1, buffer1, 1, 300);

	if((uint8_t)0x69 == buffer1[0]){
		return 1;
	}
	else{
		return 0;
	}


}


float LSM6DS33_Gyro_X(void){

	int16_t gyroX;
	uint8_t OUTX_H_G,OUTX_L_G;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x22,    //OUTX_L_G  0x22
						1,
						&OUTX_L_G,   //OUTX_L_G
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x23,    //OUTX_H_G   0x23
						1,
						&OUTX_H_G,   //OUTX_H_G
						1,
						100);
	gyroX = (OUTX_H_G << 8) | (OUTX_L_G);

	gyroX = (float)gyroX /70; // GYRO_FS_2000

	return (float) gyroX;
}


float LSM6DS33_Gyro_Y(void){


	int16_t gyroY;
	uint8_t OUTY_H_G,OUTY_L_G;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x24,    //OUTY_L_G  0x24
						1,
						&OUTY_L_G,   //OUTX_L_G
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x25,    //OUTY_H_G   0x25
						1,
						&OUTY_H_G,   //OUTX_H_G
						1,
						100);
	gyroY = (OUTY_H_G << 8) | (OUTY_L_G);

	gyroY = (float)gyroY /70; // GYRO_FS_2000

	return (float) gyroY;

}


float LSM6DS33_Gyro_Z(void){


	int16_t gyroZ;
	uint8_t OUTZ_H_G,OUTZ_L_G;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x26,    //OUTZ_L_G  0x26
						1,
						&OUTZ_L_G,   //OUTZ_L_G
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x27,    //OUTZ_H_G   0x27
						1,
						&OUTZ_H_G,   //OUTX_H_G
						1,
						100);
	gyroZ = (OUTZ_H_G << 8) | (OUTZ_L_G);

	gyroZ = (float)gyroZ /70; // GYRO_FS_2000

	return (float) gyroZ;


}


float LSM6DS33_Acc_X(void){


	int16_t AccX;
	uint8_t OUTX_H_Acc,OUTX_L_Acc;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x28,    //OUTX_L_XL (28h)
						1,
						&OUTX_L_Acc,   //OUTX_L_XL
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x29,    // OUTX_H_XL (29h)
						1,
						&OUTX_H_Acc,
						1,
						100);
	AccX = (OUTX_H_Acc << 8) | (OUTX_L_Acc);

	AccX = (float)AccX /0.244; // FS = ±8

	return (float) AccX;



}


float LSM6DS33_Acc_Y(void){



	int16_t AccY;
	uint8_t OUTY_H_Acc,OUTY_L_Acc;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x2A,    //OUTY_L_XL (2Ah)
						1,
						&OUTY_L_Acc,   //OUTX_L_XL
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x2B,    // OUTY_H_XL (2Bh)
						1,
						&OUTY_H_Acc,
						1,
						100);
	AccY = (OUTY_H_Acc << 8) | (OUTY_L_Acc);

	AccY = (float)AccY /0.244; // FS = ±8

	return (float) AccY;


}


float LSM6DS33_Acc_Z(void){

	int16_t AccZ;
	uint8_t OUTZ_H_Acc,OUTZ_L_Acc;

	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x2C,    //OUTZ_L_XL (2Ch)
						1,
						&OUTZ_L_Acc,   //OUTX_L_XL
						1,
						100);


	HAL_I2C_Mem_Read(	&hi2c1,
						(0x6B)<<1,
						0x2D,    // OUTZ_H_XL (2Dh)
						1,
						&OUTZ_H_Acc,
						1,
						100);
	AccZ = (OUTZ_H_Acc << 8) | (OUTZ_L_Acc);

	AccZ = (float)AccZ /0.244; // FS = ±8

	return (float) AccZ;

}

