# LSM6DS33-STM32-driver

1- include .h file in main.c 

2- sensor connect to hi2c1 com. port

3- add init func. in main 

	  LSM6DS33_init();

4- calc. loop time and assing to dt var.

	  dt = (double)(HAL_GetTick() - timer) / 1000000; // Calculate delta time
	  timer = HAL_GetTick();
    
    
5- use gyro func like this: 
    
    gyro_x += (read_data_gyro(1) / 8.75) * dt;
    gyro_y += (read_data_gyro(2) / 8.75) * dt;
    gyro_z += (read_data_gyro(3) / 8.75) * dt;
    
   use acc func like this:
   	
   raw data:
   
  	  acc_x =  read_data_acc(1);
	  acc_y =  read_data_acc(2);
	  acc_z =  read_data_acc(3);
	  
   euler angle:
   
	  pitch_acc = angle_pitch_acc();
	  roll_acc  = angle_roll_acc();
