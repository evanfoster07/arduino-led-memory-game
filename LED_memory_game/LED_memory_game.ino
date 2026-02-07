
#define ledPin1 2
#define ledPin2 3
#define ledPin3 4

const int MIN_VAL = 1;
const int MAX_VAL = 3;
const int MAX_SEQUENCE = 5;

int sequence[MAX_SEQUENCE];

int seqIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000000000);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  randomSeed(analogRead(A0));
}


void loop() {
  //Add to sequence
  if (seqIndex < MAX_SEQUENCE) {
    sequence[seqIndex] = random(MIN_VAL, MAX_VAL + 1);
    seqIndex++;
  //Print win message and reset if user completes length of MAX_SEQUENCE
  } else {
    Serial.print("Congratulations, you win!");
    seqIndex = 0;
  }

  //Flash sequence to user
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
  
  //Take user input
  for(int i = 0; i < seqIndex; i++){
    while(Serial.available() == 0){}
    int input = Serial.readStringUntil('\n').toInt();
    //reset if user fails
    if(input != sequence[i]) {
      seqIndex = 0;
      break;
    }
  }
  //Wait briefly to update sequence and flash again
  delay(2500);
}





