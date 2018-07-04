#include <SoftwareSerial.h>

int x=1 ;
int y ;
float grad;
String out;
String out2;
String out3 = "";
String out4 = "";
String out5 = "";
int inChar ;
int st1;
int dlin1;
int dlin2;
int spd;
int outspd;
int outputPin = 6;
int outPin = 3;



SoftwareSerial Serial_2(2, 3); // RX, TX

void setup()
{
    delay(500);
    Serial.begin(9600);
    Serial_2.begin(10400);

    char bytes8[] = {0x81,0x10,0xF1,0x82,0x04};
    Serial_2.print(bytes8);
    char inChar8 = Serial_2.read();
    Serial.write(inChar8);
    Serial_2.end();

    digitalWrite(outPin, HIGH);
    delay(350);
    digitalWrite(outPin, LOW);
    delay(25);
    digitalWrite(outPin, HIGH);
    delay(25);
//delayMicroseconds(600);

    Serial_2.begin(10400);

    char bytes7[] = {0x81,0x10,0xF1,0x81,0x03};
    Serial_2.print(bytes7);
    delay(200);

    char bytes9[] = {0x81,0x10,0xF1,0x81,0x03};
    Serial_2.print(bytes9);
    delay(20);
}

void loop()
{
    if (x==1) {

        char bytes3[] = {0x82,0x10,0xF1,0x21,0x01,0xA5};
        Serial_2.print(bytes3);
        char inChar5 = Serial_2.read();
        Serial.write(inChar5);

        x = 0;
    }

    y = 0;
    out2 = "";
    out = "";
    inChar=0;

    while (Serial_2.available())
    {
        inChar = Serial_2.read();
        y = int(inChar);
        out = String(inChar);

        if (y >= 100) {
            out2 = String(y);
        }

        if (y >= 10) {
            if (y <= 99) {
                out2 = "0" + out;
            }
        }

        if (y < 10) {
            out2 = "00" + out;
        }
        out3 = out3 + "," + out2;


        if (Serial_2.available() <= 0){
            String poi = "128,241,016,060";

            st1 = out3.indexOf(poi);
            x = 1;
            if (st1 > 0) {
                st1 = out3.indexOf(poi);
                out4 = out3.substring(st1);
                out5 = out4.substring(68,71);

                const int n = 10;
                char *f = new char[n];
                String s = out5;
                s.toCharArray(f,n);
                int spd = atoi(f);
// ...
                delete[] f;

                outspd = spd*40;

                if (outspd > 4500) {
                    digitalWrite(outputPin, HIGH);
                }
                if (outspd < 4500) {
                    digitalWrite(outputPin, LOW);
                }

                Serial.println(outspd);
            }
        }
    }
}



