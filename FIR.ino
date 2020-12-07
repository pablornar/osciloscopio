void FIRlcd(void);
void FIRbotones(void);
int angulo360(double);
//hola
void FIR(){  
  FIRlcd();
  bana=1;
    while(bana==1) 
    {
      FIRbotones();

    //***implementacion de filtro
    Tretint=((Fclock/2)*Tm);
    Fs=(1000000/Tm);  //hz  Khz
    Wpi=(360*fpi)/Fs;
    Wpf=(360*fpf)/Fs;
    Wc=(360*fc)/Fs;
    AW=Wpi-Wc;       //ventana de transicion del mi filtro
    n=((8*180)/AW);  //cantidad de coeficientes a tomar
    //falta funcion para ver si n es par o impar
    L=(n/2);
    
    //************implementa el filtro fir pasabanda y pasabajos
      k=0;
      while(k < (n)){
        if (k > (n/2)){
          angulo=k-L;
          angulo=(angulo*Wc)/180;
            angsinc=angulo360(angulo);
            sinc = tabsinc[angsinc];   
        }
        else if(k == (n/2)){
          angulo=k-L;
          angulo=angulo360(angulo);
          sinc = tabsinc[angulo];
         }
        else if(k < (n/2)){
          angulo=L-k;
          angulo=(angulo*Wc)/180;
          angsinc=angulo360(angulo);
          sinc = tabsinc[angsinc];   
        }

        auhd1=(Wc/180)*sinc;
        angvent=360*k;
        angvent=angvent/(n-1);
        angvent=angulo360(angvent);
        coseno = tabcoseno[angvent];
        auhd2=(coseno*0.46)/1000;
        auhd2=(0.54-auhd2);         // w[n]
        hd[k]=(auhd1*auhd2)/(1);      //4.6 h[n] del filtro pasabanda
        
        k=k+1;
      }
    
    
      N=n+250;
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

     //----------Calculo del piso de ruido (conectar una carga fantasma( o de calibracion) a la entrada- conectamos a masa la entra A)
      i=0;
      auxnf=0;
      while(i != N){
        auxnf=(xn[i]*xn[i])+auxnf;
        i=i+1;
      }
      PRuido=sqrt(auxnf/N);     //piso de ruido

     
     //+++++++++++calculo de la senal filtada pasabanda xnf[] 
      k=0;
      r=0;
      auxnf=0;
      while(r < N+1){
        while(k < (n)){
          xnfd[r]=(hd[k])*(xn[((N+n)-r)-k]);
          auxnf= ((xnfd[r])/1)+ auxnf;
          k=k+1;
        }
        
        xnf[r]=(abs(auxnf));  //5.2
        if ((xnf[r]) > 4095){    //800
          xnf[r]=4095;
        }
        
        auxnf=0;
        k=0;
        r=r+1;
      }
       

    //------------Calculo SNR------
    i=0;
      auxnf=0;
      SNR=0;
      while(i != N){
        auxnf=((xnf[i])-(xn[i])*(xnf[i])-(xn[i]))+auxnf;
        SNR=(xn[i]*xn[i])+SNR;
        i=i+1;
      }
      SNR=SNR/auxnf;
      
      SNRT=SNR-PRuido;
      
    //----------conversion a lcd
      i=0;
      while(i != 250){
        sallcd[i]=((xnf[i]*240)/4095);
        i=i+1; 
      }

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



//********calcula el angulo de 0 a 360
int angulo360(double ang){
  int n;
  int bandang;
  n=1;
  bandang=1;
  while (bandang==1){
    if(ang > ((360*n))){
      n=n+1;
    }
    else if(ang <= 360){
      bandang=0;
    }
    else{
      ang=ang-((360*(n-1)));
      bandang=0;
    }
  }
  return ang;
}

//************botones
void FIRbotones(){
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
void FIRlcd(){
 myGLCD.clrScr(); //borra pantalla 
 myButtons.deleteAllButtons();
 myGLCD.setFont(SmallFont); //configura letra
 myGLCD.setColor(255,0, 0); //establece el color r,g,b en el rectangulo
 myGLCD.fillRect(0, 0, 319, 13); //dibuja un rectangulo
 myGLCD.setColor(64, 64, 64);  //establece color 
 //myGLCD.setColor(255, 255, 255); //establece color de fondo
 myGLCD.setBackColor(255, 0, 0); //establece color de fondo
 myGLCD.print("FIR", CENTER, 0);//imprime texto en el centro 
 myGLCD.setColor(0, 0, 255);
 myGLCD.drawRect(0, 14, 319, 240); //dibuja rectangulo de la pantalla
 myGLCD.drawRect(251, 14, 319, 240); //dibuja rectangulo de menu de la pantalla

 myGLCD.setColor(0, 255, 255);
 myGLCD.setBackColor(0, 0, 0);
 myGLCD.drawLine(119, 15, 119, 238); //dibuja linea del medio vertical
 myGLCD.drawLine(1, 119, 250, 119); //dibuja linea del medio horizontal 

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
