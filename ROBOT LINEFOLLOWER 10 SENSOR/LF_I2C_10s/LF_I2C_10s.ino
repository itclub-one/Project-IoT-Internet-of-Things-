#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int speed_right = 30;
int speed_left = 0;
const int inh = 12;
const int selA = A0;
const int selB = A3;
const int selC = A2;
const int sensor_depan = A6;
const int button1 = 1;
const int button2 = 0;
const int button3 = 11;
const int rem_ka = 8;
const int dir_ka = 9;
const int ena_ka = 5;
const int rem_ki = 7;
const int dir_ki = 10;
const int ena_ki = 6;
unsigned char tombol1 = 0;
unsigned char tombol2 = 0;
unsigned char tombol3 = 0;
int data_sensor[10];
unsigned int counter = 0, up = 0, lintasan = 0;
int xsensor, var, jumlah_indeks, jum_indeks;
int s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, flag;
int ref[10], sens[10];
int sensor_now[10], maks[10];
int minimal[10] = {1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100};
int address = 0, address_jumlah_indeks = 50, address_speed = 15, address_kons_p = 20, address_kons_d = 30, address_kons_i = 40, address_indeks2 = 10, address_path = 100;
unsigned char pwm_ka, pwm_ki, indeks = 0, loop_indeks2;
int laju, kecepatan, pi, di, ai, kons_p, kons_d, kons_i;
char path[100] = " ";
char path_solve[100] = " ";
char maze_solve[100] = " ";
unsigned char pathLength = 0;
int pathIndex = 0, a, count = 0, i, j, indeks2;
unsigned int status = 0;
int nilai[32], jumlah, hasil;

