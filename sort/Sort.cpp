#include <stdio.h>
#include <stdlib.h>   //malloc
#include <string.h> //memcpy
void Swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

/*
ѡ�������ǴӴ������������ѡ����С��һ��Ԫ�أ�������Ѿ���������к����Ԫ�ؽ���λ�ã�ֱ��ȫ���������Ԫ�ش����ꡣ


������Ϊa[0...n-1]
1����ʼʱ������ȫΪ������Ϊa[0..n-1]����i=0
2������a[i],��a[i...n-1]��ѡ��һ����СԪ�أ���������a[i]������������a[0,i]���������
3��i++�ظ���2����ֱ��������i==n-1���������

ʱ�临�Ӷȣ�
���������ԭ�����и�ֵ���Ƚϼ���������Ȼ��������Ӧ��ȡ�Ƚϡ��ܵıȽϴ�����Ȼ�ǣ�(n-1)+(n-2)+(n-3)+...+1����һ���Ȳ�����֮�ͣ������n(n-1)/2
ѡ������ƽ��ʱ�临�Ӷ�ΪO(n*n)

�ȶ��ԣ�
���ȶ���
����5 8 5 2������֪����һ��ѡ���1��Ԫ��5���2��������ôԭ������2��5�����ǰ��˳��ͱ��ƻ��ˣ�����ѡ��������һ���ȶ��������㷨��

*/
void SelectSort(int a[], int n) 
{
	int i, j, minIndex;
	for (i = 0; i < n; i++)
	{
		minIndex = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[minIndex]) 
			{
				minIndex = j;
			}
		}
		Swap(a[i], a[minIndex]);
	}
}


/*
����������ͨ�����������������еĳ�����ʵ�ֵģ�����ÿһ���������Ԫ�أ�����ؼ��ִ�С���뵽ǰ���Ѿ��ź�����������е��ʵ�λ�ã��γɸ��������������С�
��ÿһ���������Ԫ�ض������ӱ�ѭ�����������������ɡ�

��������Ϊa[0...n-1]
1����ʼʱ��a[0]�Գ�һ������������У�������Ϊa[1...n-1]����i=1
2������ÿһ��a[i...n-1]�����䲢�뵽��ǰ�����������a[0...i-1]���γɸ�������������a[0,i]��ֱ��������i==n-1��Ҳ��i==n��ʱ���������
3����i == n��ʱ��a[0,n-1]��ÿһ��Ԫ�ض����뵽��ȷ��λ��
����1��3���������㷨���۵�ѭ������ʽ֤�����������㷨����ȷ��

*/

void InsertSort(int *a, int n) 
{
	int i, j;
	for (i = 1; i < n; i++) 
	{
		for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) 
		{
			Swap(a[j], a[j + 1]);
		}
	}
}


/*
����һ������a[i]������������a[0...i-1]��ʱ��,����ͨ�������������ݵķ�����ʵ��
��j = i - 1;��a[j] > a[j+1]���򽻻�a[j]��a[j+1]����j--��������ѭ������ֱ�������������������j==-1��
*/

void InsertSort1(int *a, int n) 
{
	int i, j;
	for (i = 1; i < n; i++) 
	{
		for (j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) 
		{
			Swap(a[j], a[j + 1]);
		}
	}
}


/*
������������a[i]������������a[0...i-1]��ʱ��,����ͨ�����������ݺ��Ƶķ�����ʵ��
1����������Ӧ�ò����λ��pos
2��Ȼ��a[pos...i-1]����ƶ���a[pos+1...i]���ڳ�a[pos]��λ�ã�Ȼ��a[i]���뵽a[pos]
*/

void InsertSort2(int a[], int n)
{
	int i, j, k,pos;
	//ѭ���ӵڶ�������Ԫ�ؿ�ʼ����Ϊarr[0]��Ϊ��������򲿷�
	for (i = 1; i < n; i++)
	{
		//Ϊa[i]��ǰ�����������������һ�����ʵ�λ��
		for (j = i - 1; j >= 0; j--)
			if (a[j] < a[i])
				break;
		//���ʵ�λ������j֮��Ҳ��j+1
		pos = j+1;
		//���λ�ò���i�Լ��������Լ�������Ҫ����
		if (pos != i)
		{
			//�Ƚ�a[pos...i-1]����ƶ���a[pos+1...i]���ڳ�a[pos]��λ�ã�Ȼ��a[i]���뵽a[pos]
			int temp = a[i];
			for (k = i - 1; k >=pos ; k--)
				a[k + 1] = a[k];
			a[pos] = temp;
		}
	}
}

