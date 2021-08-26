//Oppsett
unsigned char red = 3;
unsigned char green = 2;
unsigned char buzzer = 9;
unsigned char s1_echo = 4;
unsigned char s1_trig = 5;
unsigned char s2_echo = 6;
unsigned char s2_trig = 7;

unsigned char pop_max = 5;
unsigned char pop_now = 0;

int s1init_dist = 0;
int s2init_dist = 0;

//Lese av avstaden til et objekt
int get_dist(unsigned char echo, unsigned char trig) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  long duration = pulseIn(echo, HIGH, 26000);
  return duration / 58;
}


//Innstillinger for oppstart. 
void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);

  delay(500);
  s1init_dist = get_dist(s1_echo, s1_trig);
  s2init_dist = get_dist(s2_echo, s2_trig);
  Serial.println(pop_now);
}

void loop() {
  int s1dist = get_dist(s1_echo, s1_trig);
  int s2dist = get_dist(s2_echo, s2_trig);

  //Sjekke forandringer i avstad siden inisiering.
  if (s1dist < s1init_dist - 30){
    pop_now++;
    delay(500);
  }
  else if (s2dist < s2init_dist - 30){
    pop_now--;
    delay(500);
  }

  //Sjekke antallet menneseker i orådet
  if(pop_now == pop_max){
    noTone(buzzer);
    digitalWrite(red, HIGH); 
    digitalWrite(green, LOW);
  }
  else if (pop_now > pop_max){
      tone(buzzer, 1500);
  }
  else{
    noTone(buzzer);
    digitalWrite(red, LOW); 
    digitalWrite(green, HIGH);  
  }

  //Sriver ut antallet mennesker i COM port
  Serial.print("Antall   ");
  Serial.println(pop_now);
}
