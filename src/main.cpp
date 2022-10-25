#include <Arduino.h>

// Only PWM pin for breath effects
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// RGB LED Gaussian Wave Breathing LED (https://github.com/makerportal/arduino-breathing-led)
float smoothness_pts = 500; // larger=slower change in brightness
float gamma = 0.14;         // affects the width of peak (more or less darkness)
float beta = 0.5;           // shifts the gaussian to be symmetric

// Strobe variables
int n = 30;

// Menu variables
char menu;           // Input Main Menu
char subMenuOption1; // Input SubMenu 1
char subMenuOption2; // Input SubMenu 2
char subMenuOption3; // Input SubMenu 3
bool subMenu1Flag = false;
bool subMenu2Flag = false;
bool subMenu3Flag = false;
bool runOnce = true;
bool menuState = true;
String STATIC = " Debe devolver y mantener el color marcado.";
String STROBE = " Efecto estroboscopio usando el color seleccionado.";
String BREATH = " Efecto respiracion usando los colores RGB.";

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void mainMenu()
{
  if (runOnce == true)
  {
    Serial.println("   Seleccione un efecto      ");
    Serial.println(" A) Estático: " + STATIC);
    Serial.println(" B) Estroboscópico: " + STROBE);
    Serial.println(" C) Respiración: " + BREATH);
    runOnce = false;
    menuState = true;
  }
}

void subMenu1()
{
  menuState = false;
  subMenu1Flag = true;
  Serial.println("                               Efecto Estático                                          ");
  Serial.println("1- Rojo  2- Naranja  3- Amarillo  4- Verde  5- Agua 6- Azul 7- Rosado 8- Blanco 9- Salir");
}

void subMenu2()
{
  menuState = false;
  subMenu2Flag = true;
  Serial.println("                             Efecto Estroboscópico                                      ");
  Serial.println("1- Rojo  2- Naranja  3- Amarillo  4- Verde  5- Agua 6- Azul 7- Rosado 8- Blanco 9- Salir");
}

void subMenu3()
{
  menuState = false;
  subMenu3Flag = true;
  Serial.println("         Efecto Respiración          ");
  Serial.println("1- Rojo  2- Verde  3- Azul   4- Salir");
}

void setColor(int R, int G, int B)
{
  analogWrite(redPin, R);
  analogWrite(greenPin, G);
  analogWrite(bluePin, B);
}

void ledOFF()
{
  setColor(0, 0, 0);
}

void breathRED()
{
  for (int ii = 0; ii < smoothness_pts; ii++)
  {
    float pwm_val = 255.0 * (exp(-(pow(((ii / smoothness_pts) - beta) / gamma, 2.0)) / 2.0));
    analogWrite(redPin, int(pwm_val));
    delay(5);
  }
}

void breathGREEN()
{
  for (int ii = 0; ii < smoothness_pts; ii++)
  {
    float pwm_val = 255.0 * (exp(-(pow(((ii / smoothness_pts) - beta) / gamma, 2.0)) / 2.0));
    analogWrite(greenPin, int(pwm_val));
    delay(5);
  }
}

void breathBLUE()
{
  for (int ii = 0; ii < smoothness_pts; ii++)
  {
    float pwm_val = 255.0 * (exp(-(pow(((ii / smoothness_pts) - beta) / gamma, 2.0)) / 2.0));
    analogWrite(bluePin, int(pwm_val));
    delay(5);
  }
}

