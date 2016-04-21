#include<iostream>
#include<time.h>


using namespace std;

inline void swap(int&a, int&b)
{
	auto temp = a;
	a = b;
	b = temp;
}

inline void swap(int*arr, int i, int j)
{
	auto temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void bubble_sort(int*sq, int length)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = i + 1; j < length; ++j)
		{
			if (sq[i] > sq[j])
			{
				swap(sq[i], sq[j]);
			}
		}
	}
}

void bubble_sort2(int*sq, int length)
{
	bool run = true;
	for (int i = 0; i < length&&run; ++i)
	{
		run = false;
		for (int j = length - 2; j >= i; --j)
		{
			if (sq[j] > sq[j + 1])
			{
				swap(sq[j], sq[j + 1]);
				run = true;
			}
		}

		cout << i << " loop: ";
		for (int k = 0; k < length; k++)
		{
			cout << sq[k] << " ";
		}
		cout << endl;
	}
}


void select_sort(int*sq, int length)
{
	int min = -1;
	for (int i = 0; i < length; ++i)
	{
		min = i;
		for (int j = i; j < length; ++j)
		{
			if (sq[j] < sq[i])min = j;
		}

		if (min != i)
		{
			swap(sq, i, min);
		}

		cout << i << " loop: ";
		for (int k = 0; k < length; k++)
		{
			cout << sq[k] << " ";
		}
		cout << endl;
	}
}

//5 2 6 8 1
// temp = 2,sq[1]=sq[0],  5 5 6 8 1,// 2 5 6 8 1
// 2 5 6 8 1
// 2 5 6 8 1
//temp = 1;,j = 3,sq[4] = sq[3],2 5 6 8 8,j=2,2 5 6 6 8 ,j=1,2 5 5 6 8 ,j=0,2 2 5 6 8; 1 2 5 6 8

void insert_sort(int*sq, int length)
{
	int temp;
	for (int i = 0; i < length-1; ++i)
	{
		if (sq[i] > sq[i + 1])
		{
			temp = sq[i + 1];
			int j;
			for ( j= i; j>=0&&sq[j]>temp; --j)
			{
				sq[j + 1] = sq[j];
			}
			sq[j+1] = temp;
		}

		cout << i << " loop: ";
		for (int k = 0; k < length; k++)
		{
			cout << sq[k] << " ";
		}
		cout << endl;
	}
}

//ϣ������
//5,2,6,8,1
//increase_ment = 2,i = 1;i = 2,,sq[2]>sq[4],temp = sq[4] = 1;����j = 2,  j=2 5,2,6,8,6; j=0 5,2,5,8,6   �˳���1,2,5,8,6
//increase_ment = 2/3+1 = 1; i = 0;���Ժ���ǲ�������
//
void shell_sort(int*sq, int length)
{
	int temp;
	int increase_ment = length;
	while (increase_ment > 1)
	{
		increase_ment = increase_ment / 3 + 1;
		for (int i = increase_ment-1; i < length-1&&(i+increase_ment)<length; ++i)
		{
			if (sq[i] > sq[i + increase_ment])  //����
			{
				temp = sq[i + increase_ment];
				int j;
				for (j = i; j >= 0 && sq[j] > temp; j -= increase_ment)
				{
					sq[j + increase_ment] = sq[j];   //move
				}
				sq[j + increase_ment] = temp;
			}
			cout << "increase ment : " << increase_ment << " ";
			cout << i << " loop: ";
			for (int k = 0; k < length; k++)
			{
				cout << sq[k] << " ";
			}
			cout << endl;
		}

		
	}
}

//������
//�ѵĵ���(���ѣ�ά��������)
void heap_adj(int*sq, int start, int length)
{
	int temp = sq[start];
	for (int i = 2 * start+1; i < length; i = i * 2+1)
	{
	
		if (i < length&&(i+1)<length&&sq[i] < sq[i + 1])
		{
			i = i + 1;   //ѡ����һ������
		}
		if (sq[i] <= temp) //�жϸ��ڵ����ӽڵ��ϵ
		{
			break;   //!!!!!
		}
		
		sq[start] = sq[i];
		start = i;
	}

	sq[start] = temp;
}


void heap_sort(int*sq, int length)
{
	//create heap
	for (int i = length / 2 - 1; i >= 0; --i)
	{
		heap_adj(sq,i, length);
	}

	cout << "heap is:" << endl;
	for (int i = 0; i < length; ++i)
	{
		cout << sq[i] << " ";
	}
	cout << endl;

	cout << "sort begin..." << endl;
	for (int i = length-1; i > 0; --i)
	{
		swap(sq[0], sq[i]);
		heap_adj(sq, 0, i);

		cout << "loop " << i << ": ";
		for (int i = 0; i < length; ++i)
		{
			cout << sq[i] << " ";
		}
		cout << endl;
	}
	
}


