#define   Emm42_En_Pin     8   // the number of the Emm42_En_pin
#define   Emm42_Stp_Pin    2   // the number of the Emm42_Stp_pin
#define   Emm42_Dir_Pin    5   // the number of the Emm42_Dir_pin


long i = 0, j = 0;  bool cntDir = false;
void moveto(long a){
  while(a){
  a--;

  delayMicroseconds(1200); //600us
  digitalWrite(Emm42_Stp_Pin, !digitalRead(Emm42_Stp_Pin));
  digitalWrite(Emm42_Dir_Pin, HIGH);

}
}

void moveto2(int a){
  while(a){
  a--;

  delayMicroseconds(300); //600us
  digitalWrite(Emm42_Stp_Pin, !digitalRead(Emm42_Stp_Pin));
  digitalWrite(Emm42_Dir_Pin, LOW);

}
}

void setup() {
  // put your setup code here, to run once:
  pinMode(Emm42_En_Pin , OUTPUT);  digitalWrite(Emm42_En_Pin , LOW);  // initialize the Emm42_En_Pin as an output
  pinMode(Emm42_Stp_Pin, OUTPUT);  digitalWrite(Emm42_Stp_Pin, LOW);  // initialize the Emm42_Stp_Pin as an output
  pinMode(Emm42_Dir_Pin, OUTPUT);  digitalWrite(Emm42_Dir_Pin, LOW);  // initialize the Emm42_Dir_Pin as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  while(1){
    moveto(2133);
    delay(4000);
    moveto(2133);
    delay(4000);
    moveto(2134);
    delay(4000);
  }



/**********************************************************
***  记录IO取反次数（IO取反次数 = 2倍的脉冲数）
**********************************************************/
  //if(cntDir)  {--i;}  else  {++i;}

/**********************************************************
***  控制PA6（Stp引脚）取反了6400次，即发送了3200个脉冲
*** 16细分下，发送3200个脉冲电机转动一圈（1.8度电机）
*** 所以计数到6400即电机旋转了一圈后，现在开始切换方向
**********************************************************/
//  if(i >= 6400)
//  {
//    /* 延时1秒 */
//    delay(1000);
//    /* 改变PA7（Dir引脚）电平，切换到逆时针方向转动 */
//    digitalWrite(Emm42_Dir_Pin, HIGH);  cntDir = true;
//  }
//  else if(i == 0)
//  {
//    /* 延时1秒 */
//    delay(1000);
//    /* 改变PA7（Dir引脚）电平切换到顺时针方向转动 */
//    digitalWrite(Emm42_Dir_Pin, LOW);  cntDir = false;
//  }
}
