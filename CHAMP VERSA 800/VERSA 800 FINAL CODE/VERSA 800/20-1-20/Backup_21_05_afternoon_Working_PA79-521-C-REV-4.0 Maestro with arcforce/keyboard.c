// INITILIZE THE COLUMNS AND ROWS
void init_keyboard()
{
	COLUMN0IO = 1;
	COLUMN1IO = 1;
	COLUMN2IO = 1;
	COLUMN3IO = 1;
	ROW0IO = 0;
	ROW1IO = 0;
	ROW2IO = 0;
}

//************************************************************************************************************************
char keyscan(void)
{
 temp=keypress();        
 if(temp =='1')
	  { 
	    //diswin1[0]=keydetect();
	    //display_data();
	    key=keydetect();
	    debouncedelay();
	  }
 else
	 {
	 return('0');
	 }
return(key);
}

//************************************************************************************************************************
// TO FIND OUT IF THE KEY IS PRESSED
char keypress(void)
	{
	ROW0LAT=0;
	ROW1LAT=0;
	ROW2LAT=0;
			{
				if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
				return('1');
				else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
				return('1');
				else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
				return '1';
				else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
				return '1';
				else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
				return '0';
			}
	}

//************************************************************************************************************************
// IF THE KEY IS PRESSED DETECT THE KEY

char keydetect(void)
	{  
			ROW0LAT=1;  //ROW 2 KEY DECTECT
			ROW1LAT=1;
			ROW2LAT=0;		        
					    if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
					    return('9');
					    else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
					    return('A');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
					    return('B');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
					    return('C');
		 	
	        ROW0LAT=1; //ROW 1 KEY DECTECT
			ROW1LAT=0;
			ROW2LAT=1;   
					    if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
					    return('5');
					    else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
					    return('6');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
					    return('7');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
					    return('8');
	
			ROW0LAT=0;  //ROW 0 KEY DECTECT
			ROW1LAT=1;
			ROW2LAT=1;
					    if (COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
					    return('1');
					    else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
					    return('2');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
					    return('3');
					    else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
					    return('4');
						
	}

//************************************************************************************************************************
// PROVIDE THE DEBOUNCE TIME.

void debouncedelay(void)
	{
		  for(i=0;i<50000;i++);  
          asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
		  asm("NOP");
	}
	
	
	
	