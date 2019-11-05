# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

void lower1(char *s)
{
  size_t i;
  for (i = 0; i < strlen(s); i++)
    if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] -= ('A' - 'a');
}

void lower2(char *s)
{
  size_t i;
  size_t len = strlen(s);
  for (i = 0; i < len; i++)
    if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] -= ('A' - 'a');
}

int main()
{
	int size = 1000;
	char str[size];
	for(int i = 0; i < size; i ++)
		str[i] = rand()%26 + 'a';
	//printf("%s\n", str);
	
	clock_t start1 = clock();
   	lower1(str);
    	clock_t end1 = clock();
    	printf("time1 = %lu\n", end1-start1);
    
    	clock_t start2 = clock();
    	lower2(str);
    	clock_t end2 = clock();
    	printf("time2 = %lu\n", end2-start2);
	/* code */
	return 0;
}
