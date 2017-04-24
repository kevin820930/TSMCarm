# angleroutplanning

This routplanning function is for scara armrobot to move linearly.

The function is:
</br>rout routplanning(double armbaselong,double arm2rate,double arm3rate,double angle1,double angle2,double angle3,double angle4,double distance,intpointsnum);
</br>-armbaselong:The length of first arm which is closest to origin.
</br>-arm2rate:The rate of second arm and firstarm.
</br>-arm3rate:The rate of third arm and firstarm.The third arm also is the end arm.
</br>-angle1:The angle of motor 1 which is locked at the origin.This angle is between the first axis and the horizontal plane.
</br>-angle2:The angle of motor 2 which control the scara armrobot to move up and down(Z axis).
</br>-angle3:The angle of motor 3 which is locked at the second arm and first arm .This angle is between the first arm and the second arm.
</br>-angle4:The angle of motor 4 which is locked at the second arm and third arm .This angle is between the third arm and the second arm.
</br>-distance:The distance you want to move in a straight line.
</br>-pointsnum:The number of point you want to use in the lagrange method.

</br>The "rout" struct is:
</br>typedef struct rout{
</br>    long double polynomial[100];
</br>}rout;
</br>With return of routplanning,you can call the polynomial array.
</br>The polynomial[0] represent the coefficient of x^0,polynomial[1] represent the coefficient of x^...and so on.

If your input data is correct,You will receive the reply like below.
</br>The fuction of first(x) and third(f(x)) motor angle:
</br>f(x)=-0.000000x^9+0.000000x^8-0.000000x^7+0.000000x^6-0.000017x^5+0.000552x^4-0.012342x^3+0.277067x^2-0.400424x^1+7.000000x^0

The angle of the motor 1,3,4 which are used in lagrange method are listed in the moveangle.txt file

Because the third arm move straightly,the angle change of motor 4 is equal to the angle change of motor 1 add motor 3,but positive and negative opposite.

**Notice
</br>The more number of points you enter to the lagrange function,the longer you will wait.
</br>Because of the range of "long double",the larger value and the more number of your data is,the accuracy will be reduced.
</br>According to my experience,the performance with 10 points is still good.