void maju(unsigned char kiri, unsigned char kanan) {
  pwm_ka = kanan + speed_right;       pwm_ki = kiri + speed_left;
  pwm_ka = 255 - pwm_ka;  pwm_ki = 255 - pwm_ki;
  analogWrite(ena_ka, pwm_ka); analogWrite(ena_ki, pwm_ki);
  digitalWrite(dir_ka, HIGH);  digitalWrite(dir_ki, HIGH);
  digitalWrite(rem_ka, HIGH);  digitalWrite(rem_ki, HIGH);
}
void mundur(unsigned char kiri, unsigned char kanan) {
  pwm_ka = kanan + speed_right;   pwm_ki = kiri + speed_left;
  pwm_ka = 255 - pwm_ka;  pwm_ki = 255 - pwm_ki;
  analogWrite(ena_ka, pwm_ka); analogWrite(ena_ki, pwm_ki);
  digitalWrite(dir_ka, LOW);   digitalWrite(dir_ki, LOW);
  digitalWrite(rem_ka, HIGH);  digitalWrite(rem_ki, HIGH);
}
void bel_ka(unsigned char kiri, unsigned char kanan) {
  pwm_ki = kiri + speed_left;    pwm_ka = kanan + speed_right;
  pwm_ka = 255 - pwm_ka;  pwm_ki = 255 - pwm_ki;
  analogWrite(ena_ka, pwm_ka); analogWrite(ena_ki, pwm_ki);
  digitalWrite(dir_ka, LOW);   digitalWrite(dir_ki, HIGH);
  digitalWrite(rem_ka, HIGH);  digitalWrite(rem_ki, HIGH);
}
void bel_ki(unsigned char kiri, unsigned char kanan) {
  pwm_ki = kiri + speed_left;    pwm_ka = kanan + speed_right;
  pwm_ka = 255 - pwm_ka;  pwm_ki = 255 - pwm_ki;
  analogWrite(ena_ka, pwm_ka); analogWrite(ena_ki, pwm_ki);
  digitalWrite(dir_ka, HIGH);   digitalWrite(dir_ki, LOW);
  digitalWrite(rem_ka, HIGH);  digitalWrite(rem_ki, HIGH);
}
void rem() {
  digitalWrite(rem_ka, LOW);  digitalWrite(rem_ki, LOW);
}
void stopped() {
  analogWrite(ena_ka, HIGH); analogWrite(ena_ki, HIGH);
  digitalWrite(dir_ka, HIGH);   digitalWrite(dir_ki, HIGH);
  digitalWrite(rem_ka, LOW);  digitalWrite(rem_ki, LOW);
}
void baca_button() {
  tombol1 = digitalRead(button1);
  tombol2 = digitalRead(button2);
  tombol3 = digitalRead(button3);
}
void sensing() {
  data_sensor[0] = analogRead(A7);
  digitalWrite(inh, LOW);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  data_sensor[1] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  data_sensor[2] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);
  data_sensor[3] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);
  data_sensor[4] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  data_sensor[5] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  data_sensor[6] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  data_sensor[7] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  data_sensor[8] = analogRead(sensor_depan);
  data_sensor[9] = analogRead(A1);
}
void sensing_kalibrasi() {
  sensor_now[0] = analogRead(A7);
  digitalWrite(inh, LOW);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  sensor_now[1] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, LOW);
  sensor_now[2] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);
  sensor_now[3] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, LOW);
  sensor_now[4] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  sensor_now[5] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, LOW);
  digitalWrite(selC, HIGH);
  sensor_now[6] = analogRead(sensor_depan);
  digitalWrite(selA, LOW);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  sensor_now[7] = analogRead(sensor_depan);
  digitalWrite(selA, HIGH);
  digitalWrite(selB, HIGH);
  digitalWrite(selC, HIGH);
  sensor_now[8] = analogRead(sensor_depan);
  sensor_now[9] = analogRead(A1);
}
void read_sensor() {
  sensing();
  xsensor = 255;
  xsensor &= 255;
  if (data_sensor[0] < (sens[0] * 4)) {
    s0 = 0;
  }   else {
    s0 = 1;
  }
  if (data_sensor[1] < (sens[1] * 4)) {
    s1 = 0;
    var = 1;
  }   else {
    s1 = 1;
    var = 0;
    flag = 1;
  } xsensor &= ~var;
  if (data_sensor[2] < (sens[2] * 4)) {
    s2 = 0;
    var = 2;
  }   else {
    s2 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[3] < (sens[3] * 4)) {
    s3 = 0;
    var = 4;
  }   else {
    s3 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[4] < (sens[4] * 4)) {
    s4 = 0;
    var = 8;
  }   else {
    s4 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[5] < (sens[5] * 4)) {
    s5 = 0;
    var = 16;
  }  else {
    s5 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[6] < (sens[6] * 4)) {
    s6 = 0;
    var = 32;
  }  else {
    s6 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[7] < (sens[7] * 4)) {
    s7 = 0;
    var = 64;
  }  else {
    s7 = 1;
    var = 0;
  } xsensor &= ~var;
  if (data_sensor[8] < (sens[8] * 4)) {
    s8 = 0;
    var = 128;
  } else {
    s8 = 1;
    var = 0;
    flag = 0;
  } xsensor &= ~var;
  if (data_sensor[9] < (sens[9] * 4)) {
    s9 = 0;
  }   else {
    s9 = 1;
  }
}
void tampil_all_sensor() {
  read_sensor();
  lcd.setCursor(0, 0);
  lcd.print(s0);
  lcd.print(s1);
  lcd.print(s2);
  lcd.print(s3);
  lcd.print(s4);
  lcd.print(s5);
  lcd.print(s6);
  lcd.print(s7);
  lcd.print(s8);
  lcd.print(s9);
  lcd.setCursor(0, 1);
  lcd.print(xsensor);
  lcd.print("   ");
}
void tampil_raw_sensor() {
  lcd.setCursor(0, 0);
  lcd.print(sensor_now[1]);
  lcd.setCursor(4, 0);
  lcd.print(sensor_now[2]);
  lcd.setCursor(8, 0);
  lcd.print(sensor_now[3]);
  lcd.setCursor(12, 0);
  lcd.print(sensor_now[4]);
  lcd.setCursor(0, 1);
  lcd.print(sensor_now[5]);
  lcd.setCursor(4, 1);
  lcd.print(sensor_now[6]);
  lcd.setCursor(8, 1);
  lcd.print(sensor_now[7]);
  lcd.setCursor(12, 1);
  lcd.print(sensor_now[8]);
}
void kalibrasi2() {
  sensing_kalibrasi();
  tampil_raw_sensor();
  for (int i = 0; i <= 9; i++) {
    if (sensor_now[i] > maks[i]) {
      maks[i] = sensor_now[i];
    }
    else if (sensor_now[i] < minimal[i]) {
      minimal[i] = sensor_now[i];
    }
    ref[i] = (((maks[i] - minimal[i]) / 2) + minimal[i]) / 4;
    EEPROM.write(i, ref[i]);
  }
}
void inverse_pid(unsigned char simpan) {
  unsigned int kec_maks = 250;
  unsigned int kec_min = 60;
  int kp = kons_p;  //14  9.6      13.2
  int kd = kons_d; //76  18.3     250    230
  int ki = kons_i;  //146.5              //300        1130       1730    750
  static int error, lastError, Error, LastError, SumError, right_speed, left_speed;

  read_sensor();
  switch (xsensor) {
    case 254 : error = -7; break;
    case 252 : error = -6; break;
    case 253 : error = -5; break;
    case 249 : error = -4; break;
    case 251 : error = -3; break;
    case 243 : error = -2; break;
    case 247 : error = -1; break;
    case 231 : error = 0; break;
    case 239 : error =  1; break;
    case 207 : error =  2; break;
    case 223 : error =  3; break;
    case 159 : error =  4; break;
    case 191 : error =  5; break;
    case 63  : error =  6; break;
    case 127 : error =  7; break;
    case 255:
      if (flag == 0) {
        error = 8;
      }
      else {
        error = -8;
      }
      break;
  }
  int SetPoint = 0;                      // Setpoint yang diinginkan
  Error = SetPoint - error;
  int outPID = kp * 0.01 * Error + kd * 0.1 * (Error - lastError) + ki * 0.1;
  lastError = Error;

  double motorKi = simpan - outPID;     // Motor Kiri
  double motorKa = simpan + outPID;     // Motor Kanan

  /*** Pembatasan kecepatan ***/
  if (motorKi > kec_maks)motorKi = kec_maks;
  if (motorKi < kec_min)motorKi = kec_min;
  if (motorKa > kec_maks)motorKa = kec_maks;
  if (motorKa < kec_min)motorKa = kec_min;

  if (motorKi == motorKa) {
    maju(simpan, simpan);
  }
  else if (motorKi > motorKa) {
    bel_ka(motorKi, motorKa);
  }
  else if (motorKa > motorKi) {
    bel_ki(motorKi, motorKa);
  }
}
void pid(unsigned char simpan) {
  unsigned int kec_maks = 150;
  unsigned int kec_min = 60;
  int kp = kons_p;  //14  9.6      13.2
  int kd = kons_d; //76  18.3     250    230
  int ki = kons_i;  //146.5              //300        1130       1730    750
  static int error, lastError, Error, LastError, SumError, right_speed, left_speed;

  read_sensor();
  switch (xsensor) {
    case 1 : error = -7; break;
    case 3 : error = -6; break;
    case 2 : error = -5; break;
    case 6 : error = -4; break;
    case 4 : error = -3; break;
    case 12 : error = -2; break;
    case 8 : error = -1; break;
    case 24 : error = 0; break;
    case 16 : error =  1; break;
    case 48 : error =  2; break;
    case 32 : error =  3; break;
    case 96 : error =  4; break;
    case 64 : error =  5; break;
    case 192 : error =  6; break;
    case 128 : error =  7; break;
    case 0:
      if (flag == 0) {
        error = 8;
      }
      else {
        error = -8;
      }
      break;
  }
  int SetPoint = 0;                      // Setpoint yang diinginkan
  Error = SetPoint - error;
  int outPID = kp * 0.1 * Error + kd * (Error - lastError) + ki * 0.1;
  lastError = Error;

  double motorKi = simpan - outPID;     // Motor Kiri
  double motorKa = simpan + outPID;     // Motor Kanan

  /*** Pembatasan kecepatan ***/
  if (motorKi > kec_maks)motorKi = kec_maks;
  if (motorKi < kec_min)motorKi = kec_min;
  if (motorKa > kec_maks)motorKa = kec_maks;
  if (motorKa < kec_min)motorKa = kec_min;

  if (motorKi == motorKa) {
    maju(simpan, simpan);
  }
  else if (motorKi > motorKa) {
    bel_ka(motorKi, motorKa);
  }
  else if (motorKa > motorKi) {
    bel_ki(motorKi, motorKa);
  }
}
void pid6(unsigned char simpan) {
  unsigned int kec_maks = 200;
  unsigned int kec_min = 150;
  int kp = kons_p;  //14  9.6      13.2
  int kd = kons_d; //76  18.3     250    230
  int ki = kons_i;  //146.5              //300        1130       1730    750
  static int error, lastError, Error, LastError, SumError, right_speed, left_speed;

  read_sensor();
  switch (xsensor) {
    case 2 : error = -5; break;
    case 6 : error = -4; break;
    case 4 : error = -3; break;
    case 12 : error = -2; break;
    case 8 : error = -1; break;
    case 24 : error = 0; break; //robot ditengah
    case 16 : error =  1; break;
    case 48 : error =  2; break;
    case 32 : error =  3; break;
    case 96 : error =  4; break;
    case 64 : error =  5; break;
    case 0:
      if (flag == 0) {
        error = 6;
      }
      else {
        error = -6;
      }
      break;
  }
  int SetPoint = 0;                      // Setpoint yang diinginkan
  Error = SetPoint - error;
  int outPID = kp * 0.1 * Error + kd * (Error - lastError) + ki * 0.1;
  lastError = Error;

  double motorKi = simpan - outPID;     // Motor Kiri
  double motorKa = simpan + outPID;     // Motor Kanan

  /*** Pembatasan kecepatan ***/
  if (motorKi > kec_maks)motorKi = kec_maks;
  if (motorKi < kec_min)motorKi = kec_min;
  if (motorKa > kec_maks)motorKa = kec_maks;
  if (motorKa < kec_min)motorKa = kec_min;

  if (motorKi == motorKa) {
    maju(simpan, simpan);
  }
  else if (motorKi > motorKa) {
    bel_ka(motorKi, motorKa);
  }
  else if (motorKa > motorKi) {
    bel_ki(motorKi, motorKa);
  }
}
void pindah_track_hitam_putih() {
  while (1) {
    pid(110);
    if (s8 || s7)
      break;
  }
  maju(100, 100);
  delay(100);
}
void inverse_perempatan_kanan() {
  while (1) {
    inverse_pid(kecepatan);
    if (!s1 || !s8)
      break;
  }
  mundur(100, 100); delay(50); rem(); delay(50);
  while (1) {
    bel_ka(100, 50);
    read_sensor();
    if (!s8)break;
  }
  while (1) {
    bel_ka(100, 50);
    read_sensor();
    if (!s5)break;
  }
  rem(); delay(50);
}
void perempatan_kanan() {
  while (1) {
    pid(100);
    if (s1 || s8)
      break;
  }
  mundur(100, 100); delay(50); rem(); delay(50);
  while (1) {
    bel_ka(100, 50);
    read_sensor();
    if (s8)break;
  }
  while (1) {
    bel_ka(100, 50);
    read_sensor();
    if (s5)break;
  }
  rem(); delay(50);
}
void perempatan_kiri() {
  while (1) {
    pid(kecepatan);
    if (s1 || s8)
      break;
  }
  mundur(100, 100); delay(50); rem(); delay(50);
  while (1) {
    bel_ki(50, 100);
    read_sensor();
    if (s1)break;
  }
  while (1) {
    bel_ki(50, 100);
    read_sensor();
    if (s4)break;
  }
  rem(); delay(50);
}
void perempatan_lurus() {
  while (1) {
    pid(kecepatan);
    if (s1 || s8)
      break;
  }
  while (1) {
    maju(70, 80);
    read_sensor();
    if (s0 || s9)break;
  }
}
void inverse_kanan() {
  while (1) {
    read_sensor();
    if (!s3 && !s4) {
      maju(60, 60);
    }
    else if (!s4) {
      maju(60, 50);
    }
    else if (!s3) {
      maju(50, 60);
    }
    else if (!s4 && !s5) {
      bel_ka(70, 70);
    }
    else if (!s2 && !s3) {
      bel_ki(70, 70);
    }
    else if (!s8) {
      bel_ka(90, 90);
    }
    else if (!s1) {
      bel_ki(90, 90);
    }
    else if (!s8 || !s7) {
      break;
    }
  }
  while (1) {
    bel_ka(80, 60);
    read_sensor();
    if (!s4)break;
  }
}
void inverse_kiri() {
  while (1) {
    read_sensor();
    if (!s3 && !s4) {
      maju(60, 60);
    }
    else if (!s4) {
      maju(60, 50);
    }
    else if (!s3) {
      maju(50, 60);
    }
    else if (!s4 && !s5) {
      bel_ka(70, 70);
    }
    else if (!s2 && !s3) {
      bel_ki(70, 70);
    }
    else if (!s8) {
      bel_ka(90, 90);
    }
    else if (!s1) {
      bel_ki(90, 90);
    }
    else if (!s1 || !s2) {
      break;
    }
  }
  while (1) {
    maju(60, 60);
    read_sensor();
    if (!s0)break;
  }
  while (1) {
    bel_ki(60, 80);
    read_sensor();
    if (!s3)break;
  }
}

