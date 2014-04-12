//#include "../headers/cfizika.h"
//
//void CopyFanc (Camera ** obj,Camera * count,int &num,int &max)
//{
//	if(max < num)
//	{
//		Camera ** copy = NULL;
//		copy = new Camera* [max];
//		for(int i=0;i<max;i++)
//		{
//			copy[i] = obj[i]; 
//			obj[i] = NULL;
//		}
//
//		/*delete[] obj;
//		obj = NULL;*/
//
//		obj = new Camera* [max*2];
//
//		for(int i =0;i< max*2; i++)
//		{
//			if (i < max) obj[i] = copy[i];
//			else obj[i] = NULL;
//		}
//		delete[] copy;
//
//		obj[max] = count;
//		max *= 2;
//	}
//	else
//	{
//		obj[num] = count;
//	}
//	num++;
//}