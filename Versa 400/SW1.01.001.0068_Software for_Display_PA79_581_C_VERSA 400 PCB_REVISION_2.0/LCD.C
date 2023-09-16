void lcd_int()
{
    LCDRSIO=0;  
    LCDENIO=0;
    LCDCS1IO=0;  
    LCDCS2IO=0;
    DB0IO=0;
    DB1IO=0;
    DB2IO=0;
    DB3IO=0;
    DB4IO=0;
    DB5IO=0;
    DB6IO=0;
    DB7IO=0;
    clrlcd();
    ador_logo();
    display_start(0x2F);
    displayon();
    delayy(100);
    display_start('[');
    displayoff();
    delayy(100);
    display_start(0x2F);
    displayon();
    delayy(100);
    display_start('[');
    displayoff();
    delayy(100);
    display_start(0x2F);
    displayon();
    //#############################
	clrlcd();
	lcdput(0,0,ar0);
	lcdput(2,0,ar1);
	lcdput_bold(4,0,ar2);
	lcdput(6,0,ar3);
	
	/*	
	clrlcd();
	lcdput(0,0,ar11);
	lcdput(2,0,ar12);
	Model_select_num_char(Model);
	modelupdate();
	if(Model==1)
		lcdput(5,0,ar13);
	else if(Model==2)
		lcdput(5,0,ar14);
	else if(Model==3)
		lcdput(5,0,ar15);
	else if(Model==4)
		lcdput(5,0,ar16);
      
	diswin1[0]='R';
	diswin1[1]='E';
	diswin1[2]='V';
	diswin1[3]='N';
	
	diswin2[0]='0';
	diswin2[1]='0';
	diswin2[2]='1';

	delayy(100);
   //#############################
    clrlcd();
    dpinit_flag=1;
    lcdput(0,0,ar4);
    lcdput(2,0,ar5);
    lcdput(4,0,ar6);
    lcdput(6,0,ar7);   
*/
}
    
void ctrloff()
{
  LCDRSLAT=0;
  LCDENLAT=0;
  LCDCS1LAT=0;
  LCDCS2LAT=0;
  delay(1000);
}

void displayon()
{
  ctrloff();
  LCDCS1LAT=1;
  LCDCS2LAT=1;
  val=0X3F;
  lcddatalat(val);
  delay(100);	 
  LCDRSLAT=0;
  LCDENLAT=1;
  delay(10);
  LCDENLAT=0;
  LCDCS1LAT=0;
  LCDCS2LAT=0;
}

void displayoff()
{
  ctrloff();
  LCDCS1LAT=1;
  LCDCS2LAT=1;
  val=0X3E;
  lcddatalat(val);
  delay(100);	 
  LCDRSLAT=0;
  LCDENLAT=1;
  delay(10);
  LCDENLAT=0;
  LCDCS1LAT=0;
  LCDCS2LAT=0;
}    

void delay(unsigned int n)
{
	//unsigned int i;
	n=2;//10;
	for(id=0;id<n;id++);                  
}

void delayy(unsigned int n)
{
	//unsigned int id,jd;
	for(id=0;id<n;id++)                  
	for(jd=0;jd<40000;jd++);
}

void selectpage(unsigned char x)
{
	 ctrloff();
	 val=0XB8|x;
	 lcddatalat(val);	 
	 delay(100);
	 LCDRSLAT=0;
	 LCDENLAT=1;
	 delay(10);
	 LCDCS1LAT=1;
	 LCDCS2LAT=1;
	 LCDENLAT=0;
	 LCDCS1LAT=0;
	 LCDCS2LAT=0; 
}
void selectcolumn1(unsigned char x)
{
 ctrloff();
 if(x<64)
 {
     col=x;
	 LCDCS1LAT=1;
	 LCDCS2LAT=0;
	 val=(0X40|(x&63));
	 lcddatalat(val);
	 delay(100);	 
	 LCDRSLAT=0;
	 LCDENLAT=1;
	 delay(10);
	 LCDENLAT=0;
	 LCDCS1LAT=1;
	 LCDCS2LAT=0; 
 }
} 
void selectcolumn2(unsigned char x)
{ 
 ctrloff();
 if(x>63)
 {
	 col=x;
     LCDCS1LAT=0;
	 LCDCS2LAT=1;
	 val=0X40|((x-64)&63);
	 lcddatalat(val);
	 delay(100);	 
	 LCDRSLAT=0;
	 LCDENLAT=1;
	 delay(10);
	 LCDENLAT=0;
	 LCDCS1LAT=0;
	 LCDCS2LAT=1;
  }
}

