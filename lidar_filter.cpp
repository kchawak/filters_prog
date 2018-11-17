//
// Lidar Range & Temporal Median filter
// Author: Kalyani Chawak
//

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;


// Lidar class to provide the range & median filter

class lidar_filter{
private:
	float distance_min = 0.03;
	float distance_max = 50.0;
public:
	lidar_filter(){}
	vector<float> range_filter(vector<float> &scan_val);
	vector<float> tempo_med_update(vector<vector<float> > &data);
	void accum_scan(vector<float> &scan_val, vector< vector<float> > &data);
	float get_median(vector<float> &dist_val);
	~lidar_filter(){}
};

// Method for implementing the range filter
// Values more than the maximum range are capped to the upper bound
// Likewise, values less than the minimum range are capped to the lower bound
vector<float> lidar_filter::range_filter(vector<float> &scan_val){
	float distance_min = 0.03;
	float distance_max = 50.;
	vector<float> range_scan_val(scan_val.size(), distance_min);
	for (unsigned int i = 0; i < scan_val.size(); i++)
	{
		if (scan_val[i] < distance_min) 
		{
			range_scan_val[i] = distance_min;
		}
		else if (scan_val[i] > distance_max) 
		{
			range_scan_val[i] = distance_max;
		}
		else
		{
			range_scan_val[i] = scan_val[i];
		}	
	}
	return range_scan_val;
}

// Method to get the median of a given scan (array)
// When the size of scan is odd, then it will return the middle element
// When the size of the scan is even, it will return the mean of the
// middle two elements
float lidar_filter::get_median(vector<float> &dist_val){
	unsigned int size = dist_val.size();
	if (size % 2 == 0)
	{
		return 0.5 * (dist_val[size/2 - 1] + dist_val[size/2]);
	}
	else 
	{
		return dist_val[size/2];
	}
}

// Method to update the values of the temporal median filter

vector<float> lidar_filter::tempo_med_update(vector<vector<float> > &data){
	unsigned int size = data.size();
	vector<float> med_out(size, 0);
	for (unsigned int i = 0; i < size; i++)
	{
		med_out[i] = get_median(data[i]);
	}
	return med_out;
}

// Method to accumulate the current scan values to the previous scan values

void lidar_filter::accum_scan(vector<float> &scan_val, vector< vector<float> > &data){
	unsigned int size = scan_val.size();
	unsigned int D = data.size();
	if (D == 0)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			data.push_back(vector<float>());
			data[i].push_back(scan_val[i]);
		}
	}
	else 
	{
		for (unsigned int i = 0; i < size; i++)
		{
			vector<float>::iterator it = lower_bound(data[i].begin(), data[i].end(), scan_val[i]);
			data[i].insert(it,scan_val[i]);
		}
	}
	return;
}


// Main function

int main(){

	// Test case to check Range filter
    lidar_filter L1;
    vector<float> scan1 = {0., 1., 2., 1., 3.}; 
    vector<float> output1 = L1.range_filter(scan1);
	cout << "#### Range filter ####" << endl;
	cout << "scan1 value = { ";
	for (unsigned int i = 0; i < scan1.size(); i++)
	{
		cout << scan1[i];
		if (i != scan1.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;
	
	cout << "Output value = { ";
	for (unsigned int i = 0; i < output1.size(); i++)
	{
		cout << output1[i];
		if (i != output1.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;
	cout << "######################" << endl;
	cout << endl;
	
	
	
    // Test case to check Temporal median filter
	lidar_filter L2;
    vector<float> scan2 = {1., 5., 7., 1., 3.};
	vector<float> scan3 = {2., 3., 4., 1., 0.};
	vector<float> scan4 = {3., 3., 3., 1., 3.};
	vector<float> scan5 = {10., 2., 4., 0., 0.};
    vector<vector<float> > data;
	L2.accum_scan(scan1, data);
	L2.accum_scan(scan2, data);
	vector<float> output2 = L2.tempo_med_update(data);
	
	L2.accum_scan(scan3, data);
	vector<float> output3 = L2.tempo_med_update(data);
	
	L2.accum_scan(scan4, data);
	vector<float> output4 = L2.tempo_med_update(data);
	
	L2.accum_scan(scan5, data);
	vector<float> output5 = L2.tempo_med_update(data);
	
		
	cout << "#### Temporal median filter ####" << endl;
	
	cout << "scan1 value = { ";
	for (unsigned int i = 0; i < scan1.size(); i++)
	{
		cout << scan1[i];
		if (i != scan1.size() - 1)
		{ cout << ", ";}		
	}
	cout << "}" << endl;
	
	cout << "scan2 value = { ";
	for (unsigned int i = 0; i < scan2.size(); i++)
	{
		cout << scan2[i];
		if (i != scan2.size() - 1)
		{ cout << ", ";}		
	}
	cout << "}" << endl;
	
	cout << "scan3 value = { ";
	for (unsigned int i = 0; i < scan3.size(); i++)
	{
		cout << scan3[i];
		if (i != scan3.size() - 1)
		{ cout << ", ";}		
	}
	cout << "}" << endl;

	cout << "scan4 value = { ";
	for (unsigned int i = 0; i < scan4.size(); i++)
	{
		cout << scan4[i];
		if (i != scan4.size() - 1)
		{ cout << ", ";}		
	}
	cout << "}" << endl;

	cout << "scan5 value = { ";
	for (unsigned int i = 0; i < scan5.size(); i++)
	{
		cout << scan5[i];
		if (i != scan5.size() - 1)
		{ cout << ", ";}		
	}
	cout << "}" << endl;
	
	cout << "Output2 value = {";
	for (unsigned int i = 0; i < output2.size(); i++)
	{
		cout << output2[i];
		if (i != output2.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;

	cout << "Output3 value = {";
	for (unsigned int i = 0; i < output3.size(); i++)
	{
		cout << output3[i];
		if (i != output3.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;
	
	cout << "Output4 value = {";
	for (unsigned int i = 0; i < output4.size(); i++)
	{
		cout << output4[i];
		if (i != output4.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;

	cout << "Output5 value = {";
	for (unsigned int i = 0; i < output5.size(); i++)
	{
		cout << output5[i];
		if (i != output5.size() - 1)
		{ cout << ", ";}
	}
	cout << "}" << endl;	
	
	cout << "################################" << endl;
	
	
	return 0;
}