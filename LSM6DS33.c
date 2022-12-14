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




void LSM6DS33_init(void){


	uint8_t data;


	// ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (+/-2 g full scale)
	data = 0x80; // 0x80 = 0b10000000
	HAL_I2C_Mem_Write	(	&hi2c1,
							(0x6B)<<1,
							0x10,// LSMDS_CTRL1_XL (10h)
							1,
							&data,
							1,
							100
						);


	 // ODR = 1000 (1.66 kHz (high performance)); FS_G = 00 (245 dps for DS33)
	data = 0x80; // 0x80 = 0b10000000
	HAL_I2C_Mem_Write	(	&hi2c1,
							(0x6B)<<1,
							0x11,//  CTRL2_G = (11h)
							1,
							&data,
							1,
							100
						);

	// IF_INC = 1 (automatically increment register address)
	data = 0x04; // 0x04 = 0b00000100
	HAL_I2C_Mem_Write	(	&hi2c1,
							(0x6B)<<1,
							0x12,//  CTRL2_G = (12h)
							1,
							&data,
							1,
							100
						);


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

	gyroX = (float)gyroX /8.75; // GYRO_FS_245

	return (float) gyroX*0.02; // 19ms(0.019s) is while time in main
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

	gyroY = (float)gyroY /8.75; // GYRO_FS_245

	return (float) gyroY*0.02;

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

	gyroZ = (float)gyroZ /8.75; // GYRO_FS_245

	return (float) gyroZ*0.02;


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

	AccX = (float)AccX * 0.061; // FS = ±2

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

	AccY = (float)AccY * 0.061; // FS = ±2

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

	AccZ = (float)AccZ * 0.061; // FS = ±2

	return (float) AccZ;

}



float acc_total_vector(void){

	return sqrt((LSM6DS33_Acc_X()*LSM6DS33_Acc_X())+(LSM6DS33_Acc_Y()*LSM6DS33_Acc_Y())+(LSM6DS33_Acc_Z()*LSM6DS33_Acc_Z()));;

}
float angle_pitch_acc(void){

	//57.296 = 1 / (3.142 / 180)

	return asin((float)LSM6DS33_Acc_X()/acc_total_vector())* 57.296;

}
float angle_roll_acc(void){

	return asin((float)LSM6DS33_Acc_Y()/acc_total_vector())* 57.296;


}