void clrlcd()
{
 unsigned char i,j;
 for(j=0;j<8;j++)
 {
   selectpage(j);
	 for(i=0;i<128;i++)
		 {
		   if(i==0)
		   {
		    selectcolumn1(0);
		   }
		   if(i==64)
		   {
		    selectcolumn2(64);
		   }
		   data(&m,1);
		 }
 } 
}


void ador_logo()
{
 unsigned char i,j,k;
 for(j=0;j<8;j++)
 {
   selectpage(j);
   selectcolumn1(0);
   i=16*j;
   k=(16*j)+16;
   while(i<k)
   {
	   data(&adorrlogo[i][0],8);
	   i++;
   } 
 }
}

void onlcd()
{
 unsigned char i,j;
 for(j=0;j<1;j++)
 {
   selectpage(j);
	 for(i=0;i<128;i++)
		 {
		   if(i==0)
		   {
		    selectcolumn1(0);
		   }
		   if(i==64)
		   {
		    selectcolumn2(64);
		   }
		   data(&n,1);
		 }
 } 
}
void data(unsigned char*value,unsigned char limit)
{
	unsigned char p;
	for(p=0;p<limit;p++)
     {
	    if(col<64)
		{
	      LCDCS1LAT=1;
		  LCDCS2LAT=0;
	      val=*(value+p);	 
		  lcddatalat(val);
		  delay(100);	 
		  LCDRSLAT=1;
		  LCDENLAT=1;
		  delay(10);
		  LCDENLAT=0;
		  LCDCS1LAT=1;
		  LCDCS2LAT=0;
          LCDRSLAT=0;
		  col++;		
		}
		else
		{ 
		  //if(col==64)
		  if(col>=64)
		  selectcolumn2(col);	
	      LCDCS1LAT=0;
		  LCDCS2LAT=1;
	      val=*(value+p); 
		  lcddatalat(val);
		  delay(100);	 
		  LCDRSLAT=1;
		  LCDENLAT=1;
		  delay(10);
		  LCDENLAT=0;
		  LCDCS1LAT=0;
		  LCDCS2LAT=1;	
          LCDRSLAT=0;	
		  col++;
		}
	}
}  

void lcddatalat(unsigned char dat)
{
  DB0LAT=dat&0X01;
  DB1LAT=((dat>>1)&0X01);
  DB2LAT=((dat>>2)&0X01);
  DB3LAT=((dat>>3)&0X01);
  DB4LAT=((dat>>4)&0X01);
  DB5LAT=((dat>>5)&0X01);  
  DB6LAT=((dat>>6)&0X01);
  DB7LAT=((dat>>7)&0X01);
}

