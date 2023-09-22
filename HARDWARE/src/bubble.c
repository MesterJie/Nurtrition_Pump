double GetAverVal1(float *AdcVal,uint8_t cnt)
{
	u8 i = 0;
	double sum = 0;
    float max = AdcVal[0],min = AdcVal[0];
	
	for(i = 1;i < cnt; i++)
	{
		if(AdcVal[i] > max)
		max = AdcVal[i];
		else if(AdcVal[i] < min)
		min = AdcVal[i];
	}
	for(i = 0;i < cnt;i++)
	sum += AdcVal[i];
	
	sum = sum - min - max ;
	
	return (sum/(cnt - 2)) ;

}