//�鲢��sq�Ǵ��鲢���飬res�ǽ������
void Merge_dispatch(int*sq, int*res,int start, int medium, int end)
{
	/*
	cout << "before meger: ";
	cout << "meger ,start: " << start << " meduim: " << medium << " end: " << end << " " << endl;
	for (int i = start; i <= end; ++i)
	{
		cout << sq[i] << " ";
	}
	cout << endl;*/
	int i,j, k;
	for (i = start, j = start, k = medium + 1; j <= medium&&k <= end; ++i)  //ע��߽�
	{
		if (sq[j] < sq[k])
		{
			res[i] = sq[j++];
		}
		else
		{
			res[i] = sq[k++];
		}
	}

	if (j <= medium )
	{
		for (; j <= medium; ++j)
		{
			res[i++] = sq[j];
		}
	}
	else if (k <= end)
	{
		for (; k <= end; ++k)
		{
			res[i++] = sq[k];
		}
	}
/*
	cout << "after meger:";
	for (int i = start; i <= end; ++i)
	{
		cout << res[i] << " ";
	}
	cout << endl;*/
}

//�鲢����������
void MSort_dispatch(int*sq,int*res, int start, int end,int length)
{
	int *res2 = new int[length];
	if (start == end)//��������
	{
		res[start] = sq[start];
	}
	else
	{
		int m = (start + end) / 2;
		MSort_dispatch(sq, res2,start, m, length);
		MSort_dispatch(sq, res2,m + 1, end, length);
		Merge_dispatch(res2, res, start, m, end);  //res2�洢���ǹ鲢��Ľ��
	}

}

//�鲢����
//�ݹ�汾
void MegerSort(int*sq, int length)
{
	MSort_dispatch(sq,sq,0,length - 1,length);
}


void MegerSort2_dispatch(int*sq, int*res, int k, int length)
{
	int i = 0;
	while (i <= length - k * 2)
	{
		
		Merge_dispatch(sq, res, i, i+k-1, i+2*k-1);  //�б߽����Σ��
		i = i + 2 * k;
	}
	if (i < length - k) //��ʣ�µ����ݱ�k��Ҫ�󣬽������һ�β��飿������
	{
		Merge_dispatch(sq, res, i, i + k - 1, length-1);//ע��߽磬���
	}
	else //ֻ�ǿ�����Ŀ������
	{
		for (; i < length; ++i)
		{
			res[i] = sq[i];
		}
	}

	cout << "meger loop: " << k << " :";
	for (int i = 0; i < length; ++i)
	{
		cout << res[i] << " ";
	}
	cout << endl;
}

//�鲢���򣬷ǵݹ�汾
void MegerSort2(int*sq, int length)
{
	int* res = new int[length];
	int k = 1;
	while (k < length)
	{
		MegerSort2_dispatch(sq, res, k, length);
		k = 2 * k;
		MegerSort2_dispatch(res, sq, k, length);
		k = 2 * k;
	}
}

//�ָ�õ��ָ��
int partition(int*sq, int low, int up)
{
	int pivot_key;
	//pivot_key = sq[low];
	//���ŵ������Ż�
	//ѡȡpivot_keyʹ������ȡ�еķ���,ʹ��ѡȡ��pivot���������С
	int medium_num = low + (up - low) / 2;
	if (sq[low]>sq[up])
		swap(sq, low, up);   //��֤���С
	if (sq[medium_num] > sq[up])
		swap(sq, medium_num, up);//��֤�м�С
	if (sq[low] < sq[medium_num])
		swap(sq, low, medium_num);//��֤���С

	pivot_key = sq[low];
	//int pivot_backup = pivot_key;
	while (low < up)
	{
		while (low < up&&sq[up] >= pivot_key)
			up--;
		//swap(sq, low, up);   //���ܸĽ�����Ϊ��ֵ�������ǽ���
		sq[low] = sq[up];
		while (low < up&&sq[low] <= pivot_key)
			low++;
		//swap(sq, low, up);
		sq[up] = sq[low];
	}
	sq[low] = pivot_key;
	return low;
}

//��������������
void quick_sort_dispatch(int*sq, int start, int end)
{
	int pivot;
	if(start < end)
	{
		pivot = partition(sq, start, end);
		quick_sort_dispatch(sq, start, pivot - 1);
		quick_sort_dispatch(sq, pivot + 1, end);
	}

	

}

//��������
void quick_sort(int*sq, int length)
{
	quick_sort_dispatch(sq, 0, length - 1);

}

int main()
{
	//int arr[9] = { 5,2,6,8,1 };
	time_t end;
	
	int arr[9] = { 90,70,80,60,10,40,50,30,20 };
	cout << "before sort:" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] <<" ";
	}
	cout << endl;
	
	quick_sort(arr, 9);
	end = clock();
	end = end / CLOCKS_PER_SEC;
	
	//MegerSort2(arr, 9);
	//MegerSort(arr, 9);
	//heap_sort(arr, 9);
	//shell_sort(arr, 5);
	//insert_sort(arr, 5);
	//select_sort(arr, 5);

	//bubble_sort2(arr, 5);
	cout << "after sort: " << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;


	cout << "time is: " << end << " s" << endl;
}