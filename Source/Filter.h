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

//reflection filters coefficients values

//step_0 - 1.2 cm
const double B0r_0 = 0.00148875526585464;
const double B1r_0 = -0.00120708383241042;
const double B2r_0 = -0.00148190029224148;
const double B3r_0 = 0.00121393880602358;

const double A1r_0 = -2.89790633258181;
const double A2r_0 = 2.79802595323123;
const double A3r_0 = -0.900105910702194;

//step_1 - 1.3 cm
const double B0r_1 = 0.00335592831460436;
const double B1r_1 = -0.00277817344018852;
const double B2r_1 = -0.00334268955647620;
const double B3r_1 = 0.00279141219831668;

const double A1r_1 = -2.88825538503306;
const double A2r_1 = 2.77989104675777;
const double A3r_1 = -0.891609184208459;

//step_2 - 1.4 cm
const double B0r_2 = 0.00517270575773444;
const double B1r_2 = -0.00436824166171923;
const double B2r_2 = -0.00515548132738072;
const double B3r_2 = 0.00438546609207296;

const double A1r_2 = -2.87865489770775;
const double A2r_2 = 2.76156314738057;
const double A3r_2 = -0.882873800812105;

//step_3 - 1.5 cm
const double B0r_3 = 0.00694154483627482;
const double B1r_3 = -0.00597476665661756;
const double B2r_3 = -0.00692237672582804;
const double B3r_3 = 0.00599393476706433;

const double A1r_3 = -2.86910528623180;
const double A2r_3 = 2.74306469622661;
const double A3r_3 = -0.873921073773921;

//step_4 - 1.6 cm
const double B0r_4 = 0.00866475675339795;
const double B1r_4 = -0.00759543715065878;
const double B2r_4 = -0.00864533731394742;
const double B3r_4 = 0.00761485659010931;

const double A1r_4 = -2.85960675039235;
const double A2r_4 = 2.72441611016413;
const double A3r_4 = -0.864770520892871;

//step_5 - 1.7 cm
const double B0r_5 = 0.0103445175450547;
const double B1r_5 = -0.00922813353428962;
const double B2r_5 = -0.0103261959767865;
const double B3r_5 = 0.00924645510255783;

const double A1r_5 = -2.85015929946656;
const double A2r_5 = 2.70563596673260;
const double A3r_5 = -0.855440024129502;

//step_6 - 1.8 cm
const double B0r_6 = 0.0119828779968571;
const double B1r_6 = -0.0108709108283402;
const double B2r_6 = -0.0119666668108299;
const double B3r_6 = 0.0108871220143674;

const double A1r_6 = -2.84076277470616;
const double A2r_6 = 2.68674117057348;
const double A3r_6 = -0.845945973495265;

//step_7 - 1.9 cm
const double B0r_7 = 0.00836341467664481;
const double B1r_7 = -0.00771081517160211;
const double B2r_7 = -0.00835515175240575;
const double B3r_7 = 0.00771907809584116;

const double A1r_7 = -2.88259911416098;
const double A2r_7 = 2.76830119673105;
const double A3r_7 = -0.885685556721597;

//step_8 - 2.0 cm
const double B0r_8 = 0.00900195734508397;
const double B1r_8 = -0.00838163049001607;
const double B2r_8 = -0.00899386146161446;
const double B3r_8 = 0.00838972637348558;

const double A1r_8 = -2.88561377593316;
const double A2r_8 = 2.77407915692424;
const double A3r_8 = -0.888449189224143;

//step_9 - 2.1 cm
const double B0r_9 = 0.00969383015351482;
const double B1r_9 = -0.00910235464057830;
const double B2r_9 = -0.00968593989333203;
const double B3r_9 = 0.00911024490076109;

const double A1r_9 = -2.88827763754024;
const double A2r_9 = 2.77918335198401;
const double A3r_9 = -0.890889933923404;

//step_10 - 2.2 cm
const double B0r_10 = 0.0104428831033720;
const double B1r_10 = -0.00987777161476080;
const double B2r_10 = -0.0104352379207295;
const double B3r_10 = 0.00988541679740335;

const double A1r_10 = -2.89066491723660;
const double A2r_10 = 2.78375610909223;
const double A3r_10 = -0.893075901490345;