void lcdscan()
{
}
//{
//  encod1=scanencoder1();
//  if(encod1!='$' && eswitch==0)
//     {
//        if(encod1=='+')
//           {  
//	          if(linee<6 && prevstatus>2)      
//               {
//	              linee+=1;
//                  prevstatus=0; 
//	           }
//              /*else if(linee>=6 && prevstatus>2)
//               {
//	              linee=1;
//	              prevstatus=0;
//               }*/ 
//              prevstatus++;
//           }
//        else if(encod1=='-')
//           {
//	          if(linee>1 && prevstatus>4) 
//                {
//	              linee-=1;
//                  prevstatus=0; 
//	            }  
//              /*else if(linee<=1 && prevstatus>2)
//                {
//	              linee=6;
//	              prevstatus=0;
//                }*/
//              prevstatus++;
//           }   
//     }
//           
//  else
//    {
//       linee=linee;
//    }
///***************************************IF ENCODER SWITCH PRESSED*******************************************************************/  
//if(eswitch==0)
//{
//  switch(linee)                            //GO TO PARTICULAR LINE TO UPDATE
//  {
//     case 1:
//            selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[127][0],8);
//			  delay(10);
//            	  break;
//     case 2:
//            selectpage(4);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[127][0],8);
//			  delay(10);
//            break;
//      case 3:
//              selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0); 
//			  data(&character[127][0],8);
//			  delay(10);
//            break;
//      case 4:
//              selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);	  
//			  data(&character[127][0],8);
//			  delay(10);
//            break;
//      case 5:
//              selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(0);
//			  selectcolumn1(0);	  
//			  data(&character[127][0],8);
//			  delay(10);
//            break;
//      case 6:
//              selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(2);
//			  selectcolumn1(0);	  
//			  data(&character[127][0],8);
//			  delay(10); 
//            break;
//      /*case 7:
//              selectpage(0);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(2);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(6);
//			  selectcolumn1(0);
//			  data(&character[0][0],8);
//			  selectpage(4);
//			  selectcolumn1(0);	  
//			  data(&character[127][0],8);
//			  delay(10); 
//            break;*/
//     default:
//            break;
//  }
//} 
// //************************************************************************************************************ 
//if(eswitch==1)
//{
//  switch(linee)
//  {
//     case 1:
//            if(lcdscan_flag==1)
//		    {
//			selectpage(0);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//			selectpage(0);
//            	selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//     case 2:
//            if(lcdscan_flag==1)
//		    {
//				selectpage(2);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//				selectpage(2);
//            	selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//      case 3:
//            if(lcdscan_flag==1)
//		    {
//				selectpage(4);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//				selectpage(4);
//           		selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//      case 4:
//            if(lcdscan_flag==1)
//		    {
//				selectpage(6);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//				selectpage(6);
//            	selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//      case 5:
//            if(lcdscan_flag==1)
//		    {
//				selectpage(0);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//				selectpage(0);
//            	selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//      case 6:
//            if(lcdscan_flag==1)
//		    {
//				selectpage(2);
//            	selectcolumn1(0);	  
//            	data(&character[127][0],8);
//		    }
//		    else
//		    {
//				selectpage(2);
//            	selectcolumn1(0);	  
//            	data(&character[0][0],8);
//		    }
//            break;
//      /*case 7:
//            if(lcdscan_flag==1)
//		    {
//			selectpage(4);
//            selectcolumn1(0);	  
//            data(&character[127][0],8);
//		    }
//		    else
//		    {
//			selectpage(4);
//            selectcolumn1(0);	  
//            data(&character[0][0],8);
//		    }
//            break;*/
//     default:
//            break;
//  }
//}
////*********************************************************************************************************************
//if(eswitch==0)
//{      
//       if(linee<=4) 
//	   {
//            if(glcd_flag==0)
//            {
//            	clrlcd();
//			    lcdput(0,0,ar4);
//    	        lcdput(2,0,ar5);
//        	    lcdput(4,0,ar6);
//            	lcdput(6,0,ar7);	
//		 		Matupdate();
//		    	Diaupdate(); 
//		    	speedupdate(); 
//		    	timeupdate();
//            	glcd_flag=1;
//		    }
//            if(line_flag==1)
//		    {
//			selectpage(6);
//            	selectcolumn2(120);	  
//            	data(&character[18][0],8);
//		    }
//		    else
//		    {
//				selectpage(6);
//            	selectcolumn2(120);	  
//            	data(&character[0][0],8);
//		    }
//		}
//       if(linee>=5) 
//		 {
//            if(glcd_flag==1)
//            {
//            	clrlcd();
//            	lcdput(0,0,ar8);
//            	lcdput(2,0,ar9);
//            	//lcdput(4,0,ar10);		
//		    	glcd_flag=0;
//            }
//            if(line_flag==1)
//		    {
//				selectpage(0);
//            	selectcolumn2(120);	  
//            	data(&character[17][0],8);
//		    }
//		    else
//		    {
//				selectpage(0);
//            	selectcolumn2(120);	  
//            	data(&character[0][0],8);
//		    }
//		}
//}	
////***************************************************************************************************************************
// 
//          if(point>=300)
//          {
//	          if(lcdscan_flag==1)
//	          	lcdscan_flag=0;
//	          else
//	          	lcdscan_flag=1;
//              point=0;
//          }
//          else
//          	point++;
//
//          if(line_blink>=100)
//          {
//              if(line_flag==1)
//	          	line_flag=0;
//	          else
//	          	line_flag=1;
//              line_blink=0;
//          }
//          else
//          line_blink++;
////*****************************************************************************************************************************
//if(eswitch==1)
//{
//  switch(linee)
//  {
//    case 1:
//         if(encod1!='$' && setupmode==0)
//	     {
//			     if(encod1=='+' && material<2)		//setcurrent<1200)
//			     { 
//		           		material=material+1;				//+;//setcurrent=setcurrent+1; 
//				}
//		         	else if(encod1=='-' && material > 1)	//setcurrent>200)
//	     		  	{ 
//		           		material=material-1;				////setcurrent=setcurrent-1;
//	     		  	}
//          } 
//          else  
//	    {
//			    material=material;						//setcurrent=setcurrent;
//	     }
//          break;
//    case 2:
//         if(encod1 != '$')
//	     {
//		    if(setupmode==0) 
//		   {
//			     	if(encod1=='+' && diameter<4 )      //((diameter<4 && material==1)|| (diameter<2 && material==2)))//  || //setvoltage<500)
//			     	{ 
//		           		diameter=diameter+1;//setvoltage=setvoltage+1;
//		           	}
//			     	else if(encod1=='-' && diameter>1)//setvoltage>=151)
//			     	{ 
//		           		diameter=diameter-1;//setvoltage=setvoltage-1;
//		         	}
//          	    }
// 			else
// 			{
//				if(encod1=='+' && Model<4)//setvoltage<500)
//			     	{ 
//		           		Model=Model+1;//setvoltage=setvoltage+1;
//		           	}
//			     	else if(encod1=='-' && Model>1)//setvoltage>=151)
//			     	{ 
//		           		Model=Model-1;//setvoltage=setvoltage-1;
//		         	}
// 			}    	
//        }    	    
//	    else 
//	    {
//			      diameter=diameter;//setvoltage=setvoltage;
//			      Model=Model;
//	    }
//        break;
//    case 3:
//           if(encod1 != '$')
//		{
//		     if(encod1 =='+' && kdgain<500)//setcarrspeed<160)
//		     { 
//	            	kdgain=kdgain+1;//setcarrspeed=setcarrspeed+1;
//	           }
//		     else if(encod1 =='-' && kdgain>1)//setcarrspeed>10)
//		     { 
//	           		kdgain=kdgain-1;//setcarrspeed=setcarrspeed-1;
//	          }
//		}    
//		else 
//		{
//			kdgain=kdgain;//setcarrspeed=setcarrspeed; 
//		} 
//           break;
//    case 4:    
//           if(encod1 != '$')
//	     {
//		     if(encod1=='+' && settime<10)
//		     { 
//	           		settime=settime+1;
//	         	}
//		     else if(encod1=='-' && settime>1)
//		     { 
//	           		settime=settime-1;
//	         	}
//          }    
//	     else 
//	     {
//	      	settime=settime;
//	     }
//           if(settime<10)
//            {
//	            
//                 ar7[12]=0X30+(settime%10);
//                 ar7[11]=48;
//            }
//           else
//            {
//                ar7[11]=0X30+(settime/10);
//                ar7[12]=0X30+(settime%10);
//            }
//            ar7[10]=':';             
//            
//           break;
//    	case 5:
//           if(encod1 != '$')
//			     {
//				     if(encod1=='+' && memloc<10)
//				     { 
//			           memloc=memloc+1;
//			         }
//				     else if(encod1=='-' && memloc>1)
//				     { 
//			           memloc=memloc-1;
//			         }
//		         }    
//			else 
//				     {
//				      memloc=memloc;
//				     }
//            if(memloc<10)
//             {ar8[19]=0X30+(memloc%10);ar8[18]=48;}
//            else
//             {ar8[18]=0X30+(memloc/10);ar8[19]=0X30+(memloc%10);}
//            break;
//    case 6:
//            if(encod1 != '$')
//			     {
//				     if(encod1=='+' && recloc<10)
//				     { 
//			           recloc=recloc+1;
//			         }
//				     else if(encod1=='-' && recloc>1)
//				     { 
//			           recloc=recloc-1;
//			         }
//		         }    
//		    else 
//		    {
//			      recloc=recloc;
//		    }
//	            if(recloc<10)
//	             {
//				ar9[15]=0X30+(recloc%10);
//				ar9[14]=48;
//			  }
//	            else
//	             {
//				ar9[14]=0X30+(recloc/10);
//				ar9[15]=0X30+(recloc%10);
//			  }
//            break;
//    /*case 7:
//            if(encod1 != '$')
//			     {
//				     if(encod1=='+' && wiresize<4)
//				     { 
//			           wiresize=wiresize+1;
//			         }
//				     else if(encod1=='-' && wiresize>=1)
//				     { 
//			           wiresize=wiresize-1;
//			         }
//		         }    
//		    else 
//				     {
//				       wiresize=wiresize;
//				     }
//          switch(wiresize)
//             {
//	            case 0:
//                   ar10[18]=0X30+2;ar10[20]=0X30+5;ar10[21]=0X30+0;
//                   break ;
//                case 1:
//                   ar10[18]=0X30+3;ar10[20]=0X30+1;ar10[21]=0X30+5;
//                   break;
//                case 2:
//                   ar10[18]=0X30+4;ar10[20]=0X30+2;ar10[21]=0X30+0;
//                   break;
//                case 3:
//                   ar10[18]=0X30+5;ar10[20]=0X30+0;ar10[21]=0X30+0;
//                   break;
//                case 4:
//                   ar10[18]=0X30+6;ar10[20]=0X30+0;ar10[21]=0X30+0;
//                   break;
//                default:
//                   break;
//             }   
//            break;*/
//    default:
//            break;
//  }
// }   
//}

