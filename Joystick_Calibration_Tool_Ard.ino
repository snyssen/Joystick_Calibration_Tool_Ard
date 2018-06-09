// Utilitaire de calibration du joystick prévu pour comuniquer avec le programme parallèlement développé en C# sur PC
// Le joystick correspond au setup retrouvé dans Joystick_UNOJoy_V2.ino

const short pAxeX = 14; // pin A0 | Fil orange (/!\ pas confondre avec Vcc)
const short pAxeY = 15; // pin A1 | Fil jaune
const short pThrottle = 16; // pin A2
const short pGachette = 5; // pin 5 | Fil blanc
const short pMissile = 6; // pin 6 | Fil bleu
const short pSecVcc = 2; // pin 2 | sert de second pin d'alimentation, utilisé pour la throttle


void setup()
{
  // setup des pins utilisé, voir plus bas
  setupPins();
  Serial.begin (9600);
}

void loop()
{
  // On récupère toutes les valeurs
  int vGachette = digitalRead(pGachette);
  int vMissile = digitalRead(pMissile);
  // Explications mapping et pertes des LSBs -> voir Joystick_UNOJoy_V2.ino
  int vAxeX = map(analogRead(pAxeX), 415, 605, 0, 1023) >> 2;
  int vAxeY = map(analogRead(pAxeY), 375, 640, 0, 1023) >> 2;
  int vThrottle = analogRead(pThrottle) >> 2;

  //On envoie maintenant toutes ces données
  String result = String(vGachette);
  result.concat(';');
  result.concat(vMissile);
  result.concat(';');
  result.concat(vAxeX);
  result.concat(';');
  result.concat(vAxeY);
  result.concat(';');
  result.concat(vThrottle);
  Serial.println(result);
  //Léger délai pour laisser le temps aux pins de se stabiliser en tension
  delay(1);
}

void setupPins(void)
{
  pinMode(pAxeX, INPUT);
  pinMode(pAxeY, INPUT);
  pinMode(pThrottle, INPUT);
  pinMode(pGachette, INPUT);
  pinMode(pMissile, INPUT);
  pinMode(pSecVcc, OUTPUT);
  digitalWrite(pSecVcc, HIGH);
}
