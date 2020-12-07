void FFTlcd(void);
void FFTbotones(void);
int angulo360(double);

void FFT(){  
  FFTlcd();
  bana=1;
    while(bana==1) 
    {
      FFTbotones();

    
      N=250;
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
   
    i=0;
   while (i != N+1){
    xn[i]= ((xn[i]*33)/4095);
    i=i+1;
    }
    
    //****************Calculo de los Xkr y Xki coeficientes 
     Ck=60;
     k=0;
      while(k != Ck){
        i=0;
        Wxk=((360*k)/(N));
        angWxk=angulo360(Wxk);
        cosewxk= tabcoseno[angWxk];
        senowxk= tabseno[angWxk];
        auXkr=0;
        auXki=0;
        Wxk=((360*k)/(N/2));
       while(i != (N/2)){
        angulox=angulo360(Wxk*i);
        coseno = tabcoseno[angulox];
        seno = tabseno[angulox];
        auXkr=((((xn[2*i])*coseno)+(((xn[(2*i)+1])*coseno*cosewxk)/1000))/1000)+auXkr;
        auXki=((((xn[2*i])*seno)+(((xn[(2*i)+1])*seno*senowxk)/1000))/1000)+auXki;
        i=i+1;
       } 
       Xkr[k]=abs(auXkr);
       Xki[k]=abs(auXki);
      // Serial.println(Xkr[k]);
       k=k+1;
      }

      //---------grafica la funcion en el display
      i=1;
      f=0;
      while(f != Ck){
        if(Xkr[f]>(240*10)){
          Xkr[f]=(240*10);
        }
        sallcd[f]=240+18-(Xkr[f]/10);
        
          myGLCD.setColor(0, 0, 0);       //color negro
          myGLCD.drawLine(i, 16, i, 238); //borra sobre esa linea para luego graficar
          myGLCD.drawLine(i+1, 16, i+1, 238); //borra sobre esa linea para luego graficar
          myGLCD.drawLine(i+2, 16, i+2, 238); //borra sobre esa linea para luego graficar
          myGLCD.drawLine(i+3, 16, i+3, 238); //borra sobre esa linea para luego graficar
       
          myGLCD.setColor(0, 255, 255);
          myGLCD.drawLine(i, 238, i, sallcd[f]); //dibuja en la pantalla
          myGLCD.drawLine(i+1, 238, i+1, sallcd[f]); //dibuja en la pantalla
          myGLCD.drawLine(i+2, 238, i+2, sallcd[f]); //dibuja en la pantalla
          //myGLCD.drawLine(i+3, 238, i+3, sallcd[f]); //dibuja en la pantalla
          //delayMicroseconds(Pers);
        i=i+4;
        f=f+1;
        }
  } 

}


//************botones
void FFTbotones(){
      if (myTouch.dataAvailable() == true)
      {
        pressed_button = myButtons.checkButtons();
        
        if (pressed_button==but1){
          //myGLCD.print("Button 1", 110, 180);
          delay(100);
          bana=0;
          //myGLCD.clrScr(); //borra pantalla
       }
       else if (pressed_button==-1){
          myGLCD.print("None    ", 110, 180);
         }    
      }
    }     
     
//*************************grafica de pantalla
void FFTlcd(){
 myGLCD.clrScr(); //borra pantalla 
 myButtons.deleteAllButtons();
 myGLCD.setFont(SmallFont); //configura letra
 myGLCD.setColor(255,0, 0); //establece el color r,g,b en el rectangulo
 myGLCD.fillRect(0, 0, 319, 13); //dibuja un rectangulo
 myGLCD.setColor(64, 64, 64);  //establece color 
 //myGLCD.setColor(255, 255, 255); //establece color de fondo
 myGLCD.setBackColor(255, 0, 0); //establece color de fondo
 myGLCD.print("FFT", CENTER, 0);//imprime texto en el centro 
 myGLCD.setColor(0, 0, 255);
 myGLCD.drawRect(0, 14, 319, 240); //dibuja rectangulo de la pantalla
 myGLCD.drawRect(251, 14, 319, 240); //dibuja rectangulo de menu de la pantalla

 myGLCD.setColor(0, 255, 255);
 myGLCD.setBackColor(0, 0, 0);
 //myGLCD.drawLine(119, 15, 119, 238); //dibuja linea del medio vertical
// myGLCD.drawLine(1, 119, 250, 119); //dibuja linea del medio horizontal 

  myButtons.setButtonColors(VGA_LIME, VGA_MAROON, VGA_LIME, VGA_YELLOW, VGA_TEAL);
 but1 = myButtons.addButton(255,213, 30,  25, "S");
 //but2 = myButtons.addButton(255,185, 30,  25, "+F");
// but3 = myButtons.addButton(255,155, 30,  25, "-F"); 
// but4 = myButtons.addButton(255,125, 30,  25, "+V");
 //but5 = myButtons.addButton(255,95, 30,  25, "-V"); 
 //but6 = myButtons.addButton(255,65, 30,  25, "+L");
// but7 = myButtons.addButton(255,35, 30,  25, "-L"); 
 
  myButtons.drawButtons(); 
}
