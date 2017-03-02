
unsigned char name[] = "bootloader";
unsigned char time[] = "2017-02-22";
unsigned char data[100];

void delay(int time)
{
	while(time--){
		if(time%2)
			time--;
		
	}
}

int main()
{
	int a;
	a = 20;
	a = a + 100;
	while(a) {
		a--;
		delay(a);
	}

	return 0;
}

