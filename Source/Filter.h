/*
  ==============================================================================

    Filter.h
    Created: 17 Oct 2018 1:37:13pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#ifndef Filter_hpp
#define Filter_hpp

//#include <cmath>
#include <math.h>
#include <tgmath.h>

const double mPI = 2*acos(0.0);

//propagation filter parameters values

const double f12 = -42.8571428571429; const double f12LP = 100;
const double g12 = 0.00285714285714286; const double f212 = 785.714285714286;
const double g23 = 0.00500000000000000; const double f23LP = 133.333333333333;
const double fc1_0 = 1200; const double fcLP_0 = 9500; const double fc2_0 = 1500;
const double fc1_1 = 900; const double fcLP_1 = 10200; const double fc2_1 = 7000;


//decrement steps for LP filters
const int fLPValues[36] = {0, 0, 850, 1700, 2700, 3500, 4000, 4500, 4900, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6700, 7000, 7300, 7500, 7700, 7800, 7950, 8050, 8150, 8250, 8350, 8400, 8500, 8550, 8600, 8650, 8690, 8750, 8770, 8900};

const double incValues[36] = {8.5, 8.5, 8.5, 10, 8, 5, 5, 4, 3, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 1, 1.5, 0.5, 1, 1, 1, 0.5, 1, 1.5, 0.5, 0.5, 0.4, 0.6, 1.3, 0};

class Filter {
public:
    
    Filter() :
    
    Q1(0.65000000000000002),
    fcLP(4100.0),
    G1(-8.6499999999999985),
    V1(0.36940264435828352),
    fc1(1470.0),
    G2(-9.9000000000000003),
    V2(0.31988951096913981),
    fc2(1950.0),
    Q2(0.5),
    inc(0.19687440434072259),
    
    K1(0.10201843500792108),
    a1(-1.8124480755856778),
    a2(0.82643833647869547),
    b0(0.39229522156127944),
    b1(-0.66511200112149416),
    b2(0.28680704045323241),
    K2(0.19739200480919947),
    a11(-1.5982791189070777),
    a22(0.63862403548359614),
    b00(0.37114398154063555),
    b11(-0.49755322526799012),
    b22(0.16675416030387299),
    KLP(0.30845914892734089),
    a2LP(0.27932856083050811),
    a1LP(-1.0570308620480446),
    b0LP(0.05557442469561584),
    b1LP(0.11114884939123168),
    b2LP(0.05557442469561584),
    
    a1f(-4.4677580565408004),
    a2f(8.246432752710092),
    a3f(-8.0416864964928578),
    a4f(4.3658701352651246),
    a5f(-1.250157835645624),
    a6f(0.14742497350765946),
    b0f(0.0016473782482660101),
    b1f(-0.0017067348851367849),
    b2f(-0.0026667292888066523),
    b3f(0.0035067498850163384),
    b4f(0.00049099029470241347),
    b5f(-0.0017872423055908145),
    b6f(0.00054113344012696836){};
    //{initializeMatrix();};
    
    ~Filter(){};
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    inline double setLengt(float lengthInput) {
        return (double)((long)floor(lengthInput*100))/100; };
    
    inline double setDelayMilliseconds(double lengtInput) { return lengtInput/0.345; };
    
    inline double setDelaySamples(double delayMilliseconds) { return (double)(delayMilliseconds * (mSampleRate/1000)); };
    
    void setValues(float inputLength, double inputSize);
    
    void getCalculatedCoefficients();
    
   /* void initializeMatrix(){
        //reflection filter coefficients matrix
        a_Ref = new double*[14];
        for (int i = 0; i < 14; ++i) {
            a_Ref[i] = new double[4];
        }
        b_Ref = new double*[14];
        for (int i = 0; i < 14; ++i) {
            b_Ref[i] = new double[3];
        }
        //step_0 - 1.2 cm
        b_Ref[0][0] = B0r_0;
        b_Ref[0][1] = B1r_0;
        b_Ref[0][2] = B2r_0;
        b_Ref[0][3] = B3r_0;
        
        a_Ref[0][0] = A1r_0;
        a_Ref[0][1] = A2r_0;
        a_Ref[0][2] = A3r_0;
        
        //step_1 - 1.3 cm
        b_Ref[1][0] = B0r_1;
        b_Ref[1][1] = B1r_1;
        b_Ref[1][2] = B2r_1;
        b_Ref[1][3] = B3r_1;
        
        a_Ref[1][0] = A1r_1;
        a_Ref[1][1] = A2r_1;
        a_Ref[1][2] = A3r_1;
        
        //step_2 - 1.4 cm
        b_Ref[2][0] = B0r_2;
        b_Ref[2][1] = B1r_2;
        b_Ref[2][2] = B2r_2;
        b_Ref[2][3] = B3r_2;
        
        a_Ref[2][0] = A1r_2;
        a_Ref[2][1] = A2r_2;
        a_Ref[2][2] = A3r_2;
        
        //step_3 - 1.5 cm
        b_Ref[3][0] = B0r_3;
        b_Ref[3][1] = B1r_3;
        b_Ref[3][2] = B2r_3;
        b_Ref[3][3] = B3r_3;
        
        a_Ref[3][0] = A1r_3;
        a_Ref[3][1] = A2r_3;
        a_Ref[3][2] = A3r_3;
        
        //step_4 - 1.6 cm
        b_Ref[4][0] = B0r_4;
        b_Ref[4][1] = B1r_4;
        b_Ref[4][2] = B2r_4;
        b_Ref[4][3] = B3r_4;
        
        a_Ref[4][0] = A1r_4;
        a_Ref[4][1] = A2r_4;
        a_Ref[4][2] = A3r_4;
        
        //step_5 - 1.7 cm
        b_Ref[5][0] = B0r_5;
        b_Ref[5][1] = B1r_5;
        b_Ref[5][2] = B2r_5;
        b_Ref[5][3] = B3r_5;
        
        a_Ref[5][0] = A1r_5;
        a_Ref[5][1] = A2r_5;
        a_Ref[5][2] = A3r_5;
        
        //step_6 - 1.8 cm
        b_Ref[6][0] = B0r_6;
        b_Ref[6][1] = B1r_6;
        b_Ref[6][2] = B2r_6;
        b_Ref[6][3] = B3r_6;
        
        a_Ref[6][0] = A1r_6;
        a_Ref[6][1] = A2r_6;
        a_Ref[6][2] = A3r_6;
        
        //step_7 - 1.9 cm
        b_Ref[7][0] = B0r_7;
        b_Ref[7][1] = B1r_7;
        b_Ref[7][2] = B2r_7;
        b_Ref[7][3] = B3r_7;
        
        a_Ref[7][0] = A1r_7;
        a_Ref[7][1] = A2r_7;
        a_Ref[7][2] = A3r_7;
        
        //step_8 - 2.0 cm
        b_Ref[8][0] = B0r_8;
        b_Ref[8][1] = B1r_8;
        b_Ref[8][2] = B2r_8;
        b_Ref[8][3] = B3r_8;
        
        a_Ref[8][0] = A1r_8;
        a_Ref[8][1] = A2r_8;
        a_Ref[8][2] = A3r_8;
        
        //step_9 - 2.1 cm
        b_Ref[9][0] = B0r_9;
        b_Ref[9][1] = B1r_9;
        b_Ref[9][2] = B2r_9;
        b_Ref[9][3] = B3r_9;
        
        a_Ref[9][0] = A1r_9;
        a_Ref[9][1] = A2r_9;
        a_Ref[9][2] = A3r_9;
        
        //step_10 - 2.2 cm
        b_Ref[10][0] = B0r_10;
        b_Ref[10][1] = B1r_10;
        b_Ref[10][2] = B2r_10;
        b_Ref[10][3] = B3r_10;
        
        a_Ref[10][0] = A1r_10;
        a_Ref[10][1] = A2r_10;
        a_Ref[10][2] = A3r_10;
        
        //step_11 - 2.3 cm
        b_Ref[11][0] = B0r_11;
        b_Ref[11][1] = B1r_11;
        b_Ref[11][2] = B2r_11;
        b_Ref[11][3] = B3r_11;
        
        a_Ref[11][0] = A1r_11;
        a_Ref[11][1] = A2r_11;
        a_Ref[11][2] = A3r_11;
        
        //step_11 - 2.4 cm
        b_Ref[12][0] = B0r_12;
        b_Ref[12][1] = B1r_12;
        b_Ref[12][2] = B2r_12;
        b_Ref[12][3] = B3r_12;
        
        a_Ref[12][0] = A1r_12;
        a_Ref[12][1] = A2r_12;
        a_Ref[12][2] = A3r_12;
        
        //step_12 - 2.5 cm
        b_Ref[13][0] = B0r_13;
        b_Ref[13][1] = B1r_13;
        b_Ref[13][2] = B2r_13;
        b_Ref[13][3] = B3r_13;
        
        a_Ref[13][0] = A1r_13;
        a_Ref[13][1] = A2r_13;
        a_Ref[13][2] = A3r_13;

    }*/

    double a1f;
    double a2f;
    double a3f;
    double a4f;
    double a5f;
    double a6f;
    double b0f;
    double b1f;
    double b2f;
    double b3f;
    double b4f;
    double b5f;
    double b6f;
    
    //double **a_Ref;
    //double **b_Ref;
    
private:
    
    double Q1;
    double fcLP;
    double G1;
    double V1;
    double fc1;
    double G2;
    double V2;
    double fc2;
    double Q2;
    
    double inc;
    
    double K1;
    double a1;
    double a2;
    double b0;
    double b1;
    double b2;
    double K2;
    double a11;
    double a22;
    double b00;
    double b11;
    double b22;
    
    double KLP;
    double a2LP;
    double a1LP;
    double b0LP;
    double b1LP;
    double b2LP;
    
    double mSampleRate;

};

#endif /* Filter_hpp */