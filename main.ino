
unsigned char red = 3;
unsigned char green = 2;
unsigned char buzzer = 9;
unsigned char s1_echo = 4;
unsigned char s1_trig = 5;
unsigned char s2_echo = 6;
unsigned char s2_trig = 7;

int s1init_dist = 0;
int s2init_dist = 0;


int get_dist(unsigned char echo, unsigned char trig) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  long duration = pulseIn(echo, HIGH, 26000);
  return duration / 58;
}

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT);

  delay(500);
  s2init_dist = get_dist(s1_echo, s1_trig);
  s2init_dist = get_dist(s2_echo, s2_trig);
}

void loop() {
  int sensor1Val = get_dist(s1_echo, s1_trig);
  int sensor2Val = get_dist(s2_echo, s2_trig);
  

  if(currentPeople = maxPeople){
    digitalWrite(red, HIGH); 
    digitalWrite(green, LOW);
  }
  else if (currentPeople > maxPeople){
      //bizzzzz
  }
  else{
    digitalWrite(red, LOW); 
    digitalWrite(green, HIGH);  
  }
}