//step_11 - 2.3 cm
const double B0r_11 = 0.0112533756990923;
const double B1r_11 = -0.0107128762780108;
const double B2r_11 = -0.0112460156575885;
const double B3r_11 = 0.0107202363195145;

const double A1r_11 = -2.89283178576968;
const double A2r_11 = 2.78790514723905;
const double A3r_11 = -0.895058641386365;

//step_12 - 2.4 cm
const double B0r_12 = 0.0121299824661228;
const double B1r_12 = -0.0116129408030305;
const double B2r_12 = -0.0121229478695646;
const double B3r_12 = 0.0116199753995886;

const double A1r_12 = -2.89482161761424;
const double A2r_12 = 2.79171365153887;
const double A3r_12 = -0.896877964731514;

//step_13 - 2.5 cm
const double B0r_13 = 0.0130778078453958;
const double B1r_13 = -0.0125835707077660;
const double B2r_13 = -0.0130711387557259;
const double B3r_13 = 0.0125902397974359;

const double A1r_13 = -2.89666851198821;
const double A2r_13 = 2.79524702918906;
const double A3r_13 = -0.898565179021510;

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
    
    a1f_L(-4.4677580565408004),
    a2f_L(8.246432752710092),
    a3f_L(-8.0416864964928578),
    a4f_L(4.3658701352651246),
    a5f_L(-1.250157835645624),
    a6f_L(0.14742497350765946),
    b0f_L(0.0016473782482660101),
    b1f_L(-0.0017067348851367849),
    b2f_L(-0.0026667292888066523),
    b3f_L(0.0035067498850163384),
    b4f_L(0.00049099029470241347),
    b5f_L(-0.0017872423055908145),
    b6f_L(0.00054113344012696836),
    
    a1f_R(-4.4677580565408004),
    a2f_R(8.246432752710092),
    a3f_R(-8.0416864964928578),
    a4f_R(4.3658701352651246),
    a5f_R(-1.250157835645624),
    a6f_R(0.14742497350765946),
    b0f_R(0.0016473782482660101),
    b1f_R(-0.0017067348851367849),
    b2f_R(-0.0026667292888066523),
    b3f_R(0.0035067498850163384),
    b4f_R(0.00049099029470241347),
    b5f_R(-0.0017872423055908145),
    b6f_R(0.00054113344012696836)
    {initializeMatrix();};
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    inline double setLengt(float lengthInput) {
        return (double)((long)floor(lengthInput*100))/100; };
    
    inline double setDelayMilliseconds(double lengtInput) { return lengtInput/0.345; };
    
    inline double setDelaySamples(double delayMilliseconds) { return (double)(delayMilliseconds * (mSampleRate/1000)); };
    
    void setValues(float inputLength, double inputSize);
    
    void getCalculatedCoefficients(int side);
    
    void getCalculatedCoefficients_Ref(int side);
    
    void initializeMatrix(){
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

    }

    double a1f_L;
    double a2f_L;
    double a3f_L;
    double a4f_L;
    double a5f_L;
    double a6f_L;
    double b0f_L;
    double b1f_L;
    double b2f_L;
    double b3f_L;
    double b4f_L;
    double b5f_L;
    double b6f_L;
    
    double a1f_R;
    double a2f_R;
    double a3f_R;
    double a4f_R;
    double a5f_R;
    double a6f_R;
    double b0f_R;
    double b1f_R;
    double b2f_R;
    double b3f_R;
    double b4f_R;
    double b5f_R;
    double b6f_R;
    
    double a1f_Ref_L;
    double a2f_Ref_L;
    double a3f_Ref_L;
    double a4f_Ref_L;
    double a5f_Ref_L;
    double a6f_Ref_L;
    double b0f_Ref_L;
    double b1f_Ref_L;
    double b2f_Ref_L;
    double b3f_Ref_L;
    double b4f_Ref_L;
    double b5f_Ref_L;
    double b6f_Ref_L;
    
    double a1f_Ref_R;
    double a2f_Ref_R;
    double a3f_Ref_R;
    double a4f_Ref_R;
    double a5f_Ref_R;
    double a6f_Ref_R;
    double b0f_Ref_R;
    double b1f_Ref_R;
    double b2f_Ref_R;
    double b3f_Ref_R;
    double b4f_Ref_R;
    double b5f_Ref_R;
    double b6f_Ref_R;

    double **a_Ref;
    double **b_Ref;
    
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