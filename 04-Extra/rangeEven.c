#include <stdio.h>

int range_of_even(int *nums , int length , int *min , int *max );

int main(){
	//LENGTH
	int len=0;
	printf("Insert array length:");
	scanf("%d", &len);

	//CREATE AND INITIALIZE ARRAY
	int array[len];
	for(int i=0; i<len; i++){
		printf("Insert array[%d]:", i);
		scanf("%d", array+i);
	}
	//FUNCTION AND RESULT
	int min, max, res;
	res=range_of_even(array, len, &min, &max);
	printf("there is even=%d, min even=%d, max even=%d", res, min, max);
}

int range_of_even ( int *nums , int length , int *min , int *max ){
	int res=0;
	for(int i=0; i<length; i++){
		if(res==0 && nums[i]%2==0){
			*min=nums[i];
			*max=nums[i];
			res=1;
		}
		else if(*min>nums[i]){
			*min=nums[i];
		}
		else if(*max<nums[i]){
			*max=nums[i];
		}
	}

	return res;
}