/*
������:����a[i]������������a[0...i-1]��ʱ��,����ͨ�����������ݺ���ͬʱ���еķ�����ʵ��
��j = i-1;��a[j] > a[i]����a[j]���Ƶ�a[j+1]��Ȼ����j--��������ѭ������ֱ�������������������j==-1
*/
void InsertSort3(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		if (a[i] >= a[i-1]) 
		{
			break;
		}
		int temp = a[i];
		for (j = i-1; j >= 0 && a[j] > temp; j--)
		{
			a[j + 1] = a[j];
		}
		a[j+1] = temp;
	}
}


/*
�ܽ��������ַ�����
����һ����Ϊ������Swap��ÿ��Swap��Ҫ�����θ�ֵ�Ĳ�����ƽ��ʱ�临�Ӷȿ�����Ϊ��3n*n
�������������������ݺ��ƣ��ֳ�������ƽ��ʱ�临�Ӷ���2*n*n
�����������������ݺ���ͬʱ����ƽ��ʱ�临�Ӷ���n*n
�������������ֲ������򷽷������ŵ��㷨

���������ʱ�临�Ӷȷ�����
���������ǣ������Ѿ������������ˣ�����������£���Ҫ���еıȽϲ�����(n-1)�μ���
�������ǣ������ǽ������У���ô��ʱ��Ҫ���еıȽϹ���n(n-1)/2�Σ���������ĸ�ֵ�����ǱȽϲ����Ĵ�����ȥ(n-1)�Ρ�
ƽ����˵��������ʱ�临�Ӷ�ΪO(n*n)

����������ȶ��Է�����
��ǰ���Ԫ�ظ���ǰԪ��һ�����򲻻�����λ�Ĳ�����������ȶ���
*/




/*ð�������ǴӴ�����������У��Ƚ����ڵ�ǰ��������ݣ���ǰ��Ԫ��ֵ���ں���Ԫ��ֵ�򽻻�λ�ã���1����������Ԫ�ؾͳ�������ĵ�n-1��λ�ã���ȫ���������Ԫ�ش�����
������Ϊa[0...n-1]
1����ʼʱ������ȫΪ������Ϊa[0...n-1]����i=0
2���Ƚ����ڵ�ǰ������Ԫ�أ���ǰ��Ԫ�ش��ں���Ԫ�أ��򽻻�λ�ã�һ������������Ԫ�ؾ�"��"����a[n-1]
3��i++�ظ���2�������뵽������i=n-1,�������
*/

void BubbleSourt1(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(a[j], a[j+1]);
			}
		}
	}
}

/*ð����������Ż�������һ�����isSwapHappened�������һ���з�����������Ϊture,����Ϊfalse.�����һ��û�з����������������Ѿ��������*/

void BubbleSourt2(int a[], int n)
{
	int i, j;
	bool isSwapHappened;
	for (i = 0; i < n; i ++)
	{
		isSwapHappened =  false;
		for (j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				Swap(a[j], a[j+1]);
				isSwapHappened = true;
			}
		}
		if (!isSwapHappened)
		{
			break;
		}
	}
}

/*���⻹��������ͬʱð��*/
void TwoWayBubbleSourt(int a[], int n)
{
	int i, low, high, isSwapHappend;
	low = 0;
	high = n - 1;

	while (low < high)
	{
		isSwapHappend = false;
		for (i = low; i < high; i++)
		{
			if (a[i] > a[i + 1])
			{
				Swap(a[i], a[i + 1]);
				isSwapHappend = true;
			}
		}
		if (!isSwapHappend) 
		{
			break;
		}
		high--;
		isSwapHappend = false;
		for(i = high; i > low; i--)
		{
			if (a[i] < a[i - 1])
			{
				Swap(a[i], a[i - 1]);
				isSwapHappend = true;
			}
		}
		if (!isSwapHappend) 
		{
			break;
		}
		low++;
	}
}
/* 
ʱ�临�Ӷȣ�
�����һ��ʼ������ģ�ֻ��Ҫ��n-1���жϣ�ʱ�临�Ӷ�ΪO(n)
�������ģ���Ҫ��n(n-1)/2�αȽϣ�ʱ�临�Ӷ�ΪO(n*n)
ƽ��ʱ�临�Ӷ�ΪO(n*n)

�ȶ��ԣ�
����������Ԫ�����ʱ�����Բ��������������ȶ���
*/


