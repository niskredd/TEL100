//Oppsett
unsigned char red = 3;
unsigned char green = 2;
unsigned char buzzer = 9;
unsigned char s1_echo = 4;
unsigned char s1_trig = 5;
unsigned char s2_echo = 6;
unsigned char s2_trig = 7;

unsigned int pop_max = 10;
int pop_now = 0;

int s1init_dist = 0;
int s2init_dist = 0;

//Lese av avstaden til et objekt
int get_dist(unsigned char echo, unsigned char trig) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  long duration = pulseIn(echo, HIGH, 26000);
  return duration / 58;
}


bool wait_sensor(){
  if((get_dist(s2_echo, s2_trig) < s2init_dist - 30) || (get_dist(s1_echo, s1_trig) < s1init_dist - 30)){
    delay(500);
    return true;
  }
  else{   return false; }
}

//Innstillinger for oppstart. 
void setup() {
  Serial.begin(9600);
  Serial.println("Starting up....");
  delay(5000);
  pinMode(red, OUTPUT);
  Serial.println("Pin 3 is set to output Red diode");
  pinMode(green, OUTPUT);
  Serial.println("Pin 2 is set to output Green diode");
  pinMode(buzzer, OUTPUT);
  Serial.println("Pin 9 is set to output Buzzer");

  delay(3000);
  s1init_dist = get_dist(s1_echo, s1_trig);
  s2init_dist = get_dist(s2_echo, s2_trig);

  s1init_dist = get_dist(s1_echo, s1_trig);
  s2init_dist = get_dist(s2_echo, s2_trig);
  delay(2000);

  s1init_dist = get_dist(s1_echo, s1_trig);
  s2init_dist = get_dist(s2_echo, s2_trig);
  Serial.print("Default distans sensor 1:    ");
  Serial.println(s1init_dist);
  Serial.print("Default distans sensor 2:    ");
  Serial.println(s2init_dist);
  Serial.print("Initial population:    ");
  Serial.println(pop_now);
}

void loop() {
  int s1dist = get_dist(s1_echo, s1_trig);
  int s2dist = get_dist(s2_echo, s2_trig);
  
  //Sjekke forandringer i avstad siden inisiering.
  if (s1dist < s1init_dist - 30){
    pop_now++;
    Serial.println(s1dist);
    while(wait_sensor());
    Serial.println("One person more in area");
    Serial.print("Customers   ");
    Serial.println(pop_now);
  }
  else if (s2dist < s2init_dist - 30){
    pop_now--;
    if(pop_now < 0){
      pop_now = 0;
    }
    Serial.println(s2dist);
    while(wait_sensor());
    Serial.println("One person less in area");
    Serial.print("Customers   ");
    Serial.println(pop_now);
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
}
