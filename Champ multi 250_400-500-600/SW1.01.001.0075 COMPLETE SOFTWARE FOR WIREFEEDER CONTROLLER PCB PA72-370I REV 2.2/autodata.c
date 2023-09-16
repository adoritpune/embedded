const unsigned int mmmatgas[4][4][4]=					//for selection of wire dia., material, gas.
									{
										{
											{1,2,3,4},
											{5,6,7,8},
											{9,10,11,12},
											{13,14,15,16}
										},
										{
											{17,18,19,20},
											{21,22,23,24},
											{25,26,27,28},
											{29,30,31,32}
										},
										{
											{33,34,35,36},
											{37,38,39,40},
											{41,42,43,44},
											{45,46,47,48}
										},
										{
											{49,50,51,52},
											{53,54,55,56},
											{57,58,59,60},
											{61,62,63,64}
										}
									};
 unsigned int autopwm[65][20]=						//for selection of motor speed w.r.t. welding voltage and ocv also
									{					//operating voltage is between 14-33 volt (span==20)
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//dummy
									  // 14  15	 16	 17	 18	 19	 20	 21  22  23  24  25  26  27  28  29  30  31  32  33				           //output voltages
										{90,90,150,205,240,270,295,363,415,440,460,480,500,510,520,540,540,540,540,540},			     //1 0.8 FE ARCo2 
										{90,90,90,91,154,175,198,253,288,388,489,540,540,540,540,540,540,540,540,540},				//2 0.8 FE Co2	 	
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//3 0.8 FE AR
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//4 0.8 FE ARo2

										{117,126,159,204,255,306,372,387,414,435,462,474,480,486,492,504,516,528,540,540},	    	     //5 0.8 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//6 0.8 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//7 0.8 SS Ar
										{100,117,143,174,240,320,364,390,415,460,500,540,540,540,540,540,540,540,540,540},			//8 0.8 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//9  0.8 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//10 0.8 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//11 0.8 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//12 0.8 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//13 0.8     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//14 0.8     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//15 0.8     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//16 0.8     Aro2
									
										//*********************************************************************************************************************************************
										{85,95,101,137,189,195,220,280,330,390,452,500,540,540,540,540,540,540,540,540},		     //17 1.0 FE ARCo2
										{60,70,74,85,100,120,140,180,200,240,270,320,360,420,460,480,500,520,540,540},			     //18 1.0 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//19 1.0 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//20 1.0 FE Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//21 1.0 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//22 1.0 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//23 1.0 SS Ar
										//{90,100,114,140,155,234,255,290,323,345,447,464,470,490,520,540,540,540,540,540},			//24 1.0 SS ARO2
										{90,100,114,140,155,234,255,290,323,345,447,464,470,490,520,540,540,540,540,540},			//24 1.0 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//25 1.0 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//26 1.0 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//27 1.0 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//28 1.0 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//29 1.0     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//30 1.0     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//31 1.0     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//32 1.0     Aro2
									
										//*********************************************************************************************************************************************
										{90,96,120,142,150,183,196,220,224,266,390,420,470,500,520,540,540,540,540,540},			//33 1.2 FE ARCo2
										{60,65,68,70,71,96,109,114,128,148,188,228,254,282,356,384,428,450,480,480},			    //34 1.2 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//35 1.2 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//36 1.2 FE Aro2
										//87,93,95,115
										{90,100,110,120,145,200,240,270,350,390,410,430,460,490,500,510,520,530,540,540},			//37 1.2 SS ARCo2 
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//38 1.2 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//39 1.2 SS Ar
									    {100,104,106,136,179,180,186,189,192,193,195,216,243,333,360,375,396,444,480,540},			//40 1.2 SS ARO2 
										//{100,104,106,136,179,216,222,246,300,336,389,432,462,464,465,480,500,520,540,540},		//40 1.2 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//41 1.2 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//42 1.2 ALu Co2
									  //{214,230,247,264,292,335,353,378,388,397,418,434,450,470,480,490,500,510,520,540},			//43 1.2 ALu Ar
										{214,230,247,264,292,335,336,337,338,339,339,354,363,396,402,405,432,438,444,460},			//43 1.2 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//44 1.2 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//45 1.2     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//46 1.2     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//47 1.2     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//48 1.2     Aro2
																			
										//*********************************************************************************************************************************************
										{102,112,119,123,126,128,158,194,208,219,236,266,286,300,320,330,340,360,370,380},			//49 1.6 FE ARCo2
										{90,90,90,90,90,90,90,95,111,125,147,148,182,195,208,210,215,218,220,230},		        		//50 1.6 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//51 1.6 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//52 1.6 FE Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//53 1.6 SS ARCo2 COFMOW
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//54 1.6 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//55 1.6 SS Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//56 1.6 SS ARO2  COFMOW

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//57 1.6 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//58 1.6 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//59 1.6 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//60 1.6 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//61 1.6     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//62 1.6     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//63 1.6     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//64 1.6     Aro2
									};

