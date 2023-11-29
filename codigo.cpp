#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#define BACKLIGHT 13
#define PRESET_INICIO A0
#define PRESET_FINAL A1

Servo myServo;
LiquidCrystal myLcd(2, 3, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 12, 10, 9, 8 };
byte colPins[COLS] = { 7, 6, 5, 4 };

Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool backlightOn = false;

//modo normal
int anguloInicioActual = 0;
int anguloFinalActual = 0;
int indiceClaveNumerica = 0;

//modo cambio de angulo
bool modoCambioDeAngulo = false;
int anguloInicio = 0;
int anguloFinal = 0;

//modo programacion
bool modoProgramacion = false;
int clave[4] = { 1, 2, 3, 4 };
int nuevaClave[4];


//modo informacion
bool modoInformacion = false;
int indiceClaveInformacion = 0;
char claveInformacion[5] = { 'D', 'A', 'C', 'B', '#' };
bool claveCorrecta = false;

void setup()
{
    myServo.attach(11);
    myLcd.begin(16, 2);
    pinMode(BACKLIGHT, OUTPUT);
    mostrarAngulosModoNormal();
    Serial.begin(9600);
}

void loop()
{
    char key = teclado.getKey();

    if (modoInformacion)
    {
        manejarEntradaClaveInformacion(key);
    }
    else
    {
        if (!modoProgramacion)
        {
            switch (key)
            {
            case '#':
                manejarTeclaNumeral();
                break;
            case 'B':
                manejarTeclaB();
                break;
            case '*':
                entrarModoProgramacion();
                break;
            case 'C':
                validarClaveNumericaInversa();
                break;
            }
            if (modoCambioDeAngulo)
            {
                mostrarCambioDeAngulos();
            }
        }
        else
        {
            manejarEntradaClave(key);
        }
    }

    if (!modoProgramacion && !modoCambioDeAngulo && !modoInformacion)
    {
        if (key >= '0' && key <= '9')
        {
            manejarClaveNumerica(key);
        }
        else if (key == 'A')
        {
            validarClaveNumerica();
        }
    }

}

// SETUP
void mostrarAngulosModoNormal()
{
    myLcd.clear();
    myLcd.setCursor(0, 0);
    myLcd.print("Ini: ");
    myLcd.print(anguloInicioActual);
    myLcd.print(" Fin: ");
    myLcd.print(anguloFinalActual);
    myLcd.setCursor(0, 1);
    myLcd.print("      ****");
    indiceClaveNumerica = 0;
}

// TECLA A Y C

void manejarClaveNumerica(char key)
{
    if (indiceClaveNumerica < 4)
    {
        nuevaClave[indiceClaveNumerica] = key - '0';
        myLcd.setCursor(6 + indiceClaveNumerica, 1);
        myLcd.print(key);
        indiceClaveNumerica++;
    }
}

void validarClaveNumerica()
{
    if (indiceClaveNumerica == 4)
    {
        if (esClaveCorrectaNormal())
        {
            abrirBarrera();
        }
        else
        {
            mostrarMensajeClaveIncorrecta();
        }
        mostrarAngulosModoNormal();
    }
}

void validarClaveNumericaInversa()
{
    if (indiceClaveNumerica == 4)
    {
        if (esClaveCorrectaInverso())
        {
            cerrarBarrera();
        }
        else
        {
            mostrarMensajeClaveIncorrecta();
        }
        mostrarAngulosModoNormal();
    }
}

bool esClaveCorrectaNormal()
{
    for (int i = 0; i < 4; i++)
    {
        if (nuevaClave[i] != clave[i])
        {
            return false;
        }
    }
    return true;
}

bool esClaveCorrectaInverso()
{
    for (int i = 0; i < 4; i++)
    {
        if (nuevaClave[i] != clave[3 - i])
        {
            return false;
        }
    }
    return true;
}

void mostrarMensajeClaveIncorrecta()
{
    myLcd.clear();
    myLcd.print("Clave incorrecta");
    delay(2000);
    mostrarAngulosModoNormal();
}


// TECLA B

void manejarTeclaB()
{
    if (!modoInformacion)
    {
        alternarModoCambioDeAngulos();
    }
}

void alternarModoCambioDeAngulos()
{
    modoCambioDeAngulo = !modoCambioDeAngulo;
    if (modoCambioDeAngulo)
    {
        myLcd.clear();
        mostrarCambioDeAngulos();
    }
    else
    {
        myLcd.clear();
        mostrarAngulosModoNormal();
    }
}

