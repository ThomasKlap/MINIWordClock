//show

void show()
{
for (int i=0; i <= 255; i++){
    mx.setRow(1, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(2, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(3, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(4, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(5, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(6, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(7, i, 1);
    delay(10);  }
  for (int i=0; i <= 255; i++){
    mx.setRow(8, i, 1);
    delay(10);  }
    delay(100);
    mx.displayOff();
    delay(100);
    mx.displayOn();
    delay(100);
    mx.clear();
}