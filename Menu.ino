
void menulcd(void);

void Menu(){
  menulcd();
  
  ban=1;
  while(ban==1) 
  {
    if (myTouch.dataAvailable() == true)
    {
      pressed_button = myButtons.checkButtons();
      
      if (pressed_button==but1){
        //myGLCD.print("Button 1", 110, 180);
        delay(100);
        Muestreo();
        menulcd();
        //ban=0;
        //myGLCD.clrScr(); //borra pantalla
     }
     else if (pressed_button==but2){
        delay(100);
        FIR();
        menulcd();
        //ban=0;
        //myGLCD.clrScr(); //borra pantalla
     }
     else if (pressed_button==but3){
        delay(100);
        FFT();
        menulcd();
        //ban=0;
        //myGLCD.clrScr(); //borra pantalla
     }
     else if (pressed_button==-1){
        myGLCD.print("None    ", 110, 180);
       }    
    }
  }
}


void menulcd(){
 myGLCD.clrScr(); //borra pantalla  
 myButtons.deleteAllButtons(); 
 myGLCD.setFont(SmallFont); //configura letra
  myGLCD.setColor(255,0, 0); //establece el color r,g,b en el rectangulo
  myGLCD.fillRect(0, 0, 319, 13); //dibuja un rectangulo
  myGLCD.setColor(64, 64, 64);  //establece color 
 //myGLCD.setColor(255, 255, 255); //establece color de fondo
 myGLCD.setBackColor(255, 0, 0); //establece color de fondo
 myGLCD.print("Menu", CENTER, 0);//imprime texto en el centro 
 myGLCD.setColor(0, 0, 255);
 myGLCD.drawRect(0, 14, 319, 240); //dibuja rectangulo de la pantalla

 myButtons.setButtonColors(VGA_LIME, VGA_MAROON, VGA_LIME, VGA_YELLOW, VGA_TEAL);
 but1 = myButtons.addButton(50,30, 130,  50, "Muestreo");
 but2 = myButtons.addButton(50,100, 130,  50, "Filtro");
 but3 = myButtons.addButton(50,160, 130,  50, "FFT");
  myButtons.drawButtons(); 
}