/*
�鲢�����ǽ����ڹ鲢�����ϵ�һ����Ч�������㷨�����㷨�ǲ��÷��η���һ���ǳ����͵�Ӧ�á�

1.��·�鲢�ݹ��㷨˼·
����a[first...last] mid = (first + last) / 2;
���԰�����ֳ�����a[first...mid]�Լ�a[mid+1...last]��Ȼ���������鶼������ģ��ϲ�������Ӷ���a[first...last]����
��ô��a[first...mid]�Լ�a[mid+1...last]�����أ����԰�a[first...mid]��a[mid+1...last]�ֱ��ٷֳ����飬�������ơ�
ֱ�����ֳ�����С��ֻ��һ��Ԫ��ʱ��������Ϊ���С���Ѿ�����Ȼ���ٺϲ����ڵ�����С�顣
����ͨ���ȵݹ�ķֽ����У��ٺϲ����о�����˹鲢����

ʱ�临�Ӷȣ�
�����鳤��ΪN����������ַ��ֳ�N��С�飬��ҪlogN����ÿһ������һ���ϲ��������еĹ��̣�ʱ�临�Ӷ�ΪN,��һ��ΪN * logN
�ռ临�Ӷȣ�
��Ҫ����һ���������飬�ռ临�Ӷ�ΪN
�ȶ��ԣ�
�ȶ��ģ���Ϊ�ڽ�������������кϲ���һ�������������ʱ����Ԫ����ȵ�����£���������ѡ������������е�Ԫ��
*/

//����������������a[first...mid]��a[mid+1...last]�ϲ�������һ����a��Сһ����temp����
void Merge(int a[], int first, int mid, int last, int temp[]) 
{
	int i = first, j = mid+1;
	int k = 0;
	while (i <= mid && j <= last)
	{
		if (a[i] <= a[j])
		{
			temp[k++] = a[i++];
		} else {
			temp[k++] = a[j++];
		}
	}
	while (i <= mid ) 
	{
		temp[k++] = a[i++];
	}
	while (j <= last)
	{
		temp[k++] = a[j++];
	}
	for(int v = 0; v < k; v++)
	{
		a[first + v] = temp [v];
	}
}

//�鲢����
void MergeSort(int a[], int first, int last, int temp[])
{
	if (first < last) //�ݹ���ս������������䳤��Ϊ1��һ����¼��Ȼ����
	{
		int mid = (first + last)/2;
		MergeSort(a, first, mid, temp); //�����a[first...mid]����
		MergeSort(a, mid+1, last, temp); //���ұ�[mid+1...last]����
		Merge(a, first, mid, last, temp); //�ٽ������������кϲ�
	}
}

/*2.��·�鲢����ǵݹ�ʵ��
�ٰ� n ����¼���� n ������Ϊ l �����������У�
�ڽ��������鲢ʹ��¼�ؼ������򣬵õ� n/2 ������Ϊ 2 �����������У�
���ظ��ڢڲ�ֱ�����м�¼�鲢��һ������Ϊ n ������������Ϊֹ��
*/


void MergeSort2(int a[], int n, int temp[])
{
	int first, mid, last;
	int i = 0;
	//����
	for (int step = 1; step < n; step *= 2)
	{
		for (i = 0; i < n; i += 2 * step)
		{
			first = i;
			mid = i + step - 1;
			last = i + 2 * step - 1;
			if (mid >= n) {
				break;
			}
			if (last >= n) {
				last = n-1;
			}
			Merge(a, first, mid, last, temp);
		}
	}
}


/*��������
����������C.R.A.Hoare��1962�������һ�ֻ��ֽ���������������һ�ַ��εĲ��ԣ�ͨ������Ϊ���η�(Divide-and-Conquer Method)��
�÷����Ļ���˼���ǣ�
1��ѡ����ֵ��pivot
2���ָ��������ֵλ�ã������л���Ϊ����������L��R��ʹ��L�����м�¼��С�ڻ������ֵ��R�м�¼��������ֵ
3���ݹ鴦����������L��R�ݹ���п�������

���ڲ���1��2�������������������˵����

���ӣ�



˵����


�������£�
*/


/*
//ѡ����ֵ���ָ��������ֵλ��
int Partition(int a[], int l, int r)
{
	//ѡ����ֵ
	int pivot = a[l];
	//�ָ�
	int i = l, j = r;
	while (i < j)
	{
		while(i < j && a[j] > pivot) // ���������ҵ�һ��С�ڵ���pivot����
			j--;  
		if(i < j) 
			a[i++] = a[j];
		
		while(i < j && a[i] <= pivot) // ���������ҵ�һ������pivot����
			i++;  
		if(i < j) 
			a[j--] = a[i];
	}
	a[i] = pivot;
	//������ֵλ��
	return i;
}

*/

