#include "utils.h"

namespace {
char g32BitIntTextBuffer[12]; // Should be enough for int
}

namespace utils {
void strcpyn(char* dest, uint8_t destSize, const char* src) {
  for (uint8_t i=0; i<destSize-1; i++) {
    if (src[i]=='\0')  {
      break;
    }

    dest[i]=src[i];
  }

  dest[destSize-1] = '\0';
}

void swap(char *a, char *b)                                                                                                                                                                       
{
  if(!a || !b)
     return;

  char temp = *(a);
  *(a) = *(b);
  *(b) = temp;
}

void reverse(char *str, int length) 
{ 
	int start = 0; 
	int end = length -1; 
	while (start < end) 
	{ 
		swap((str+start), (str+end)); 
		start++; 
		end--; 
	} 
} 

char* itoa(int num) 
{ 
  char* str = g32BitIntTextBuffer;
	int i = 0; 
	bool isNegative = false; 

	if (num == 0) 
	{ 
		str[i++] = '0'; 
		str[i] = '\0'; 
		return str; 
	}

	if (num < 0) 
	{ 
		isNegative = true;
		num = -num; 
	} 

	while (num != 0) 
	{ 
		int rem = num % 10; 
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
		num = num/10; 
	}

	if (isNegative == true) 
		str[i++] = '-'; 

	str[i] = '\0';
	reverse(str, i); 
	return str; 
}
}