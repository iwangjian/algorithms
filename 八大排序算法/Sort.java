package temp;
import java.util.ArrayList;
import java.util.List;

public class Sort {

	/*
	 * 直接插入排序
	 */
	public void insertSort(int a[])
	{
		int temp = 0;
		for(int i=1; i<a.length; i++)
		{
			int j=i-1;
			temp = a[i];
			for(; j>=0&&temp<a[j]; j--)
			{
				a[j+1] = a[j];
			}
			a[j+1] = temp;
		}
	}
	/*
	 * 希尔排序
	 */
	public void shellSort(int a[])
	{
		int temp = 0;
		int d1 = a.length;
		while(true)
		{
			d1 = d1/2;
			int d = d1;
			for(int x=0; x<d; x++)
			{
				for(int i=x+d; i<a.length; i+=d)
				{
					int j=i-d;
					temp = a[i];
					for(; j>=0&&temp<a[j]; j-=d)
					{
						a[j+d] = a[j];
					}
					a[j+d] = temp;
				}
			}
			if(d == 1)
				break;
		}
	}
	/*
	 * 冒泡排序
	 */
	public void bubbleSort(int a[])
	{
		int temp = 0;
		for(int i = 0; i<a.length-1; i++)
		{
			for(int j=0; j<a.length-1-i; j++)
			{
				if(a[j] > a[j+1])
				{
					temp = a[j];
					a[j] = a[j+1];
					a[j+1] = temp;
				}
			}
		}
	}
	/*
	 * 快速排序
	 */
	public int getMiddle(int a[], int low, int high)
	{
		int temp = a[low];
		while(low < high)
		{
			while(low<high && a[high]>=temp)
			{
				high--;
			}
			a[low] = a[high];
			while(low<high && a[low]<=temp)
			{
				low ++;
			}
			a[high] = a[low];
		}
		a[low] = temp;
		return low;
	}
	public void quickSort(int a[], int low, int high)
	{
		if(low < high)
		{
			int middle = getMiddle(a,low,high);
			quickSort(a, low, middle-1);
			quickSort(a, middle+1, high);
		}
	}
	/*
	 * 选择排序
	 */
	public void selectSort(int a[])
	{
		int position = 0;
		int temp = 0;
		for(int i=0; i<a.length; i++)
		{
			position = i;
			temp = a[i];
			for(int j=i+1; j<a.length; j++)
			{
				if(a[j] < temp)
				{
					temp = a[j];
					position = j;
				}
			}
			a[position] = a[i];
			a[i] = temp;
		}
	}
	/* 堆排序
	 * @param H是待调整的数组
	 * @param s是待调整的元素的位置
	 * @param length是数组的长度
	 */
	public void adjustHeap(int H[], int s, int length)
	{
		int temp = H[s];
		int child = 2*s;
		while(child < length)
		{
			if(child+1 < length && H[child]<H[child+1])
			{
				child ++;
			}
			if(H[s] < H[child])
			{
				H[s] = H[child];
				s = child;
				child = 2*s;
			}
			else
				break;
			H[s] = temp;
		}
	}
	public void buildHeap(int H[])
	{
		for(int i=H.length/2; i>=1; i--)
		{
			adjustHeap(H, i, H.length);
		}
	}
	public void heapSort(int H[])
	{
		buildHeap(H);
		for(int i=H.length-1; i>0; i--)
		{
			int temp = H[i];
			H[i] = H[1];
			H[1] = temp;
			adjustHeap(H,1,i);
		}
	}
	/*
	 * 归并排序算法-递归形式
	 * 1.merge()为归并函数
	 * 2.mergeSort()为排序函数
	 */
	public void merge(int a[], int left, int center, int right)
	{
		int []temp = new int[a.length];
		int mid = center+1;
		int index = left, t = left;
		while(left<=center && mid<=right)
		{
			if(a[left] <= a[mid])
			{
				temp[index] = a[left];
				index++;
				left++;
			}
			else
			{
				temp[index] = a[mid];
				index++;
				mid++;
			}
		}
		while(mid <= right){
			temp[index] = a[mid];
			index++;
			mid++;
		}
		while(left <= center){
			temp[index] = a[left];
			index++;
			left++;
		}
		while(t <= right)
		{
			a[t] = temp[t];
			t++;
		}
	}
	public void mergeSort(int a[], int left, int right)
	{
		if(left < right)
		{
			int center = (left+right)/2;
			mergeSort(a, left, center);
			mergeSort(a, center+1, right);
			merge(a,left,center,right);
		}
	}
	/*
	 * 基数排序
	 */
	public void radixSort(int a[])
	{
		int times = 0;
		int max = a[0];
		for(int i=0; i<a.length; i++)
		{
			if(a[i] > max){
				max = a[i];
			}
		}
		while(max > 0)
		{
			max = max/10;
			times = times+1;
		}
		List<ArrayList<Integer>> queues = new ArrayList<ArrayList<Integer>>();
		for(int i=0; i<10; i++)
		{
			ArrayList<Integer> queue_i = new ArrayList<Integer>();
			queues.add(queue_i);
		}
		for(int i=0; i<times; i++)
		{
			for(int j=0; j<a.length; j++)
			{
				int x = (a[j]%(int)Math.pow(10, i+1))/(int)Math.pow(10, i);
				ArrayList<Integer> q = queues.get(x);
				q.add(a[j]);
				queues.set(x, q);
			}
			int count = 0 ;
			for(int j=0; j<10; j++)
			{
				while(!queues.get(j).isEmpty())
				{
					a[count] = queues.get(j).get(0);
					queues.get(j).remove(0);
					count++;
				}
			}
		}
		int count = 0 ;
		for(int i=0; i<10; i++)
		{
			while(!queues.get(i).isEmpty())
			{
				a[count] = queues.get(i).get(0);
				queues.get(i).remove(0);
				count++;
			}
		}
	}
	
	public static void main(String []args)
	{
		Sort s = new Sort();
		int a1[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.insertSort(a1);
		for(int i=0; i<a1.length; i++)
		{
			System.out.print(a1[i]+" ");
		}
		System.out.println();
		int a2[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.shellSort(a2);
		for(int i=0; i<a2.length; i++)
		{
			System.out.print(a2[i]+" ");
		}
		System.out.println();
		int a3[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.bubbleSort(a3);
		for(int i=0; i<a3.length; i++)
		{
			System.out.print(a3[i]+" ");
		}
		System.out.println();
		int a4[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.quickSort(a4, 0, 10);
		for(int i=0; i<a4.length; i++)
		{
			System.out.print(a4[i]+" ");
		}
		System.out.println();
		int a5[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.selectSort(a5);
		for(int i=0; i<a5.length; i++)
		{
			System.out.print(a5[i]+" ");
		}
		System.out.println();
		int H[] = {0,48,39,67,52,16,22,17,68,24};
		//int H[] = {0,52,43,68,89,77,16,24,52,80,31,22};
		s.buildHeap(H);
		//s.heapSort(H);
		for(int i=1;  i<H.length; i++)
		{
			System.out.print(H[i]+" ");
		}
		System.out.println();
		int a7[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.mergeSort(a7, 0, 10);
		for(int i=0; i<a7.length; i++)
		{
			System.out.print(a7[i]+" ");
		}
		System.out.println();
		int a8[] = {52,43,68,89,77,16,24,52,80,31,22};
		s.radixSort(a8);
		for(int i=0; i<a8.length; i++)
		{
			System.out.print(a8[i]+" ");
		}
	}
}
