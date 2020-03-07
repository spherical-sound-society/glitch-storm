
/*
switch (state) {
      case 1: 
         value = ((t&((t>>a)))+(t|((t>>b))))&(t>>(a+1))|(t>>a)&(t*(t>>b));  
         aTop = 10;
         aBottom =0;
         bTop = 14;
         bBottom = 0;
         break;
      case 2: 
         value =(t*(t>>(a/10)|t>>(b/10)))>>(t>>((b/10)*2)); 
         aTop = 10;
         aBottom =0;
         bTop = 16;
         bBottom = 0;
         break;
      case 3:
        value = t*(((t>>(a*3))|(t>>(10+a)))&(b&(t>>(a*2))));   
         aTop = 6;
         aBottom =0;
         bTop = 50;
         bBottom = 0;
        break;
      case 4:
        value = t*(((t>>a)&(t>>8))&((b+73)&(t>>3)));  
         aTop = 22;
         aBottom =0;
         bTop = 99;
         bBottom = 0;
         break;
      case 5:
        value = t*(((t>>a)|(t>>(b*2)))&(63&(t>>b)));   
         aTop = 24;
         aBottom = 0;
         bTop = 8;
         bBottom = 0;
         break;
      case 6:
        value = ((t>>a&t)-(t>>a)+(t>>a&t))+(t*((t>>b)&b)); 
         aTop = 10;
         aBottom = 0;
         bTop = 28;
         bBottom = 0;
         break;
      case 7:
        value = ((t%42)*(t>>a)|(0x577338)-(t>>a))/(t>>b)^(t|(t>>a));  
         aTop = 8;
         aBottom = 0;
         bTop = 32;
         bBottom = 0;
         break;
      case 8:
         value = (t>>a|t|t>>(t>>16))*b+((t>>(b+1))&(a+1));   
         aTop = 12;
         aBottom = 0;
         bTop = 20;
         bBottom = 0;
         break;
      case 9:
         value = ((t*(t>>a|t>>(a+1))&b&t>>8))^(t&t>>13|t>>6);   
         aTop = 16;
         aBottom = 0;
         bTop = 86;
         bBottom = 0;
         break;
      case 10:
         value = ((t>>32)*7|(t>>a)*8|(t>>b)*7)&(t>>7);   
         aTop = 8;
         aBottom = 0;
         bTop = 22;
         bBottom = 0;
         break; 

    }

*/