void lcdput(unsigned char x,unsigned char y,const unsigned char *str)
{
  unsigned int k=0;
  ctrloff();
  selectpage(x);
  if(y<64)
  	selectcolumn1(y);
  else
  	selectcolumn2(y);
  //selectcolumn1(y);
  data(&character[0][0],8);					//FOR ELIMINATE FIRST COLUMN
  while(*str!='\0')
  {
	  k=*str;//-32;                     //HOLD THE VALUE AT LOCATION STR+I
	  
	  //if(k>=48 && k<=57) // ||k==0)     //FOR DATA 0-9 bold size
	  //{
	  // 	data(&character[k][0],8);
	  //}
	  //else								//FOR CHARACTERS A-Z
	  {
		   k=k-32;
		   if(k==0)
		   data(&font[k][0],2);
		   else
		   data(&font[k][0],6); 
      } 
	  str++;      
   }
}

void lcdput_bold(unsigned char x,unsigned char y,const unsigned char *str)
{
  unsigned int k=0;
  ctrloff();
  selectpage(x);
  if(y<64)
  	selectcolumn1(y);
  else
  	selectcolumn2(y);
  //selectcolumn1(y);
  data(&character[0][0],8);
  while(*str!='\0')
   {
	 k=*str;//-32;                     //HOLD THE VALUE AT LOCATION STR+I
	  
	 if(k==32)
		data(&character[k][0],2);
	 else
		data(&character[k][0],8); 

	  //if(k>=48 && k<=57) // ||k==0)     //FOR DATA 0-9
	  //{
	  // 	data(&character[k][0],8);
	  //}
	  //else
	  /*								//FOR CHARACTERS A-Z
	  {
		   k=k-32;
		   if(k==0)
		   data(&font[k][0],2);
		   else
		   data(&font[k][0],6); 
      } */
	  str++;      
   }
}

