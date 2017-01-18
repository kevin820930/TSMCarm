#ifndef _STRAIGHT_H
#define _STRAIGHT_H

/*point style */
typedef struct POINT {
    double xpoint;
    double ypoint;
    double zpoint;
} point;

typedef struct ARM {
    double longbase;
    double longrate2;
    double longrate3;
    double vector[2];
} arm;

typedef struct MOTOR {
    double anglerate1;
    double anglerate2;
    double anglerate3;
} motor;

point calcu(point *orig,point *endaxis,arm *myarm,double  distance);
void *move(motor mymotor);

#endif