void loop()
{
  mainMenu();
  while (Serial.available() == 0)
  {
  }
  if (menuState == true)
  {
    char menu = Serial.read();
    if (menu == 'a' || menu == 'A')
    {
      Serial.println("Estático:");
      subMenu1();
    }
    else if (menu == 'b' || menu == 'B')
    {
      Serial.println("Estroboscópico:");
      subMenu2();
    }
    else if (menu == 'c' || menu == 'C')
    {
      Serial.println("Respiración:");
      subMenu3();
    }
    else
    {
      Serial.println("Elegir una opción de la A a la C");
    }
  }
  if (menuState == false && subMenu1Flag)
  {
    subMenuOption1 = Serial.read();
    if (subMenuOption1 == '1')
    {
      Serial.println("Led Rojo");
      setColor(255, 0, 0);
    }
    else if (subMenuOption1 == '2')
    {
      Serial.println("Led Naranja");
      setColor(255, 136, 0);
    }
    else if (subMenuOption1 == '3')
    {
      Serial.println("Led Amarillo");
      setColor(255, 255, 0);
    }
    else if (subMenuOption1 == '4')
    {
      Serial.println("Led Verde");
      setColor(0, 255, 0);
    }
    else if (subMenuOption1 == '5')
    {
      Serial.println("Led Aqua");
      setColor(0, 255, 255);
    }
    else if (subMenuOption1 == '6')
    {
      Serial.println("Led azul");
      setColor(0, 0, 255);
    }
    else if (subMenuOption1 == '7')
    {
      Serial.println("Led Rosado");
      setColor(255, 20, 147);
    }
    else if (subMenuOption1 == '8')
    {
      Serial.println("Led Blanco");
      setColor(255, 255, 255);
    }
    else if (subMenuOption1 == '9')
    {
      Serial.println("Salir al Menu Prinicpal");
      menu = 'q';
      runOnce = true;
      subMenu1Flag = false;
      ledOFF();
      mainMenu();
    }
    else
    {
      Serial.println("Elegir una opcion del 1 al 9");
    }
  }

  if (menuState == false && subMenu2Flag)
  {
    subMenuOption2 = Serial.read();
    if (subMenuOption2 == '1')
    {
      Serial.println("Led Rojo Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(255, 0, 0); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '2')
    {
      Serial.println("Led Naranja Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(255, 136, 0); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '3')
    {
      Serial.println("Led Amarillo Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(255, 255, 0); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '4')
    {
      Serial.println("Led Verde Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(0, 255, 0); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '5')
    {
      Serial.println("Led Aqua Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(0, 255, 255); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '6')
    {
      Serial.println("Led Azul Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(0, 0, 255); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '7')
    {
      Serial.println("Led Rosado Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(255, 20, 147); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '8')
    {
      Serial.println("Led Blanco Estroboscópico");
      Serial.println("Presione 1, 2 o 3 para variar la frecuencia");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        setColor(255, 255, 255); // turn color on
        delay(n);
        ledOFF();
        delay(n);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          n = 30;
          break;
        }
        else if (subMenuOption2 == '1')
        {
          n = 70;
        }
        else if (subMenuOption2 == '2')
        {
          n = 120;
        }
        else if (subMenuOption2 == '3')
        {
          n = 200;
        }
      }
    }
    else if (subMenuOption2 == '9')
    {
      Serial.println("Salir al Menu Prinicpal");
      menu = 'q';
      runOnce = true;
      subMenu2Flag = false;
      mainMenu();
    }
    else
    {
      Serial.println("Elegir una opcion del 1 al 9");
    }
  }

  if (menuState == false && subMenu3Flag)
  {
    subMenuOption3 = Serial.read();
    if (subMenuOption3 == '1')
    {
      Serial.println("Led Rojo breathing");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        breathRED();
        delay(60);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          ledOFF();
          break;
        }
      }
    }
    else if (subMenuOption3 == '2')
    {
      Serial.println("Led Verde breathing");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        breathGREEN();
        delay(60);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          ledOFF();
          break;
        }
      }
    }
    else if (subMenuOption3 == '3')
    {
      Serial.println("Led Azul breathing");
      Serial.println("Presione q para detener el efecto y seleccionar otro color o salir");
      while (true)
      {
        breathBLUE();
        delay(60);
        subMenuOption2 = Serial.read();
        if (subMenuOption2 == 'q' || subMenuOption2 == 'Q')
        {
          ledOFF();
          break;
        }
      }
    }
    else if (subMenuOption3 == '4')
    {
      Serial.println("Salir al Menu Prinicpal");
      menu = 'q';
      runOnce = true;
      subMenu3Flag = false;
      mainMenu();
    }
    else
    {
      Serial.println("Elegir una opcion del 1 al 4");
    }
  }
}
