########################################################
#
#
#      README file
#      Lidar filters sample code for Brain Corporation
#      Author: Kalyani Chawak
#      Date: 10/26/2018
#
#      This program has implemented range filter and 
#      temporal median filter for Lidar scan values.
#      These filters will help to reduce the noise in
#      the data coming from the Lidar sensors.    
#      I have used 1-Dimensional vectors as an array 
#      to store the values coming from the sensor.
#      For temporal median filter, I am using 2-Dimensional
#      vectors to accumulate the current scan values in the 
#      previous data. 
#
#      Test case provided in the problem statement has 
#      been used to validate the program.
#      This particular test case has a series of 5 scans
#      with each having 5 values.
#
#      Please use the below template to create an instance 
#      of the filter:
#      lidar_filter L2;
#
#      To add a new test case, use the below template:
#      vector<float> scan2 = {1., 5., 7., 1., 3.};
#
#      To accumulate the current scan value with the
#      previous scan values, use the below template:
#      L2.accum_scan(scan2, data);
#
#      To use the temporal median filter, use the following:
#      vector<float> output2 = L2.tempo_med_update(data);
#
#      Future work:
#      Adding following test cases:
#      1. Empty scan values
#      2. Random scan value generation
#      3. Scan values with large number
#      4. Varying the number of values in each scan
#
#########################################################