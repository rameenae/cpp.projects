#include<iostream>
using namespace std;
const int DAYS_PER_WEEK = 7;
const int HOURS_PER_DAY = 24;
double calculateAverageTemperature(int temp[DAYS_PER_WEEK ][HOURS_PER_DAY]){
	double sum =0.0;
	
	for(int i=0;i<DAYS_PER_WEEK;i++){
		
		for(int j=0;j<HOURS_PER_DAY;j++){
			sum+=temp[i][j];
		}
	}
	
	return sum/(DAYS_PER_WEEK*HOURS_PER_DAY);
}
double calculateMax(int temp[DAYS_PER_WEEK][HOURS_PER_DAY]){
	int max= temp[0][0];
	
	for(int i=0;i<DAYS_PER_WEEK;i++){
		
		for(int j=0;j<HOURS_PER_DAY;j++){
			
			if (temp[i][j]>max){
				max=temp[i][j];
			}
		}
	}
	return max;
}
	double calculateMin(int temp[DAYS_PER_WEEK][HOURS_PER_DAY]){
	int min=  temp[0][0];
	for(int i=0;i<DAYS_PER_WEEK;i++){
		
		for(int j=0;j<HOURS_PER_DAY;j++){
			
			if (temp[i][j]<min){
				min=temp[i][j];
			}
		}
	}
	return min;
}

int main(){
	int temp[DAYS_PER_WEEK ][HOURS_PER_DAY];
	cout<<"Enter hourly temperature for each day of week(in CELSIUS)"<<endl;
	for(int i=0;i<DAYS_PER_WEEK;i++){
		cout<<"Day "<<i+1<<":"<<endl;
		for(int j=0;j<HOURS_PER_DAY;j++){
			cout<<"Temperature for hour "<<j+1<<":"<<endl;
			cin>>temp[i][j];
		}
	}
	double avg_temperature = calculateAverageTemperature(temp);
	double max_temperature = calculateMax(temp);
		double min_temperature = calculateMin(temp);

	cout<<"Average weekly temperature is "<<avg_temperature<<" degree Celsius"<<endl;
	cout<<"maximum hourly temperature in week is "<<max_temperature<<" degree Celsius"<<endl;
	cout<<"minimum hourly temperature in week is "<<min_temperature<<" degree Celsius"<<endl;
	
}
