void muestreolcd(void);

void Muestreo(){  
  muestreolcd();

  bana=1;
  while(bana==1) 
  {
    if (myTouch.dataAvailable() == true)
    {
      pressed_button = myButtons.checkButtons();
      
      if (pressed_button==but1){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        bana=0;
        //myGLCD.clrScr(); //borra pantalla
     }
      else if (pressed_button==but2){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        if(Tm > 0){  //tope fs=1Mhz
         Tm=Tm-1;  
        }
        Tretint=((Fclock/2)*Tm);
         Fs=(1000000/Tm);  //hz  Khz
        myGLCD.print("F=", 255, 20);
        myGLCD.printNumI(Fs,260,20,0);
        //myGLCD.clrScr(); //borra pantalla
     }
      else if (pressed_button==but3){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        Tm=Tm+1;
        if(Tm < 1000000){   //tope fs=1hz
         Tm=Tm-1;  
        }
        Tretint=((Fclock/2)*Tm);
        Fs=(1000000/Tm);  //hz  Khz
        myGLCD.print("F=", 255, 20);
        myGLCD.printNumI(Fs,260,20,0);
        
        //myGLCD.clrScr(); //borra pantalla
     }
     else if (pressed_button==but4){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        Gan=Gan+1;
        REG_ADC_COR = (REG_ADC_COR & 0b11111111011111111111111111111111) | 0b00000000000000000000000000000000; //registro cor
        if (Gan==2){ 
          REG_ADC_CGR = (REG_ADC_CGR & 0b11111111111111110011111111111111) | 0b00000000000000001000000000000000; //Ganancia 7 A0
        }
        else if (Gan>2){ 
          REG_ADC_CGR = (REG_ADC_CGR & 0b11111111111111110011111111111111) | 0b00000000000000001100000000000000; //Ganancia 7 A0
          Gan=3;
        }
        
        myGLCD.print("Gan=", 255, 20);
        myGLCD.printNumI(Gan,260,20,0);
     }
     else if (pressed_button==but5){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        Gan=Gan-1;
        REG_ADC_COR = (REG_ADC_COR & 0b11111111011111111111111111111111) | 0b00000000000000000000000000000000; //registro cor
        if (Gan<2){ 
          REG_ADC_CGR = (REG_ADC_CGR & 0b11111111111111110011111111111111) | 0b00000000000000000100000000000000; //Ganancia 7 A0
          Gan=1;
        }
        else if (Gan==2){ 
          REG_ADC_CGR = (REG_ADC_CGR & 0b11111111111111110011111111111111) | 0b00000000000000001000000000000000; //Ganancia 7 A0
        }
        myGLCD.print("Gan=", 255, 20);
        myGLCD.printNumI(Gan,260,20,0);
     }
     else if (pressed_button==but6){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        leveltriger=leveltriger+100;        
        if (leveltriger > 4095){
          leveltriger=4095;
        }
     }
     else if (pressed_button==but7){
        myGLCD.print("Button 1", 110, 180);
        delay(100);
        leveltriger=leveltriger-100;        
        if (leveltriger < 100){
          leveltriger=0;
        }
     }
     else if (pressed_button==-1){
        myGLCD.print("None    ", 110, 180);
       }    
    }



    //******Trigger-----------------
      i=0;
      while((REG_ADC_ISR & 0b00000000000000000000000010000000) == 0); // wait for conversion del canal 7
      xn[i]=(ADC->ADC_CDR[7]);
      i=1;
      bandtriger=0;
      while(bandtriger == 0){
        delayMicroseconds(Tm);      //periodo de muestreo minimo es 1useg 
        while((REG_ADC_ISR & 0b00000000000000000000000010000000) == 0); // wait for conversion del canal 7
        xn[i]=(ADC->ADC_CDR[7]);
        if ((xn[i]==leveltriger) && (xn[i-1]<leveltriger)){
          bandtriger=1;
        }
        i=i+1;
        if(i==250){
          i=1;                       
        }
      }


     //************funcion para la adquision de los datos  
    i=0;
    REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    
    while(bandint == 0){
      digitalWrite(13,HIGH);
    }
    digitalWrite(13,LOW);
    bandint=0;

    /*
    //----------muestreo
      i=0;
      while(i != 250){
        xn[i]=(ADC->ADC_CDR[7]);
        //xn=analogRead(A0);
        delayMicroseconds(Tm);      //periodo de muestreo minimo es 1useg 
        i=i+1;                      //fs=1Mhz.
        //Serial.println(xn);  
      }
   */

     //----------busqueda del maximo
      i=0;
      au=0;
      while(i != 250){
        if (xn[i]>au){
          au=xn[i];
        }
        i=i+1;                      
      }
      
    //----------conversion a lcd
      i=0;
      while(i != 250){
        sallcd[i]=((xn[i]*240)/4095);
        i=i+1; 
      }

     /*
      //-------promedion m muestras
        i=0;
        Nprom=250;
        sallcdprom[i]=0;
        while(i != 250){
         sallcdprom[i]=sallcd[i]+sallcdprom[i];
         i=i+1; 
        }    
        sallcd[i]=sallcdprom[i]/Nprom;
     */

      //---------grafica la funcion en el display
      for(i=1;i<250;i++){
          myGLCD.setColor(0, 0, 0);       //color negro
          myGLCD.drawLine(i, 16, i, 238); //borra sobre esa linea para luego graficar
          
          myGLCD.setColor(0, 255, 255);
          myGLCD.drawLine(119, 15, 119, 238); //dibuja linea del medio vertical
          myGLCD.drawLine(1, 119, 250, 119); //dibuja linea del medio horizontal
          myGLCD.setColor(0, 255, 255);
          myGLCD.drawLine(i, 240-sallcd[i-1], i, 240-sallcd[i]); //dibuja en la pantalla
          delayMicroseconds(Pers);
        }
  } 

}

