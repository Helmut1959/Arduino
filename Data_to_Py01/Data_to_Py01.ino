int cnt = 1;
int DL = 50;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(cnt);
  Serial.println(" Datapoints");
  cnt = cnt +1;
  delay(DL);

}
