lcd_saverecall_ptr=1  //Escape
lcd_saverecall_ptr=2 //save
lcd_saverecall_ptr=3 //recall

lcdmigpointer=1 //preflow
lcdmigpointer=2  //burnback
lcdmigpointer=3 //postflow


lcdpage=1;   //escape save recall page 
lcdpage=2;  

setlcdweldparameter==1

lcdscan_flag //for blinking selection

In 
lcdpage==1
lcd_saverecall_ptr will ++ or --

In
lcdpage==2
lcdmigpointer will ++ or --

In 
lcdpage==3  // second page of parameter