/*
  ����1��2�ټ��ϲ���3��һ�������Ŀ��������������
*/
/*
void QuickSort(int a[], int l, int r)
{
	// �����������ֻ��0��1����¼���Ͳ�������
	if (r <= l)
	{
		return;
	}
	//ѡ����ֵ���ָ��������ֵ
	int i = Partition(a,l,r);
	//����ֵ��ߵ������н��еݹ��������
	QuickSort(a, l, i - 1);  
	//����ֵ�ұߵ������н��еݹ��������
    QuickSort(a, i + 1, r);
}*/
        

/*�Ż��Ŀ�������*/

//ѡ����ֵ���ָ��������ֵλ��
int Partition(int a[], int l, int r)
{
	//�Ż�1��ȡ�м���һ����Ϊ��ֵ
	Swap(a[l], a[(r-l)/2]);
	//ѡ����ֵ
	int pivot = a[l];
	//�ָ�
	int i = l, j = r;
	while (i < j)
	{
		while(i < j && a[j] > pivot) // ���������ҵ�һ��С�ڵ���pivot����
			j--;  
		if(i < j) 
			a[i++] = a[j];
		
		while(i < j && a[i] <= pivot) // ���������ҵ�һ������pivot����
			i++;  
		if(i < j) 
			a[j--] = a[i];
	}
	a[i] = pivot;
	//������ֵλ��
	return i;
}


void QuickSort(int a[], int l, int r)
{
	// �����������ֻ��0��1����¼���Ͳ�������
	if (r <= l)
	{
		return;
	}
	//�Ż�2��������г���С�ڵ�����ֵ(16���),ֹͣ�ָ������ݹ�
	if((r - l + 1) > 16)
	{
		//ѡ����ֵ���ָ��������ֵ
		int i = Partition(a,l,r);
		//����ֵ��ߵ������н��еݹ��������
		QuickSort(a, l, i - 1);  
		//����ֵ�ұߵ������н��еݹ��������
		QuickSort(a, i + 1, r);
	}
}



void ImprovedQuickSort(int a[], int l, int r)
{
	QuickSort(a, l, r);
	//�Ż�2��β������һ���������
	InsertSort(a,r - l + 1);
}



//	int a[3] = {5,24,24};��ʱ�������⣬����ѭ�� QuickSort(a,0,1)
/*
void QuickSort(int a[], int first, int last)
{
	if (first >= last)
	{
		return;
	}
	int mid = (first + last) / 2;
	int i = first, j = last;
	while(i < j)
	{
		while(i < j && a[i] < a[mid]) {
			i++;
		}

		while(i < j && a[j] > a[mid]) {
			j--;
		}
		if(i < j){
			// <=mid�ģ���i�����; >=mid����j�ұ�
			Swap(a[i], a[j]);
			i++;
			j--;
		}
	}

	QuickSort(a, 0, i - 1);
	QuickSort(a, i, last);
}*/

/*
void HeapShiftDown(int a[], int i, int n)
{
	int temp = a[i];
	int lchild = 2*i + 1;
	int rchild = 2*i + 2;
	while ((temp < a[lchild] || temp < a[rchild]) && i < n && lchild < n && rchild < n)
	{
		if (temp < a[lchild])
		{
			a[i] = a[lchild];
			i = lchild;
			lchild = 2*i + 1;
			rchild = 2*i + 2;
			continue;
		}

		if (temp < a[rchild])
		{
			a[i] = a[rchild];
			lchild = 2*i + 1;
			rchild = 2*i + 2;
			continue;
		}
	}
}
*/

//�ѵĲ���


/*
void MaxHeapFixDown(int a[], int i, int n)
{
	int temp = a[i];
	int j = 2*i + 1;
	while (j < n)
	{
		if (j + 1 < n && a[j + 1] > a[j]) //�����Һ�����������  
		{
			j = j + 1;
		}
		if (a[j] <= temp)
		{
			break;
		} 
		else 
		{
			a[i] = a[j]; //�ѽϴ���ӽ�������ƶ�,�滻���ĸ���㣬�����ڲ�������
			i = j;
			j = 2 * i + 1;
		}
	}
	a[i] = temp;
}
*/

//��a[i]���뵽��С��a[0...i-1]�е��ʵ�λ�ã��γɸ������С��a[0...i]�������ڲ������� 
void MinHeapFixUp(int a[], int i)
{
	int j,temp;
	temp = a[i];
	for (j = (i - 1)/2; j >= 0; j = (i-1)/2) //jΪ�����
	{
		if (a[j] > temp)
		{
			a[i] = a[j]; //�ѽϴ�ĸ���������ƶ�,�滻�����ӽ��  
			i = j;
		}
		else
		{
			break;
		}
	}
	a[i] = temp;
}