void leerPresets()
{
    int lecturaInicio = analogRead(PRESET_INICIO);
    int lecturaFinal = analogRead(PRESET_FINAL);

    anguloInicio = map(lecturaInicio, 0, 1023, 0, 45);
    anguloFinal = map(lecturaFinal, 0, 1023, 150, 180);
}

void mostrarCambioDeAngulos()
{
    leerPresets();
    anguloInicioActual = anguloInicio;
    anguloFinalActual = anguloFinal;

    if (modoCambioDeAngulo)
    {
        myLcd.setCursor(0, 1);
        myLcd.print("Cambio de Angulo");
        myLcd.setCursor(0, 0);
        myLcd.print("Ini: ");
        myLcd.print(anguloInicio);
        myLcd.setCursor(8, 0);
        myLcd.print("Fin: ");
        myLcd.print(anguloFinal);
    }
}

// TECLA #

void alternarBacklight()
{
    backlightOn = !backlightOn;
    if (backlightOn)
    {
        digitalWrite(BACKLIGHT, HIGH);
    }
    else
    {
        digitalWrite(BACKLIGHT, LOW);
    }
}

void manejarTeclaNumeral()
{
    alternarBacklight();
    if (!modoCambioDeAngulo && !modoInformacion)
    {
        modoInformacion = true;
        indiceClaveInformacion = 0;
        myLcd.clear();
        myLcd.setCursor(0, 1);
        myLcd.print("Informacion");
        myLcd.setCursor(0, 0);
        myLcd.print(">");
    }
}

void manejarEntradaClaveInformacion(char key)
{
    if (modoInformacion)
    {
        if (key != NO_KEY)
        {
            if (indiceClaveInformacion < 5)
            {
                validarClaveInformacion(key);
            }

            if (indiceClaveInformacion == 5)
            {
                finalizarSecuenciaInformacion();
            }
        }
    }
}

void validarClaveInformacion(char key)
{
    if (key == claveInformacion[indiceClaveInformacion])
    {
        myLcd.setCursor(indiceClaveInformacion, 0);
        myLcd.print(key);
        indiceClaveInformacion++;
    }
    else
    {
        myLcd.clear();
        myLcd.print("Secuencia incorrecta");
        delay(2000);
        mostrarAngulosModoNormal();
        modoInformacion = false;
    }
}

void finalizarSecuenciaInformacion()
{
    myLcd.clear();
    myLcd.setCursor(0, 0);
    for (int i = 0; i < 4; i++)
    {
        myLcd.print(clave[i]);
    }
    delay(2000);
    mostrarAngulosModoNormal();
    modoInformacion = false;
}


// TECLA *

void entrarModoProgramacion()
{
    modoProgramacion = true;

    if (modoCambioDeAngulo)
    {
        modoCambioDeAngulo = false;
    }

    indiceClaveNumerica = 0;
    mostrarPantallaModoProgramacion();
}

void mostrarPantallaModoProgramacion()
{
    myLcd.clear();
    myLcd.setCursor(0, 1);
    myLcd.print("  Programacion");
    myLcd.setCursor(0, 0);

    for (int i = 0; i < 4; i++)
    {
        myLcd.print("-");
    }
}

void manejarEntradaClave(char key)
{
    if (key >= '0' && key <= '9')
    {
        (key);
    }
    else if (key == '*')
    {
        finalizarEntradaClave();
    }
}

void manejarDigito(char key)
{
    if (indiceClaveNumerica < 4)
    {
        nuevaClave[indiceClaveNumerica] = key - '0';
        myLcd.setCursor(indiceClaveNumerica, 0);
        myLcd.print(key);
        indiceClaveNumerica++;
    }
}

void finalizarEntradaClave()
{
    if (indiceClaveNumerica == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            clave[i] = nuevaClave[i];
        }
        mostrarMensajeClaveGuardada();
    }
    else
    {
        mostrarMensajeError();
    }
    modoProgramacion = false;
    mostrarAngulosModoNormal();
}

void mostrarMensajeClaveGuardada()
{
    myLcd.clear();
    myLcd.setCursor(0, 1);
    myLcd.print("Clave Guardada ");
    delay(2000);
}

void mostrarMensajeError()
{
    myLcd.clear();
    myLcd.setCursor(0, 1);
    myLcd.print("     Falla");
    delay(2000);
}

// BARRERAS

void abrirBarrera()
{
    myLcd.clear();
    myLcd.setCursor(0, 1);
    myLcd.print("Abre Barrera");
    myServo.write(anguloInicioActual);
    delay(2000);
}

void cerrarBarrera()
{
    myLcd.clear();
    myLcd.setCursor(0, 1);
    myLcd.print("Cierra Barrera");
    myServo.write(anguloFinalActual);
    delay(2000);
}