void siku_kiri2() {
  while (1) {
    pid(100);
    if (s1)break;
  }
  while (1) {
    maju(90, 90);
    read_sensor();
    if (s0)break;
  }
  while (1) {
    bel_ki(70, 70);
    read_sensor();
    if (s8)break;
  }
  while (1) {
    bel_ki(70, 70);
    read_sensor();
    if (s2 || s3 || s4)break;
  }
  rem(); delay(50);
}

void tajam_kiri() {
  while (1) {
    pid(kecepatan);
    if (s0)
      break;
  }
  mundur(100, 100); delay(95); rem(); delay(100);
  while (1) {
    maju(100, 100);
    if (s0)break;
  }
  rem(); delay(50);
  while (1) {
    bel_ki(10, 100);
    read_sensor();
    if (s0 || s1)break;
  }
  rem(); delay(100); stopped();
}
void y_kanan() {
  while (1) {
    pid(kecepatan);
    if (s1)
      break;
  }
  while (1) {
    bel_ka(40, 0);
    read_sensor();
    if (s4 || s5)break;
  }
  rem(); delay(50);
}
void y_kiri() {
  while (1) {
    pid(kecepatan);
    if (s1)
      break;
  }
  maju(70, 70); delay(20);
  while (1) {
    bel_ki(70, 80);
    read_sensor();
    if (s3 || s4)break;
  }
  rem(); delay(50);
}
void recIntersection(char direction) {
  path[pathLength] = direction; // Store the intersection in the path variable.
  pathLength ++;
  nilai[count] = a;
  count++;
  //simplifyPath(); // Simplify the learned path.
}
void pathPlanning(char direction) {
  path[pathLength] = direction; // Store the intersection in the path variable.
}
void move_S() {
  while (1) {
    pid(kecepatan);
    if (s1 || s2 || s7 || s8)break;
  }
  while (1) {
    maju(70, 70);
    delay(20);
    break;
  }
}
void move_L() {
  while (1) {
    pid(kecepatan);
    if (s1 || s2)break;
  }
  rem(); delay(20);
  while (1) {
    maju(70, 70);
    read_sensor();
    if (s0 || s9)break;
  }
  rem(); delay(10);
  while (1) {
    bel_ki(125, 55);
    read_sensor();
    if (s3 || s4)break;
  }
  rem(); delay(20);
}
void move_R() {
  while (1) {
    pid(kecepatan);
    if (s7 || s8)break;
  }
  rem(); delay(20);
  while (1) {
    maju(70, 70);
    read_sensor();
    if (s0 || s9)break;
  }
  rem(); delay(10);
  while (1) {
    bel_ka(80, 120);
    read_sensor();
    if (s6 || s5)break;
  }
  rem(); delay(20);
}
void move_E() {
  while (1) {
    pid(kecepatan);
    if (s3 && s4 && s5 && s6)break;
  }
  while (1) {
    stopped();
  }
}
void percobaan(int waktu) {
  for (i = 0; i <= waktu; i++) {
    for (j = 0; j <= 100; j++) {
      //while(1){
      read_sensor();
      if (s3 && s4) {
        maju(60, 60);
      }
      else if (s3) {
        maju(50, 60);
      }
      else if (s4) {
        maju(60, 50);
      }
      else if (s4 && s5) {
        maju(60, 45);
      }
      else if (s2 && s3) {
        maju(45, 60);
      }
      else if (s2) {
        bel_ki(60, 50);
      }
      else if (s5) {
        bel_ka(50, 60);
      }

      //}
    }
  }
}
void percobaan2() {
  while (1) {
    pid(kecepatan);
    read_sensor();
    if (s0 || s1)break;
  }
  while (1) {
    bel_ka(130, 80);
    read_sensor();
    if (s2 || s3); break;
  }
}
//my track
void bulat_1() {
  while (1) {
    pid(kecepatan);
    if (s3 && s4 && s5 && s6)break;
  }
  rem(); delay(75);
  while (1) {
    maju(kecepatan, kecepatan);
    read_sensor();
    if (!s3 && !s4 && !s5 && !s6)break;
  }
  rem(); delay(75);
  while (1) {
    bel_ka(110, 110);
    read_sensor();
    if ((!s2 && !s3 && s4) || (!s2 && s3 && s4)) break;
  }
  rem(); delay(50);
}
void bulat_2() {
  while (1) {
    pid(kecepatan);
    if (s3 && s4 && s5 && s6)break;
  }
  rem(); delay(50);
  while (1) {
    bel_ka(120, 120);
    read_sensor();
    if ((!s2 && !s3 && s4) || (!s3 && !s4 && s5) || (!s3 && s4 && s5)) break;
  }
  rem(); delay(75);
}
void pertigaan_kiri() {
  while (1) {
    maju(kecepatan, kecepatan);
    read_sensor();
    if (s9)break;
  }
  rem(); delay(75);
  while (1) {
    bel_ki(120, 100);
    read_sensor();
    if (s4 || s5)break;
  }
  rem(); delay(75);
}

