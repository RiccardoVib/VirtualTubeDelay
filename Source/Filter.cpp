/*
  ==============================================================================

    Filter.cpp
    Created: 17 Oct 2018 1:38:05pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

#include "Filter.h"


void Filter::process() {
    
        i_0 = ptr%7;       //->6
        i_1 = (ptr + 1)%7; //->0
        i_2 = (ptr + 2)%7; //->1
        i_3 = (ptr + 3)%7; //->2
        i_4 = (ptr + 4)%7; //->3
        i_5 = (ptr + 5)%7; //->4
        i_6 = (ptr + 6)%7; //->5
        
        if (--ptr < 0) { ptr += 7; }
    
        j_0 = ptr2%4;       //->3
        j_1 = (ptr2 + 1)%4; //->0
        j_2 = (ptr2 + 2)%4; //->1
        j_3 = (ptr2 + 3)%4; //->2
    
        if (--ptr2 < 0) { ptr2 += 4; }
}


void Filter::setValues(double tubeLength, double tubeSize) {
    
    double lengt = setLengt(tubeLength);
    //if(lengt > 30 || lengt < 2){lengt = 10;}
    long stepLength = floor(lengt);
        
    if (tubeSize <= 6){
        
        inc = (pow(0.85 + tubeSize*g12,(lengt)));
        Q1 = 0.65;
        fcLP = fcLP_0 + tubeSize*f12LP - (fLPValues[stepLength] + incValues[stepLength]*(lengt - floor(lengt)));
        
        if (lengt <= 15) {
            
            G1 = -1 - 0.85*(lengt-1);
            V1 = pow(10,(G1/20));
            fc1 = fc1_0 + tubeSize*f12 +(lengt-1)*30;
            
            G2 = -0.9-(lengt-1)*1;
            V2 = pow(10,(G2/20));
            fc2 = fc2_0 + tubeSize*f212 + (lengt-1)*50;
            Q2 = 0.5;
            
        }else{
            
            G1 = -12.9000-0.6*(lengt-15);
            V1 = pow(10,(G1/20));
            fc1 = 1620 + tubeSize*f12 + (lengt-15)*20;
            
            G2 = -14.9000-(lengt-15)*0.1;
            V2 = pow(10,(G2/20));
            fc2 = 2200 + tubeSize*f212;
            Q2 = 0.5 + (lengt-15)*0.02;
            
        }
        
    }else if(tubeSize >= 7){
        
        inc = (pow(0.87 + (tubeSize-7)*g23,(lengt)));
        Q1 = 0.65;
        fcLP = fcLP_1 + (tubeSize-7)*f23LP - (fLPValues[stepLength] + incValues[stepLength]*(lengt - floor(lengt)));
        
        if (lengt <= 15) {
            
            G1 = -1 - 0.85*(lengt-1);
            V1 = pow(10,(G1/20));
            fc1 = fc1_1 +(lengt-1)*30;
            
            G2 = -0.9 - (lengt-1)*1;
            V2 = pow(10,(G2/20));
            fc2 = fc2_1 + (lengt-1)*50;
            Q2 = 0.5;
            
        }else{
            
            G1 = -12.9000 - 0.6*(lengt-15);
            V1 = pow(10,(G1/20));
            fc1 = 1320 + (lengt-15)*20;
            
            G2 = -14.9000 - (lengt-15)*0.1;
            V2 = pow(10,(G2/20));
            fc2 = 7700;
            Q2 = 0.5 + (lengt-15)*0.02;
            
        }
        
    }
    
    //1st filter
    
    K1 = tan(mPI*fc1/mSampleRate);
    
    a1 = (2*(V1*K1*K1 - 1))/(1 + (sqrt(V1)*K1)/Q1 + V1*K1*K1);
    
    a2 = (1 - (sqrt(V1)*K1)/Q1 + V1*K1*K1)/(1 + (sqrt(V1)*K1)/Q1 + V1*K1*K1);
    
    b0 = V1*(1 + (K1)/Q1 + K1*K1) / (1 + (sqrt(V1)*K1)/Q1 + V1*K1*K1);
    
    b1 = (2*V1*(K1*K1 - 1)) / (1 + (sqrt(V1)*K1)/Q1 + V1*K1*K1);
    
    b2 = V1*(1 - (K1)/Q1 + K1*K1) / (1 + (sqrt(V1)*K1)/Q1 + V1*K1*K1);
    
    //2nd filter
    
    K2 = tan(mPI*fc2/mSampleRate);
    
    a11 = (2*(V2*K2*K2 - 1))/ (1 + (sqrt(V2)*K2)/Q2 + V2*K2*K2);
    
    a22 = (1 - (sqrt(V2)*K2)/Q2 + V2*K2*K2) / (1 + (sqrt(V2)*K2)/Q2 + V2*K2*K2);
    
    b00 =  V2*(1 + (K2)/Q2 + K2*K2) / (1 + (sqrt(V2)*K2)/Q2 + V2*K2*K2);
    
    b11 = (2*V2*(K2*K2 - 1)) / (1 + (sqrt(V2)*K2)/Q2 + V2*K2*K2);
    
    b22 = V2*(1 - (K2)/Q2 + K2*K2)/ (1 + (sqrt(V2)*K2)/Q2 + V2*K2*K2);
    
    //LP filter
    if (lengt < 2){
        
        KLP = tan(mPI*fcLP/mSampleRate);
        
        a2LP = 0;
        
        a1LP = (KLP-1)/(KLP+1);
        
        b0LP = KLP/(KLP+1);
        
        b1LP = KLP/(KLP+1);
        
        b2LP = 0;
        
    }else{
        
        KLP = tan(mPI*fcLP/mSampleRate);
        
        a2LP = pow(((KLP-1)/(KLP+1)),2);
        
        a1LP = 2*((KLP-1)/(KLP+1));
        
        b0LP = pow((KLP/(KLP+1)),2);
        
        b1LP = 2*(KLP/(KLP+1))*(KLP/(KLP+1));
        
        b2LP = pow((KLP/(KLP+1)),2);
        
    }
    
}

    


void Filter::getCalculatedCoefficients(int side) {

    if (side == 0) {
        
        
    //final
    
    a1f_L = a1LP  + a1 + a11;
    
    a2f_L = a2LP + a1 * a1LP + a2 + a11 * a1LP + a11 * a1 + a22;
    
    a3f_L = a1 * a2LP + a2 * a1LP + a11 * a2LP + a11 * a1 * a1LP + a11 * a2 + a22 * a1LP + a22 * a1;
    
    a4f_L = a2 * a2LP + a11 * a1 * a2LP + a11 * a2 * a1LP + a22 * a2LP + a22 * a1 * a1LP + a22 * a2;
    
    a5f_L = a11 * a2 * a2LP + a22 * a1 * a2LP + a22 * a2 * a1LP;
    
    a6f_L = a22 * a2LP * a2;
    
    b0f_L = inc*(b00 * b0 * b0LP);
    
    b1f_L = inc*(b00 * b0 * b1LP + b00 * b1 * b0LP + b11 * b0 * b0LP);
    
    b2f_L = inc*(b00 * b0 * b2LP + b00 * b1 * b1LP + b00 * b2 * b0LP + b11 * b0 * b1LP + b11 * b1 * b0LP + b0 * b0LP * b22);
    
    b3f_L = inc*(b00 * b1 * b2LP + b00 * b2 * b1LP + b11 * b0 * b2LP + b11 * b1 * b1LP + b11 * b2 * b0LP + b22 * b1 * b0LP + b22 * b0 * b1LP);
    
    b4f_L = inc*(b2 * b2LP * b00 + b11 * b1 * b2LP + b11 * b2 * b1LP + b2 * b0LP * b22 + b22 * b1 * b1LP + b22 * b0 * b2LP);
    b5f_L = inc*(b11 * b2 * b2LP + b22 * b2 * b1LP + b22 * b1 * b2LP);
    
    b6f_L = inc*(b22 * b2 * b2LP);
        
        
    }else{
    
        //final
        
        a1f_R = a1LP  + a1 + a11;
        
        a2f_R = a2LP + a1 * a1LP + a2 + a11 * a1LP + a11 * a1 + a22;
        
        a3f_R = a1 * a2LP + a2 * a1LP + a11 * a2LP + a11 * a1 * a1LP + a11 * a2 + a22 * a1LP + a22 * a1;
        
        a4f_R = a2 * a2LP + a11 * a1 * a2LP + a11 * a2 * a1LP + a22 * a2LP + a22 * a1 * a1LP + a22 * a2;
        
        a5f_R = a11 * a2 * a2LP + a22 * a1 * a2LP + a22 * a2 * a1LP;
        
        a6f_R = a22 * a2LP * a2;
        
        b0f_R = inc*(b00 * b0 * b0LP);
        
        b1f_R = inc*(b00 * b0 * b1LP + b00 * b1 * b0LP + b11 * b0 * b0LP);
        
        b2f_R = inc*(b00 * b0 * b2LP + b00 * b1 * b1LP + b00 * b2 * b0LP + b11 * b0 * b1LP + b11 * b1 * b0LP + b0 * b0LP * b22);
        
        b3f_R = inc*(b00 * b1 * b2LP + b00 * b2 * b1LP + b11 * b0 * b2LP + b11 * b1 * b1LP + b11 * b2 * b0LP + b22 * b1 * b0LP + b22 * b0 * b1LP);
        
        b4f_R = inc*(b2 * b2LP * b00 + b11 * b1 * b2LP + b11 * b2 * b1LP + b2 * b0LP * b22 + b22 * b1 * b1LP + b22 * b0 * b2LP);
        b5f_R = inc*(b11 * b2 * b2LP + b22 * b2 * b1LP + b22 * b1 * b2LP);
        
        b6f_R = inc*(b22 * b2 * b2LP);
        
    }
}


void Filter::getCalculatedCoefficients_Ref(int side) {
    
    if (side == 0) {
        
        
        //final
        
        a1f_Ref_L = a1LP  + a1 + a11;
        
        a2f_Ref_L = a2LP + a1 * a1LP + a2 + a11 * a1LP + a11 * a1 + a22;
        
        a3f_Ref_L = a1 * a2LP + a2 * a1LP + a11 * a2LP + a11 * a1 * a1LP + a11 * a2 + a22 * a1LP + a22 * a1;
        
        a4f_Ref_L = a2 * a2LP + a11 * a1 * a2LP + a11 * a2 * a1LP + a22 * a2LP + a22 * a1 * a1LP + a22 * a2;
        
        a5f_Ref_L = a11 * a2 * a2LP + a22 * a1 * a2LP + a22 * a2 * a1LP;
        
        a6f_Ref_L = a22 * a2LP * a2;
        
        b0f_Ref_L = inc*(b00 * b0 * b0LP);
        
        b1f_Ref_L = inc*(b00 * b0 * b1LP + b00 * b1 * b0LP + b11 * b0 * b0LP);
        
        b2f_Ref_L = inc*(b00 * b0 * b2LP + b00 * b1 * b1LP + b00 * b2 * b0LP + b11 * b0 * b1LP + b11 * b1 * b0LP + b0 * b0LP * b22);
        
        b3f_Ref_L = inc*(b00 * b1 * b2LP + b00 * b2 * b1LP + b11 * b0 * b2LP + b11 * b1 * b1LP + b11 * b2 * b0LP + b22 * b1 * b0LP + b22 * b0 * b1LP);
        
        b4f_Ref_L = inc*(b2 * b2LP * b00 + b11 * b1 * b2LP + b11 * b2 * b1LP + b2 * b0LP * b22 + b22 * b1 * b1LP + b22 * b0 * b2LP);
        b5f_Ref_L = inc*(b11 * b2 * b2LP + b22 * b2 * b1LP + b22 * b1 * b2LP);
        
        b6f_Ref_L = inc*(b22 * b2 * b2LP);
        
        
    }else{
        
        //final
        
        a1f_Ref_R = a1LP  + a1 + a11;
        
        a2f_Ref_R = a2LP + a1 * a1LP + a2 + a11 * a1LP + a11 * a1 + a22;
        
        a3f_Ref_R = a1 * a2LP + a2 * a1LP + a11 * a2LP + a11 * a1 * a1LP + a11 * a2 + a22 * a1LP + a22 * a1;
        
        a4f_Ref_R = a2 * a2LP + a11 * a1 * a2LP + a11 * a2 * a1LP + a22 * a2LP + a22 * a1 * a1LP + a22 * a2;
        
        a5f_Ref_R = a11 * a2 * a2LP + a22 * a1 * a2LP + a22 * a2 * a1LP;
        
        a6f_Ref_R = a22 * a2LP * a2;
        
        b0f_Ref_R = inc*(b00 * b0 * b0LP);
        
        b1f_Ref_R = inc*(b00 * b0 * b1LP + b00 * b1 * b0LP + b11 * b0 * b0LP);
        
        b2f_Ref_R = inc*(b00 * b0 * b2LP + b00 * b1 * b1LP + b00 * b2 * b0LP + b11 * b0 * b1LP + b11 * b1 * b0LP + b0 * b0LP * b22);
        
        b3f_Ref_R = inc*(b00 * b1 * b2LP + b00 * b2 * b1LP + b11 * b0 * b2LP + b11 * b1 * b1LP + b11 * b2 * b0LP + b22 * b1 * b0LP + b22 * b0 * b1LP);
        
        b4f_Ref_R = inc*(b2 * b2LP * b00 + b11 * b1 * b2LP + b11 * b2 * b1LP + b2 * b0LP * b22 + b22 * b1 * b1LP + b22 * b0 * b2LP);
        b5f_Ref_R = inc*(b11 * b2 * b2LP + b22 * b2 * b1LP + b22 * b1 * b2LP);
        
        b6f_Ref_R = inc*(b22 * b2 * b2LP);
        
    }
}