const unsigned int autocurrent[65][27]=			//[20]for selection of current w.r.t wirespeed(0.0 t0 19.0)  add 20,21,22,23,
									{			
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//dummy
									  // 00	 01	02	03	04	05	06	07	08	09	10	11	12	13	14	15	16	17	18	19					//wirespeed
									 //	{000,030,045,065,80,92,100,110,120,140,150,160,170,180,195,220,230,240,250,255,260,270,275,280,285,290},	          		//1 0.8 FE ARCo2 
										{000,030,045,065,80,92,100,110,120,140,150,160,170,180,195,200,210,220,225,230,235,240,245,250,255,260,270},	          		//1 0.8 FE ARCo2 
										{000,012,030,046,58,70,85,94,102,108,116,128,136,144,154,162,170,176,180,200,205,210,215,220,225,230,240},      			//2 0.8 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//3 0.8 FE AR
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//4 0.8 FE ARo2

										{000,000,030,040,065,075,85,95,110,125,140,150,160,170,180,190,220,230,240,250,255,260,265,270,275,282,290},		     		//5 0.8 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//6 0.8 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//7 0.8 SS Ar
										{000,000,020,030,050,070,85,95,110,115,125,135,150,160,170,175,190,205,220,240,230,240,250,260,270,280,290},		      	//8 0.8 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//9  0.8 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//10 0.8 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//11 0.8 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//12 0.8 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//13 0.8     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//14 0.8     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//15 0.8     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//16 0.8     Aro2
									
										//*********************************************************************************************************************************************
										{000,000,050,060,95,115,130,160,170,178,190,210,225,240,250,255,265,280,285,300,315,325,335,340,345,350,360},		     	//17 1.0 FE ARCo2
										{000,010,030,050,070,88,115,140,156,172,185,195,200,210,220,230,235,240,250,260,270,275,280,290,300,310,320},                //18 1.0 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//19 1.0 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//20 1.0 FE Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//21 1.0 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//22 1.0 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//23 1.0 SS Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//24 1.0 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//25 1.0 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//26 1.0 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//27 1.0 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//28 1.0 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//29 1.0     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//30 1.0     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//31 1.0     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//32 1.0     Aro2
									
										//*********************************************************************************************************************************************
										{000,050,070,100,140,160,190,210,220,230,240,245,255,270,285,310,340,370,390,400,410,420,430,440,450,460,470},	     		//33 1.2 FE ARCo2
										{000,026,58,88,118,150,168,190,210,230,250,264,272,282,292,298,304,312,320,330,330,340,350,360,370,380,390},			 	//34 1.2 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//35 1.2 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//36 1.2 FE Aro2
										
									  //{000,040,060,100,140,155,170,200,220,230,235,245,260,290,315,335,380,400,410,420,430,440,450,460,470,480,490},			//37 1.2 SS ARCo2
										{000,040,050,80,105,130,155,175,200,220,235,255,260,275,290,310,320,340,360,380,390,400,410,420,430,440,450},			//37 1.2 SS ARCo2 COFMOW
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//38 1.2 SS Co2
										//{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//39 1.2 SS Ar
										{000,040,050,120,155,180,205,225,250,270,295,315,330,345,370,390,400,420,440,460,480,490,500,510,520,530,540},     		//39 1.2 SS ArO2 ----For Champ multi 250  on place of 1.2 SS ar	
									  //{000,040,050,120,155,180,205,225,250,270,295,315,330,345,370,390,400,420,440,460,480,490,500,510,520,530,540},     		//40 1.2 SS ARO2
										{000,040,050,80,105,130,155,175,200,220,235,255,260,275,290,310,320,340,360,380,390,400,410,420,430,440,450},     		//40 1.2 SS ARO2 COFMOW

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//41 1.2 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//42 1.2 ALu Co2
										{000,000,000,030,040,050,065,100,135,180,205,215,260,275,290,310,320,330,340,350,360,370,380,390,400,410,420},		      //43 1.2 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//44 1.2 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//45 1.2     ARCo2
										{000,030,050,075,100,130,150,170,190,220,230,240,245,260,270,285,290,300,310,320,330,340,350,360,370,380,390},			//46 1.2  FCAW welding  Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//47 1.2     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//48 1.2     Aro2
																			
										//*********************************************************************************************************************************************
										{000,015,100,155,205,240,290,322,350,370,390,400,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560},	    	    	//49 1.6 FE ARCo2
										{000,015,80,146,195,245,270,306,340,360,370,378,388,400,420,430,440,450,460,470,470,480,490,500,510,520,530},		      //50 1.6 FE Co2
                                        {000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//51 1.6 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//52 1.6 FE Aro2
										
										{000,015,100,135,190,210,220,250,300,320,350,370,390,400,410,420,430,440,450,460,470,480,490,500,510,530,540},			//53 1.6 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//54 1.6 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//55 1.6 SS Ar
										{000,015,100,135,190,210,220,250,300,320,350,370,390,400,410,420,430,440,450,460,470,480,490,500,510,530,540},			//56 1.6 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//57 1.6 Alu ARCo2
										{000,160,210,260,320,355,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400},			//58 1.6 ALu Co2 FCAW 24V 40 RPM/min MOTOR
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//59 1.6 ALu Ar
										{000,120,180,230,290,340,385,400,410,420,430,450,460,400,400,400,400,400,400,400,400,400,400,400,400,400,400},			//60 1.6 ALu Aro2 FCAW 42V 90 RPM/MIN MOTOR
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//61 1.6     ARCo2
										{000,025,055,100,140,180,220,250,280,310,340,360,380,420,450,470,480,510,520,530,550,560,570,580,590,600,600},			//62 1.6  FCAW welding     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//63 1.6     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//64 1.6     Aro2
									};


unsigned int findmatindex(unsigned int wvtg)
{
	unsigned char temp,temp1=0,temp2=0,temp3=0;
	unsigned char mm=0,mat=0,gas=0;
	unsigned int ans=0;
	temp1=(TypeU.LEDGROUP[2] & 0x0F);
	temp=(TypeU.LEDGROUP[2] >> 4);
	temp2=(temp & 0x0F);
	temp3=(TypeU.LEDGROUP[3] & 0x0F);
	mm=findvalue(temp1);
	mat=findvalue(temp2);
	gas=findvalue(temp3);
	ans=mmmatgas[mm][mat][gas];
	//transmit_dec(ans);
	ans=autopwm[ans][(wvtg - 14)];//16
	return(ans);
	//transmit_dec(ans);
}	
unsigned char findvalue(unsigned char num)
{
	unsigned char ans=0;
	if(num==0X0E)
	{
		ans=0;
	}
	else if(num==0X0D)
	{
		ans=1;
	}
	else if(num==0X0B)
	{
		ans=2;
	}
	else if(num==0X07)
	{
		ans=3;
	}
	return(ans);	
}


unsigned int findmatindex1(unsigned int wirespeed)
{
	unsigned char temp,temp1=0,temp2=0,temp3=0;
	unsigned char mm=0,mat=0,gas=0;
	unsigned int ans=0;
	temp1=(TypeU.LEDGROUP[2] & 0x0F);
	temp=(TypeU.LEDGROUP[2] >> 4);
	temp2=(temp & 0x0F);
	temp3=(TypeU.LEDGROUP[3] & 0x0F);
	mm=findvalue(temp1);
	mat=findvalue(temp2);
	gas=findvalue(temp3);
	if(WeldMode==0x03)
		ans=mmmatgas[mm][mat][gas];
	else if(WeldMode==0x04)
	{
		ans=mmmatgas[mm][mat][gas];
		ans=ans+12;
	}
	//transmit_dec(ans);
	ans=autocurrent[ans][wirespeed];//16
	return(ans);
	//transmit_dec(ans);
}	

const unsigned int autovoltage[65][27]=			// [20] for selection of voltage w.r.t wirespeed(0.0 t0 19.0) 
									{			
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//dummy
									   // 00	 01	02	03	04	05	06	07	08	09	10	11	12	13	14	15	16	17	18	19					//wirespeed
									 	{0,140,145,150,160,165,170,180,185,190,200,205,215,220,230,245,260,280,300,320,330,335,338,340,343,348,352},	   	    		//1 0.8 FE ARCo2 
										{0,155,160,167,175,181,190,198,207,216,226,233,236,238,242,244,248,251,260,280,290,300,310,320,330,340,345},   			//2 0.8 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//3 0.8 FE AR
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//4 0.8 FE ARo2

										{0,150,155,160,165,170,180,185,190,195,200,210,215,220,230,250,260,280,300,320,325,330,335,340,345,350,355},		    		//5 0.8 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//6 0.8 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//7 0.8 SS Ar
										{0,140,145,150,160,165,175,180,190,195,205,210,220,225,235,240,250,255,260,270,280,290,300,310,320,330,340},		    		//8 0.8 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//9  0.8 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//10 0.8 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//11 0.8 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//12 0.8 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//13 0.8     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//14 0.8     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//15 0.8     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//16 0.8     Aro2
									
										//*********************************************************************************************************************************************
										{0,155,160,170,175,180,190,195,205,210,220,225,230,235,245,250,260,265,270,280,285,290,300,310,320,330,340},            		//17 1.0 FE ARCo2
										{0,140,170,181,190,200,208,218,228,235,238,242,246,250,254,260,266,268,271,285,295,305,320,340,350,360,370},            		//18 1.0 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//19 1.0 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//20 1.0 FE Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//21 1.0 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//22 1.0 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//23 1.0 SS Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//24 1.0 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//25 1.0 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//26 1.0 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//27 1.0 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//28 1.0 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//29 1.0     ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//30 1.0     Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//31 1.0     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//32 1.0     Aro2
									
										//*********************************************************************************************************************************************
										{0,120,140,160,180,195,205,220,225,230,240,250,255,260,265,270,275,280,290,310,320,330,335,340,345,350,360},	     			//33 1.2 FE ARCo2
										{0,150,166,184,198,212,224,236,244,256,266,274,280,284,290,296,300,308,316,320,330,335,338,340,345,350,360},		    		//34 1.2 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//35 1.2 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//36 1.2 FE Aro2
										
										//{0,150,160,170,180,185,190,200,210,220,230,240,250,260,270,290,300,320,340,350,360,370,380,390,400,410,420},		    	//37 1.2 SS ARCo2
										{0,95,120,150,170,190,210,220,230,240,250,260,270,275,280,290,295,300,310,320,330,340,350,360,370,380,390},		    //37 1.2 SS ARCo2 COFMOW
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//38 1.2 SS Co2
										//{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//39 1.2 SS Ar
										{0,125,150,180,200,220,240,250,260,270,280,290,300,305,310,320,325,330,340,350,360,370,380,390,400,410,420},     			//39 1.2 SS ARO2
									  //{0,125,150,180,200,220,240,250,260,270,280,290,300,305,310,320,325,330,340,350,360,370,380,390,400,410,420},     			//40 1.2 SS ARO2
                                        {0,95,120,150,170,190,210,220,230,240,250,260,270,275,280,290,295,300,310,320,330,340,350,360,370,380,390},     			//40 1.2 SS ARO2 COFMOW
                                        
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//41 1.2 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//42 1.2 ALu Co2
										{0,80,90,105,130,150,185,210,230,250,260,270,280,300,320,340,350,360,370,380,390,400,410,420,430,440,440},		        	//43 1.2 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//44 1.2 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//45 1.2     ARCo2
										{000,205,218,220,226,232,238,242,250,252,258,262,270,275,280,284,290,298,302,310,320,330,340,350,360,370,380},			//46 1.2  FCAW welding     Co2		
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//47 1.2     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//48 1.2     Aro2
																			
										//*********************************************************************************************************************************************
										{0,160,174,196,219,240,260,278,290,304,314,322,330,336,342,350,360,370,380,390,400,410,420,430,440,440,440},	    			//49 1.6 FE ARCo2
										{0,160,202,215,242,258,275,290,296,306,315,324,334,344,350,360,370,380,390,400,410,420,430,440,440,440,440},		    		//50 1.6 FE Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//51 1.6 FE Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//52 1.6 FE Aro2
										
										{0,150,164,176,190,200,220,240,250,270,280,290,300,320,332,340,350,360,370,390,400,410,420,430,440,440,440},			//53 1.6 SS ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//54 1.6 SS Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//55 1.6 SS Ar
										{0,150,164,176,190,200,220,240,250,270,280,290,300,320,332,340,350,360,370,390,400,410,420,430,440,440,440},			//56 1.6 SS ARO2

										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//57 1.6 Alu ARCo2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//58 1.6 ALu Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//59 1.6 ALu Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//60 1.6 ALu Aro2
										
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//61 1.6     ARCo2
										{000,210,221,230,239,250,258,265,275,288,295,306,314,322,334,342,352,362,370,390,400,410,420,430,440,440,440},			//62 1.6  FCAW welding  Co2
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//63 1.6     Ar
										{000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000},			//64 1.6     Aro2
									};


unsigned int findmatindex2(unsigned int wirespeed)
{
	unsigned char temp,temp1=0,temp2=0,temp3=0;
	unsigned char mm=0,mat=0,gas=0;
	unsigned int ans=0;
	temp1=(TypeU.LEDGROUP[2] & 0x0F);
	temp=(TypeU.LEDGROUP[2] >> 4);
	temp2=(temp & 0x0F);
	temp3=(TypeU.LEDGROUP[3] & 0x0F);
	mm=findvalue(temp1);
	mat=findvalue(temp2);
	gas=findvalue(temp3);
	//ans=mmmatgas[mm][mat][gas];
	if(WeldMode==0x03)
		ans=mmmatgas[mm][mat][gas];
	else if(WeldMode==0x04)
	{
		ans=mmmatgas[mm][mat][gas];
		ans=ans+12;
	}
	//transmit_dec(ans);
	ans=autovoltage[ans][wirespeed];//16
	return(ans);
	//transmit_dec(ans);
}	

unsigned int findmatindex3(unsigned int wirespeed)
{
	//unsigned char temp,temp1=0,temp2=0,temp3=0;
	//unsigned char mm=0,mat=0,gas=0;
	unsigned int ans=0;
	//temp1=(TypeU.LEDGROUP[2] & 0x0F);
	//temp=(TypeU.LEDGROUP[2] >> 4);
	//temp2=(temp & 0x0F);
	//temp3=(TypeU.LEDGROUP[3] & 0x0F);
	//mm=findvalue(temp1);
	//mat=findvalue(temp2);
	//gas=findvalue(temp3);
	//ans=mmmatgas[mm][mat][gas];
	ans=60;				//fcw is data is stored at that location
	//transmit_dec(ans);
	ans=autocurrent[ans][wirespeed];//16
	return(ans);
	//transmit_dec(ans);
}	

unsigned int findmatindex4(unsigned int wirespeed)
{
	unsigned int ans=0;
	ans=autodatarow;//58;				//fcaw 24V data is data is stored at that location
	ans=autocurrent[ans][wirespeed];//16
	return(ans);
}	
unsigned int CalCurrAsPerWirespeed(unsigned int iWireSpeed)
{
	return(456);
}
unsigned int CalVoltAsPerWirespeed(unsigned int iWireSpeed )
{
	return(123);
}
const unsigned int iWFMulFactorArr[0][26] =
								{	
							//		 00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26				
									{40,40,40,30,26,25,24,23,21,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,1}
								};
								
								
unsigned int WFmotorCal(unsigned int iWireSpeed)
{
	if(iWireSpeed <= 20)
	{
		return(30);//iWFMulFactorArr [0][iWireSpeed]);	
	}
	else
	{
		
		return(30);//iWFMulFactorArr [0][22]);	
	}
}								
								
								
								
