
#define ledPin1 2
#define ledPin2 3
#define ledPin3 4

const int MIN_VAL = 1;
const int MAX_VAL = 3;
const int MAX_SEQUENCE = 50; //Max sequence length
int selectedSequence = 5; //Default sequence length
bool started = false;

int sequence[MAX_SEQUENCE];

int seqIndex = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}


void loop() {
  if(!started) {  //Prompt player for sequence length before starting a game
    start();      
    if(!started) return;
  }
  
  addSeq();   //add to sequence and flash the entire sequence
  flashSeq();

  if(!takeInput()) {  //Take user input and check if user failed
    lose();
    return;
  }

  if(seqIndex == selectedSequence) {  //Check if player has reached their selected sequence length 
    win();
    return;
  }
  printCurrSequence();
  delay(2000);  //Wait briefly to update sequence and flash again
}


void start()  {
  Serial.print("Enter your desired sequence length (1-");
  Serial.print(MAX_SEQUENCE);
  Serial.println("):");
  while(Serial.available() == 0) {}
  String input = Serial.readStringUntil('\n');
  input.trim();
  int length = input.toInt();
  if(length < 1 || length > MAX_SEQUENCE) {
    Serial.println("Invalid input");
    return;
  }
  selectedSequence = length;
  while(Serial.available() > 0) Serial.read();  //Prevent any newline from being read as input
  started = true;
}

void addSeq() {
  if (seqIndex < selectedSequence) {
    sequence[seqIndex] = random(MIN_VAL, MAX_VAL + 1);
    seqIndex++;
  }
}

void flashSeq() {
  for(int i = 0; i < seqIndex; i++) {
    int led;
    if(sequence[i] == 1){
      led = ledPin1;
    } else if(sequence[i] == 2) {
      led = ledPin2;
    } else {
      led = ledPin3;
    }
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}

void printCurrSequence()  {
  Serial.print("Your current sequence: ");
  Serial.print(seqIndex);
  Serial.print("/");
  Serial.println(selectedSequence);
}

bool takeInput() {
  for(int i = 0; i < seqIndex; i++){
    while(Serial.available() == 0){}
    String input = Serial.readStringUntil('\n');
    input.trim();
    int val = input.toInt();
    
    if(val != sequence[i]) {  //Return false if user fails
      return false;
    }
  }
  return true;
}

void win() {
  seqIndex = 0;
  started = false;
  Serial.println("Congratulations, you win!");
  winSequence();
}

void lose() {
  seqIndex = 0;
  started = false;
  Serial.println("Incorrect!");
  loseSequence();
}

void winSequence() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(ledPin1, HIGH);
    delay(50);
    digitalWrite(ledPin2, HIGH);
    delay(50);
    digitalWrite(ledPin3, HIGH);
    delay(200);
    digitalWrite(ledPin1, LOW);
    delay(50);
    digitalWrite(ledPin2, LOW);
    delay(50);
    digitalWrite(ledPin3, LOW);
    delay(200);
  }
}

void loseSequence() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(200);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    delay(200);
  }
}