void n_besar() {
  /*while (1) {
    pid(90);
    if (s6 && s7)
      break;
  }
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9)break;
  }
  while (1) {
    bel_ka(100, 60);
    read_sensor();
    if (s4 || s5)break;
  }
  //rem(); delay(30);
  while (1) {
    pid(90);
    if (s1 && s2)break;
  }
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9)break;
  }
  while (1) {
    bel_ka(60, 100);
    read_sensor();
    if (s4)break;
  }*/
  //bel_ka(100, 60);
  //delay(450);
  while (1) {
    pid(100);
    if (s0) break;
  }
}
void n_kecil() {
  while (1) {
    bel_ki(90, 90);
    read_sensor();
    if (s5) break;
  }
  while (1) {
    pid_timer(20);
    break;
  }
  /*while (1) {
    pid(100);
    if (!s2 && !s3 && !s4 && !s5 && !s6 && !s7)break;
    }*/
}
void huruf_v() {
  bel_ka(90, 90);
  delay(300);
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9)break;
  }
  while (1) {
    bel_ka(90, 90);
    read_sensor();
    if (s6)break;
  }
}
void pid_timer(int waktu) {
  for (i = 0; i <= waktu; i++) {
    for (j = 0; j <= 50; j++) {
      pid(kecepatan);
    }
  }
  //stopped();//mundur(0,255);delay(150);//rem();delay(50);
}
void pid_timer2(int waktu) {
  for (i = 0; i <= waktu; i++) {
    for (j = 0; j <= 50; j++) {
      pid6(170);
    }
  }
  //stopped();//mundur(0,255);delay(150);//rem();delay(50);
}
void siku_kiri() {
  while (1) {
    pid(kecepatan);
    if (s1)
      break;
  }
  rem(); delay(50);
  while (1) {
    maju(80, 80);
    read_sensor();
    if (s0)break;
  }
  rem(); delay(50);
  while (1) {
    bel_ki(100, 100);
    read_sensor();
    if (s3 || s2)break;
  }
  rem(); delay(50);
}
void siku_kanan() {
  while (1) {
    pid(kecepatan);
    if (s8)
      break;
  }
  rem(); delay(50);
  while (1) {
    maju(80, 80);
    read_sensor();
    if (s9)break;
  }
  rem(); delay(50);
  while (1) {
    bel_ka(100, 100);
    read_sensor();
    if (s6 || s5)break;
  }
  rem(); delay(50);
}
void tajam_kanan() {
  while (1) {
    pid(100);
    if (s8)
      break;
  }
  rem(); delay(100);
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9)break;
  }
  rem(); delay(100);
  while (1) {
    bel_ka(110, 110);
    read_sensor();
    if (s4 || s5)break;
  }
  rem(); delay(100);
}
void tajam_kanan_2() {
  while (1) {
    pid(100);
    if (s8)
      break;
  }
  rem(); delay(100);
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9)break;
  }
  rem(); delay(100);
  while (1) {
    bel_ka(90, 90);
    read_sensor();
    if (s8)break;
  }
}
void huruf_k() {
  while (1) {
    pid(100);
    if (s7 || s8)
      break;
  }
  while (1) {
    maju(90, 90);
    read_sensor();
    if (s9) break;
  }
  while (1) {
    bel_ka(90, 90);
    read_sensor();
    if (s7)break;
  }
}
void segitiga() {
  while (1) {
    pid(100);
    if (s7 || s8)
      break;
  }
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s9) break;
  }
  while (1) {
    bel_ki(90, 90);
    read_sensor();
    if (s1 || s2) break;
  }
}
void kapasitor() {
  while (1) {
    pid(kecepatan);
    if (s1 || s8)break;
  }
  maju(110, 110);
  delay(200);
}
void kepala() {
  while (1) {
    pid(100);
    if (s2 || s7)
      break;
  }
  while (1) {
    read_sensor();
    if (!s4 && s5) {
      maju(100, 100);
    }
    else if (s4) {
      bel_ki(110, 80);
    }
    else if (!s5) {
      bel_ka(80, 1100);
    }
    else if (!s4 && !s5) {
      maju(100, 100);
    }
  }
}
void putus_putus(int a) {
  for (i = 0; i <= a; i++) {
    while (1) {
      pid(90);
      if (!s3 && !s4 && !s5 && !s6)
        break;
    }
    while (1) {
      maju(100, 100);
      read_sensor();
      if (s2 || s3 || s4 || s5 || s6 || s7)
        break;
    }
  }
}
void putus_baru() {
lompat:
  while (1) {
    pid(100);
    if (!s3 && !s4 && !s5 && !s6)break;
  }
  while (1) {
    maju(100, 100);
    read_sensor();
    if (s1 || s2 || s3 || s4 || s5 || s6 || s7 || s8) {
      goto lompat;
    }
  }
}
void setup() {
  //Serial.begin(9600);
  lcd.begin();
  pinMode (inh, OUTPUT);
  pinMode (selA, OUTPUT);
  pinMode (selB, OUTPUT);
  pinMode (selC, OUTPUT);
  pinMode (rem_ka, OUTPUT);
  pinMode (dir_ka, OUTPUT);
  pinMode (ena_ka, OUTPUT);
  pinMode (rem_ki, OUTPUT);
  pinMode (dir_ki, OUTPUT);
  pinMode (ena_ki, OUTPUT);
  pinMode (button1, INPUT_PULLUP);
  pinMode (button2, INPUT_PULLUP);
  pinMode (button3, INPUT_PULLUP);
}
void loop() {
awal:
  lcd.setCursor(0, 0);
  lcd.print("1.Setting ");
  lcd.setCursor(0, 1);
  lcd.print("2.Sensor ");
  lcd.setCursor(10, 0);
  lcd.print("3.Play");
  baca_button();
  while (tombol1 && tombol2 && tombol3) {
    baca_button();
  }//tampil_sensor();}
  if (!tombol1) { //TEKAN TOMBOL SETTING
    delay(200);
    lcd.clear();
    delay(200);
    while (!tombol1) {
      baca_button();
      lcd.setCursor(0, 0);
      lcd.print("1.Kalib ");
      lcd.setCursor(0, 1);
      lcd.print("2.Speed ");
      lcd.setCursor(10, 0);
      lcd.print("3.PID");
    }
    while (1) {
      while (tombol1 && tombol2 && tombol3) {
        baca_button();
      }
      if (!tombol1) { //TEKAN TOMBOL KALIBRASI
        lcd.clear();
        delay(200);
        while (!tombol1) {
          delay(50);
          while (1) {
            baca_button();
            kalibrasi2();
            if (!tombol1) {
              delay(200);
              goto awal;
            }
          }
        }
      }
      else if (!tombol3) { //TEKAN TOMBOL SPEED
        delay(100);
        kecepatan = EEPROM.read(address_speed);
        laju = kecepatan;
        while (!tombol3) {
          baca_button();
        }
        lcd.clear();
        while (1) {
          lcd.setCursor(0, 0);
          lcd.print("Speed:");
          lcd.print(kecepatan);
          lcd.print("  ");
          baca_button();
          if (!tombol1) { //SPEED UP
            delay(200);
            laju++;
            if (laju > 255) {
              laju = 0;
            }
            lcd.print(laju);
            lcd.print("  ");
          }
          else if (!tombol3) { //SPEED DOWN
            delay(200);
            laju--;
            if (laju < 0) {
              laju = 255;
            }
            lcd.print(laju);
            lcd.print("  ");
          }
          else if (!tombol2) { //OK
            delay(200);
            lcd.clear();
            EEPROM.write(address_speed, laju);
            delay(500);
            lcd.setCursor(0, 0);
            lcd.print("OK");
            delay(500);
            lcd.clear();
            goto awal;
          }
        }
      }
      else if (!tombol2) { //TEKAN TOMBOL PID
        delay(100);
        lcd.clear();
        delay(200);
        kons_p = EEPROM.read(address_kons_p);
        kons_d = EEPROM.read(address_kons_d);
        kons_i = EEPROM.read(address_kons_i);
        pi = kons_p;
        di = kons_d;
        ai = kons_i;
        lcd.setCursor(0, 0);
        lcd.print("Kp:");
        lcd.print(pi);
        lcd.setCursor(0, 1);
        lcd.print("Kd:");
        lcd.print(di);
        lcd.setCursor(8, 0);
        lcd.print("Ki:");
        lcd.print(ai);
        while (!tombol1) {
          baca_button();
        }
        while (1) {
          baca_button();
          if (!tombol1 && indeks == 0) { //SETTING KP
            delay(200);
            pi++;
            if (pi > 255) {
              pi = 0;
            }
            lcd.setCursor(3, 0);
            lcd.print(pi);
            lcd.print("  ");
          }
          else if (!tombol3 && indeks == 0) {
            delay(200);
            pi--;
            if (pi < 0) {
              pi = 255;
            }
            lcd.setCursor(3, 0);
            lcd.print(pi);
            lcd.print("  ");
          }
          else if (!tombol2 && indeks == 0) {
            delay(200);
            EEPROM.write(address_kons_p, pi);
            delay(500);
            lcd.setCursor(8, 1);
            lcd.print("OK");
            delay(500);
            lcd.setCursor(8, 1);
            lcd.print("  ");
            indeks = 1;
            delay(500);
          }
          while (indeks == 1) {
            baca_button();
            if (!tombol1 && indeks == 1) { //SETTING KD
              delay(200);
              di++;
              if (di > 255) {
                di = 0;
              }
              lcd.setCursor(3, 1);
              lcd.print(di);
              lcd.print("  ");
            }
            else if (!tombol3 && indeks == 1) {
              delay(200);
              di--;
              if (di < 0) {
                di = 255;
              }
              lcd.setCursor(3, 1);
              lcd.print(di);
              lcd.print("  ");
            }
            else if (!tombol2 && indeks == 1) {
              delay(200);
              EEPROM.write(address_kons_d, di);
              delay(500);
              lcd.setCursor(8, 1);
              lcd.print("OK");
              indeks = 2;
              delay(500);
              lcd.setCursor(8, 1);
              lcd.print("OK");
              delay(500);
              lcd.setCursor(8, 1);
              lcd.print("  ");
            }
          }
          while (indeks == 2) {
            baca_button();
            if (!tombol1 && indeks == 2) { //SETTING KI
              delay(200);
              ai++;
              if (ai > 255) {
                ai = 0;
              }
              lcd.setCursor(11, 0);
              lcd.print(ai);
              lcd.print("  ");
            }
            else if (!tombol3 && indeks == 2) {
              delay(200);
              ai--;
              if (ai < 0) {
                ai = 255;
              }
              lcd.setCursor(11, 0);
              lcd.print(ai);
              lcd.print("  ");
            }
            else if (!tombol2 && indeks == 2) {
              delay(200);
              EEPROM.write(address_kons_i, ai);
              delay(500);
              indeks = 0;
              lcd.setCursor(8, 1);
              lcd.print("OK");
              delay(500);
              lcd.setCursor(8, 1);
              lcd.print("  ");
              delay(1000);
              lcd.clear();
              goto awal;
            }
          }
        }
      }
    }
  }
  else if (!tombol3) { //TEKAN TOMBOL 2.SENSOR
    delay(100);
    lcd.clear();
    kons_p = EEPROM.read(address_kons_p);
    kons_d = EEPROM.read(address_kons_d);
    kons_i = EEPROM.read(address_kons_i);
    kecepatan = EEPROM.read(address_speed);
    sens[0] = EEPROM.read(0);
    sens[1] = EEPROM.read(1);
    sens[2] = EEPROM.read(2);
    sens[3] = EEPROM.read(3);
    sens[4] = EEPROM.read(4);
    sens[5] = EEPROM.read(5);
    sens[6] = EEPROM.read(6);
    sens[7] = EEPROM.read(7);
    sens[8] = EEPROM.read(8);
    sens[9] = EEPROM.read(9);
    while (1) {
      tampil_all_sensor();
    }
  }
  else if (!tombol2) { //TEKAN TOMBOL 3.PLAY
    delay(100);
    kons_p = EEPROM.read(address_kons_p);
    kons_d = EEPROM.read(address_kons_d);
    kons_i = EEPROM.read(address_kons_i);
    kecepatan = EEPROM.read(address_speed);
    sens[0] = EEPROM.read(0);
    sens[1] = EEPROM.read(1);
    sens[2] = EEPROM.read(2);
    sens[3] = EEPROM.read(3);
    sens[4] = EEPROM.read(4);
    sens[5] = EEPROM.read(5);
    sens[6] = EEPROM.read(6);
    sens[7] = EEPROM.read(7);
    sens[8] = EEPROM.read(8);
    sens[9] = EEPROM.read(9);
    lcd.clear();
    delay(100);
    while (!tombol2) {
      baca_button();
      lcd.setCursor(0, 0);
      lcd.print("1. L FOLLOWER  ");
      lcd.setCursor(0, 1);
      lcd.print("2. L MAZE SOLVE");
      while (tombol1 && tombol3) {
        baca_button();
      }
      if (!tombol1) { //MENU UNTUK LINE FOLLOWER
        lcd.clear(); delay(200);
        while (!tombol1) {
          baca_button();
          lcd.setCursor(0, 0);
          lcd.print("1.Start ");
          lcd.setCursor(0, 1);
          lcd.print("2.Retry ");
          while (tombol1 && tombol3) {
            baca_button();
          }
          if (!tombol1) { //TEKAN TOMBOL START
            lcd.clear();
            delay(200);
            while (!tombol1) {
              baca_button();
              lcd.setCursor(0, 0);
              lcd.print("1.Start1 ");
              lcd.setCursor(0, 1);
              lcd.print("2.Start2 ");
              while (tombol1 && tombol3) {
                baca_button();
              }
              if (!tombol1) { //TEKAN TOMBOL START1
                lcd.clear();
                delay(200);
                while (!tombol1) { //ISI PROGRAM UNTUK START1
                  maju(kecepatan, kecepatan);
                  delay(300);
                  bulat_1();
                  bulat_2();
                  pertigaan_kiri();
                  pid_timer(17);
                  n_besar();
                  n_kecil();
                  /*huruf_v();
                  siku_kiri();
                  siku_kiri();
                  siku_kanan();*/
                  /*pid_timer(10);
                  tajam_kanan();
                  siku_kanan();
                  siku_kiri();
                  siku_kiri();
                  siku_kiri();
                  huruf_k();
                  pid_timer(5);
                  tajam_kanan_2();
                  siku_kanan();
                  siku_kiri();
                  siku_kiri();
                  pid_timer(27);
                  segitiga();
                  kapasitor();
                  kepala();
                  putus_putus(10);*/
                  while (1) {
                    stopped();
                  }
                }
              }
              else if (!tombol3) { //TEKAN TOMBOL START2
                lcd.clear();
                delay(200);
                while (!tombol3) { //ISI PROGRAM UNTUK START2
                  while (1) {
                    stopped();
                  }
                }
              }
            }
          }
          else if (!tombol3) { //TEKAN TOMBOL RETRY
            lcd.clear();
            delay(200);
            while (!tombol3) {
              baca_button();
              lcd.setCursor(0, 0);
              lcd.print("1.Retry1 ");
              lcd.setCursor(0, 1);
              lcd.print("2.Retry2 ");
              while (tombol1 && tombol3) {
                baca_button();
              }
              if (!tombol1) { //TEKAN TOMBOL RETRY1
                lcd.clear();
                delay(200);
                while (!tombol1) {
                  baca_button();
                  lcd.setCursor(0, 0);
                  lcd.print("1.CP1 ");
                  lcd.setCursor(0, 1);
                  lcd.print("2.CP2 ");
                  lcd.setCursor(8, 0);
                  lcd.print("3.CP3 ");
                  while (tombol1 && tombol2 && tombol3) {
                    baca_button();
                  }
                  if (!tombol1) {   //program untuk cek poin 1 retry 1 start 1
                    lcd.clear();
                    delay(200);
                    while (!tombol1) {
                      
                      pid(kecepatan);
                      
                    }
                  }
                  else if (!tombol3) { //program untuk cek poin 2 retry 1 start 1
                    lcd.clear();
                    delay(200);
                    while (!tombol3) {
                      maju(170,170);
                      delay(500);
                      while (1) {
                        stopped();
                      }
                    }
                  }
                  else if (!tombol2) { //program untuk cek poin 3 retry 1 start 1
                    lcd.clear();
                    delay(200);
                    while (!tombol2) {
                      mundur(220,220);
                      delay(500);
                      while (1) {
                        stopped();
                      }
                    }
                  }
                }
              }
              else if (!tombol3) { //TEKAN TOMBOL RETRY2
                lcd.clear();
                delay(200);
                while (!tombol3) {
                  baca_button();
                  lcd.setCursor(0, 0);
                  lcd.print("1.CP1 ");
                  lcd.setCursor(0, 1);
                  lcd.print("2.CP2 ");
                  lcd.setCursor(8, 0);
                  lcd.print("3.CP3 ");
                  while (tombol1 && tombol2 && tombol3) {
                    baca_button();
                  }
                  if (!tombol1) {   //program untuk cek poin 1 retry 2 start 2
                    lcd.clear();
                    delay(200);
                    while (!tombol1) {
                      pid_timer(5);
                      putus_putus(4);
                      stopped();delay(100);
                      siku_kiri();
                      stopped();delay(100);
                      siku_kiri();
                      stopped();delay(100);
                      pid_timer(130);
                      putus_putus(5);
                      pid_timer2(280);
                      while(1){
                        stopped();
                      }
                    }
                  }
                  else if (!tombol3) {   //program untuk cek poin 2 retry 2 start 2
                    lcd.clear();
                    delay(200);
                    while (!tombol3) {
                      ///ISI PROGRAM DISINI
                      pid(kecepatan);
                      
                    }
                  }
                  else if (!tombol2) {   //program untuk cek poin 3 retry 2 start 2
                    lcd.clear();
                    delay(200);
                    while (!tombol2) {
                      ///ISI PROGRAM DISINI
                      mundur(180,180);
                      delay(700);
                      while(1){
                        stopped();
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (!tombol3) { //MENU UNTUK LINE MAZE SOLVING
        lcd.clear(); delay(200);
        while (!tombol3) {
         
        }
      }
    }
  }
}
