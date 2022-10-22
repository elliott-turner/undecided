#define X_PIN A0
#define Y_PIN A1
#define L_PIN 3
#define R_PIN 2
#define NUM_READINGS 10

void setup() {
  // put your setup code here, to run once:
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(L_PIN, INPUT_PULLUP);
  pinMode(R_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

float xs[NUM_READINGS] = {0.0};
float ys[NUM_READINGS] = {0.0};
int l = 0;
int r = 0;
int i = 0;

void loop() {
  l = 0;
  r = 0;
  
  for(i=0; i<NUM_READINGS; i++) {
    xs[i] = analogRead(X_PIN)-450.0;
    ys[i] = analogRead(Y_PIN)-450.0;
    if (digitalRead(L_PIN)) { l = 1; }
    if (digitalRead(R_PIN)) { r = 1; }
    delay(12);
  }

  float x_sum = 0;
  float y_sum = 0;
  for (i=0; i<NUM_READINGS; i++) {
    x_sum += xs[i];
    y_sum += ys[i];
  }

  // put your main code here, to run repeatedly:
  Serial.print(x_sum / (float)NUM_READINGS);
  Serial.print(" ");
  Serial.print(y_sum / (float)NUM_READINGS);
  Serial.print(" ");
  Serial.print(l);
  Serial.print(" ");
  Serial.print(r);
  Serial.print(" \n");
}