void muestreolcd(){
 myGLCD.clrScr(); //borra pantalla 
 myButtons.deleteAllButtons();
 myGLCD.setFont(SmallFont); //configura letra
 myGLCD.setColor(255,0, 0); //establece el color r,g,b en el rectangulo
 myGLCD.fillRect(0, 0, 319, 13); //dibuja un rectangulo
 myGLCD.setColor(64, 64, 64);  //establece color 
 //myGLCD.setColor(255, 255, 255); //establece color de fondo
 myGLCD.setBackColor(255, 0, 0); //establece color de fondo
 myGLCD.print("Modulacion AM", CENTER, 0);//imprime texto en el centro 
 myGLCD.setColor(0, 0, 255);
 myGLCD.drawRect(0, 14, 319, 240); //dibuja rectangulo de la pantalla
 myGLCD.drawRect(251, 14, 319, 240); //dibuja rectangulo de menu de la pantalla

 myGLCD.setColor(0, 255, 255);
 myGLCD.setBackColor(0, 0, 0);
 myGLCD.drawLine(119, 15, 119, 238); //dibuja linea del medio vertical
 myGLCD.drawLine(1, 119, 250, 119); //dibuja linea del medio horizontal 

  myButtons.setButtonColors(VGA_LIME, VGA_MAROON, VGA_LIME, VGA_YELLOW, VGA_TEAL);
 but1 = myButtons.addButton(255,213, 30,  25, "S");
 but2 = myButtons.addButton(255,185, 30,  25, "+F");
 but3 = myButtons.addButton(255,155, 30,  25, "-F"); 
 but4 = myButtons.addButton(255,125, 30,  25, "+V");
 but5 = myButtons.addButton(255,95, 30,  25, "-V"); 
 but6 = myButtons.addButton(255,65, 30,  25, "+L");
 but7 = myButtons.addButton(255,35, 30,  25, "-L"); 
 
  myButtons.drawButtons(); 
}