//����С�ѵ�����Ϊn�������µ�����num
void MinHeapAddNumber(int a[], int n, int num)  
{  
    a[n] = num;  
    MinHeapFixUp(a, n);  
}  


//��a[i]�������϶��µ��ؽ��ѣ�nΪ�������,�����ڲ������� 
void MinHeapFixDown(int a[], int i, int n)
{
	int temp = a[i];
	for (int j = 2 * i + 1; j < n ; j = 2 * i + 1) //jΪ�ӽ��
	{
		if (j + 1 < n && a[j + 1] > a[j])
		{
			j = j + 1; //�����ҽ��������С��
		}
		if (a[j] < a[i])
		{
			a[i] = a[j]; //�ѽ�С���ӽ�������ƶ�,�滻���ĸ���� 
			i = j;
		} 
		else 
		{
			break;
		}
	}
	a[i] = temp;
}

//ɾ����С�ڵ� 
void MaxHeapDeleteElement(int a[], int n)
{
	//����
	Swap(a[0], a[n-1]);
	//ɾ��
	MinHeapFixDown(a, 0, n-1);
}


//�ѻ����齨����С��
void MakeMinHeap(int a[], int n)
{
	for (int i = n/2 -1; i >= 0; i--)
	{
		MinHeapFixDown(a, i, n);
	}
}

//������
void MinHeapSort(int a[], int n)
{
	//�ѻ����飬������С��
	MakeMinHeap(a, n);
	for (int i = n-1; i > 0; i--)
	{
		Swap(a[i], a[0]);
		MinHeapFixDown(a, 0, i);
	}
}

/*---------------------------ShellSort---------------------------*/
void ShellSort1(int a[], int n) 
{
	//����
	for (int gap = n/2; gap >= 1; gap /=2)
	{
		//��������
		for (int i = 0; i < gap; i++)
		{
			//ʹ�ò���������ÿһ������	
			for (int j = i + gap; j < n; j += gap)
			{
				int temp = a[j];
				for (int k = j - gap; k >= 0; k -= gap)
				{
					if (a[k] > temp)
					{
						a[k + gap] = a[k]; 
					}
					else 
					{
						break;
					}
				}
				a[k + gap] = temp;
			}
		}
	}
}

void ShellSort2(int a[], int n) 
{
	//����
	for (int gap = n/2; gap >= 1; gap /=2)
	{
		//���ڴ�gap��ʼ��ÿһ���������ڱ���֮�ڽ��в�������	
		for (int j = gap; j < n; j += gap)
		{
			int temp = a[j];
			for (int k = j - gap; k >= 0; k -= gap)
			{
				if (a[k] > temp)
				{
					a[k + gap] = a[k]; 
				}
				else 
				{
					break;
				}
			}
			a[k + gap] = temp;
		}
	}
}


void CountingSort(int a[], int n, int k)
{
	//counted_a���ڴ�ż���
	int *counted_a = (int *)malloc(sizeof(int) * k);
	//sorted_a���ڴ���Ѿ�����õ�Ԫ��
	int *sorted_a = (int *)malloc(sizeof(int) * n);

	int i;
	for (i = 0; i < k; i++)
	{
		counted_a[i] = 0;
	}
	// ������ͳ�ƴ�����������Ԫ�صĳ��ִ���
	for (i = 0; i < n; i++)
	{
		counted_a[a[i]] ++;
	}

	//�������
	for (i = 1; i < k; i++)
	{
		counted_a[i] += counted_a[i - 1];
	}

	// ������������counted_a��������������a�е�Ԫ���ŵ���ȷ��λ��
	for (i = n-1; i >= 0; i--)
	{
		sorted_a[counted_a[a[i]] - 1] = a[i];
		counted_a[a[i]]--;
	}
	//���Ѿ���������鸴�ƻ�ԭ����ʼ����
	memcpy(a, sorted_a, sizeof(int) *n); 

	free(counted_a);
	free(sorted_a);

}


int main() 
{
	int a[5] = {25,13,50,18,35};
//	int a[3] = {5,24,24};
	int n = sizeof(a)/sizeof(int);
//	InsertSort3(a,n);
	int *temp = new int[n];
	CountingSort(a, n, 100);

	for (int i =0; i < n; i++) 
	{
		printf("%d ",a[i]);
	}
	return 0;
}
