const int PWMA = 4;
const int AIN1 = 5;
const int AIN2 = 7;

const int speeds[] = {0, 64, 128, 191, 255};  // 0%, 25%, 50%, 75%, 100%
const int numSpeeds = 5;
int speedIndex = 0;

unsigned long previousMillis = 0;
const unsigned long STEP_INTERVAL = 2000;  // 2秒ごとに速度を変える

void setup() {
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // 正転方向に固定(AIN1=H, AIN2=L)
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= STEP_INTERVAL) {
    previousMillis = currentMillis;

    int pwmValue = speeds[speedIndex];
    analogWrite(PWMA, pwmValue);

    Serial.print("Speed: ");
    Serial.print((pwmValue * 100) / 255);
    Serial.println("%");

    speedIndex = (speedIndex + 1) % numSpeeds;
  }
}