void tigtunstenupdate(void)
{
	unsigned int k=0;
  	ctrloff();
  	selectpage(4);
  	selectcolumn2(84);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		//k=disp_data_arr[0];
		//data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}



}
void tigcurrupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(2);
  selectcolumn2(84);
  {
	    k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
		//k=disp_data_arr[3];
		//data(&character[k][0],8);   
  }
}


void arcforceupdate(void)
{
	unsigned int k=0;
  	ctrloff();
  	selectpage(4);
  	selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}	

void passwordupdate(unsigned int iHex)
{
	unsigned int k=0;
    unsigned char cTestarr[5];

     cTestarr[3]= 0x30 + (iHex % 10);
     iHex /= 10;  
     cTestarr[2]= 0x30 + (iHex % 10);
     iHex /= 10;
     cTestarr[1]= 0x30 + (iHex % 10);
     iHex /= 10;
     cTestarr[0]= 0x30 + iHex;
	  ctrloff();
  	selectpage(2);
  	selectcolumn1(50);//64);//64); 9*6
   {
		if (cPWstarblinkcnt == 0)
		{
		k='*';
		data(&character[k][0],8);
		k='*';
		data(&character[k][0],8);
		k='*';
		data(&character[k][0],8);
		k='*';
		data(&character[k][0],8);		
		}
		else
		{
		k= cTestarr[0];
		data(&character[k][0],8);
		k=cTestarr[1];
		data(&character[k][0],8);
		k=cTestarr[2];
		data(&character[k][0],8);
		k=cTestarr[3];
		data(&character[k][0],8);		
		}
	}
	
}	

void programupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(0);
  selectcolumn2(108);
  {
	    //k='-';
	    //k=k-32;
	    //data(&font[k][0],6);
    	k='P';
	    k=k-32;
	    data(&font[k][0],6);
    	k=disp_data_arr[1];
		k=k-32;
	    data(&font[k][0],6);
    	k=disp_data_arr[2];
		k=k-32;
	    data(&font[k][0],6);
  }
}
		
void peakampupdate(void)
{
 unsigned int k=0;
  ctrloff();
  selectpage(6);
  selectcolumn2(0);
  {
	    k=0;
		data(&character[k][0],8);
		data(&font[k][0],6);
		data(&font[k][0],6);
	    data(&font[k][0],6);
	    data(&font[k][0],6);
	}	
}

void noprogramupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(6);
  selectcolumn2(0);
  {
	    k=':';
		data(&character[k][0],8);
		k='N';
	    k=k-32;
	    data(&font[k][0],6);
		k='O';
	    k=k-32;
	    data(&font[k][0],6);
		k='P';
	    k=k-32;
	    data(&font[k][0],6);
	    k='G';
	    k=k-32;
	    data(&font[k][0],6);
	}	
	
}
	

void currupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(2);
  selectcolumn2(64);
  {
	    k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
		//k=disp_data_arr[3];
		//data(&character[k][0],8);   
  }
}
//------------------
void datafordebug(unsigned int iHex)
{
  unsigned int k=0;
  unsigned char cTestarr[5];

     cTestarr[4]= 0x30 + (iHex % 10);
     iHex /= 10;    	 	
     cTestarr[3]= 0x30 + (iHex % 10);
     iHex /= 10;  
     cTestarr[2]= 0x30 + (iHex % 10);
     iHex /= 10;
     cTestarr[1]= 0x30 + (iHex % 10);
     iHex /= 10;
     cTestarr[0]= 0x30 + iHex;
	  ctrloff();
	  selectpage(1);
	  selectcolumn2(64);
	  {
		    k=cSign1;
			data(&character[k][0],8);
			k=cTestarr[0];
			data(&character[k][0],8);
			k=cTestarr[1];
			data(&character[k][0],8);
			k=cTestarr[2];
			data(&character[k][0],8);
			k=cTestarr[3];
			data(&character[k][0],8); 
			k=cTestarr[4];
			data(&character[k][0],8); 		
	  }
//--------
     cTestarr[4]= 0x30 + (iTestpeak2 % 10);
     iTestpeak2 /= 10;
     cTestarr[3]= 0x30 + (iTestpeak2 % 10);
     iTestpeak2 /= 10;  
     cTestarr[2]= 0x30 + (iTestpeak2 % 10);
     iTestpeak2 /= 10;
     cTestarr[1]= 0x30 + (iTestpeak2 % 10);
     iTestpeak2 /= 10;
     cTestarr[0]= 0x30 + iTestpeak2;
	  ctrloff();
	  selectpage(5);
	  selectcolumn2(64);
	  {
		    k=cSign2;
			data(&character[k][0],8);
			k=cTestarr[0];
			data(&character[k][0],8);
			k=cTestarr[1];
			data(&character[k][0],8);
			k=cTestarr[2];
			data(&character[k][0],8);
			k=cTestarr[3];
			data(&character[k][0],8); 
			k=cTestarr[4];
			data(&character[k][0],8); 			
		
	  }
//--------	  
//--------
     cTestarr[4]= 0x30 + (iTestpeak3 % 10);
     iTestpeak3 /= 10;  
     cTestarr[3]= 0x30 + (iTestpeak3 % 10);
     iTestpeak3 /= 10;  
     cTestarr[2]= 0x30 + (iTestpeak3 % 10);
     iTestpeak3 /= 10;
     cTestarr[1]= 0x30 + (iTestpeak3 % 10);
     iTestpeak3 /= 10;
     cTestarr[0]= 0x30 + iTestpeak3;
	  ctrloff();
	  selectpage(6);
	  selectcolumn2(64);
	  {
		    k=cSign3;
			data(&character[k][0],8);
			k=cTestarr[0];
			data(&character[k][0],8);
			k=cTestarr[1];
			data(&character[k][0],8);
			k=cTestarr[2];
			data(&character[k][0],8);
			k=cTestarr[3];
			data(&character[k][0],8); 
			k=cTestarr[4];
			data(&character[k][0],8); 		
	  }
//--------	  
}
//------------------
void wirespeedupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(8);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k='.';
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}



void voltupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(4);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void save_update(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(5);
  selectcolumn2(64);//64);//64); 9*6
  {
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
   }
}

void recall_update(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(6);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void preflowupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(2);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}
void burnbackupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void postflowupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(4);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

 

void Gcreepspeedupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(5);
  selectcolumn2(70);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void cratercurrentupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(6);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void cratervoltageupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(7);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}
//################################################################
void pulseweldmodeupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(2);
  selectcolumn2(72);//64)
   {
		k=':';
		data(&character[k][0],8);
		
		if(para.pulseweldmode==0)
		{
			k='S';
			data(&character[k][0],8);
			k='I';
			data(&character[k][0],8);
			k='N';
			data(&character[k][0],8);
			k='G';
			data(&character[k][0],8);
			k='L';
			data(&character[k][0],8);
			k='E';
			data(&character[k][0],8);
		}
		else
		{
			k='T';
			data(&character[k][0],8);
			k='W';
			data(&character[k][0],8);
			k='I';
			data(&character[k][0],8);
			k='N';
			data(&character[k][0],8);
			k=' ';
			data(&character[k][0],8);
			k=' ';
			data(&character[k][0],8);
		}	
			
			
			
			
			
		//k=disp_data_arr[0];
		//data(&character[k][0],8);
		//k=disp_data_arr[1];
		//data(&character[k][0],8);
		//k='.';
		//data(&character[k][0],8);
		//k=disp_data_arr[2];
		//data(&character[k][0],8);
	}
}

void twinpulsefrequpdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  selectcolumn2(72);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void twinpulsedutyupdate(void)
{
  	unsigned int k=0;
  	ctrloff();
  	selectpage(4);
  	selectcolumn2(72);
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void twinpulseratioupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(5);
  selectcolumn2(72);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void creepspeedrateupdate(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(7);
  selectcolumn2(72); //64);
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void pmig_auto_man_update(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  selectcolumn2(64); //64);
   {
		k=':';
		data(&character[k][0],8);
		
		if(pmig_auto0_man1==0)
		{
		k='A';
		data(&character[k][0],8);
		k='U';
		data(&character[k][0],8);
		k='T';
		data(&character[k][0],8);
		k='O';
		data(&character[k][0],8);
		k=' ';
		data(&character[k][0],8);
		k=' ';
		data(&character[k][0],8);
		}
		else if(pmig_auto0_man1==1)
		{
		k='M';
		data(&character[k][0],8);
		k='A';
		data(&character[k][0],8);
		k='N';
		data(&character[k][0],8);
		k='U';
		data(&character[k][0],8);
		k='A';
		data(&character[k][0],8);
		k='L';
		data(&character[k][0],8);
		}
	}
}

void arcon_time_update(void)
{
  unsigned int k=0;
   
  ctrloff();
  selectpage(4);
  selectcolumn2(65); //64);
  
  
   {
		
		lcd_disp_hex_dec(arcontime.hr);  //@Hour Time
		
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
	
		k=disp_data_arr[2];
		data(&character[k][0],8);
		
		lcd_disp_hex_dec(arcontime.min);  //@Min Time
		
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
			
	}
}

void tigpreflowupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(2);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void startcurrentupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void upslopetimeupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(4);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void tigdownslopetimeupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(5);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}

void endcurrentupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(6);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		
		k=disp_data_arr[0];
		data(&character[k][0],8);
		
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


 

void tigpostflowtimeupdate(void) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(7);
  selectcolumn2(64);//64);//64); 9*6
   {
		k=':';
		data(&character[k][0],8);
		k=disp_data_arr[0];
		data(&character[k][0],8);
		k=disp_data_arr[1];
		data(&character[k][0],8);
		k='.';
		data(&character[k][0],8);
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}


void foot_1_normal_0_update(void)
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  selectcolumn2(64); //64);
   {
		k=':';
		data(&character[k][0],8);
		
		if(foot_1_normal_0==0)
		{
		k='N';
		data(&character[k][0],8);
		k='O';
		data(&character[k][0],8);
		k='R';
		data(&character[k][0],8);
		k='M';
		data(&character[k][0],8);
		k='A';
		data(&character[k][0],8);
		k='L';
		data(&character[k][0],8);
		}
		else if(foot_1_normal_0==1)
		{
		k='F';
		data(&character[k][0],8);
		k='O';
		data(&character[k][0],8);
		k='O';
		data(&character[k][0],8);
		k='T';
		data(&character[k][0],8);
		k=' ';
		data(&character[k][0],8);
		k=' ';
		data(&character[k][0],8);
		}
	}
}

void update_digit(unsigned char col_position) //@versa
{
  unsigned int k=0;
  ctrloff();
  selectpage(3);
  
  if(col_position<64)
  selectcolumn1(col_position);//64);//64); 9*6
   else
   selectcolumn2(col_position);//64);//64); 9*6
	   
	{
		k=disp_data_arr[1];
		data(&character[k][0],8);
		
		k=disp_data_arr[2];
		data(&character[k][0],8);
	}
}