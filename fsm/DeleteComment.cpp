/*
* ɾ��c�����еĵ��и�����ע�ͣ�ע�����е�action
*
*/

#include <stdio.h>
int main(void)
{
    char c, state;
    state = 0;
    while ((c = getchar()) != EOF) 
	{
		if (state == 0)		
		{
			if (c == '/') // ���ӣ� int a = b; /
			{
				state = 1;
			}
			else
			{
				putchar(c); //action
			}
		}
		else if (state == 1)
		{
			if (c == '/')  //���ӣ� int a = b; //
			{
				state = 2;

			} 
			else if (c == '*')  //���ӣ� int a= b; /*
			{
				state = 3;
			} 
			else  //���ӣ� <common/md5.h> or 8/3
			{
				state = 0;
				putchar('/'); //action
				putchar(c); //action
			}
		}
		else if (state == 2)	
		{
			if (c == '\n')  //���ӣ� int a = b; //hehe<enter>
			{
				state = 0;
				putchar(c); //action
			}
			//���ӣ� int a = b; //hehe
		}
		else if (state == 3)	
		{
			if (c == '*')  //���ӣ� int a = b; /*heh*
			{
				state = 4;
			}
			//���ӣ� int a = b; /*hehe
		}
		else if (state == 4)
		{
			if (c == '/')  //���ӣ� int a = b; /*hehe*/
			{
				state = 0;
			}
			else  //���ӣ� int a = b; /*hehe*h
			{
				state = 3;
			}
		}
		else
		{
			printf("state error!");
		}
		
	}
	return 0;
}
	
