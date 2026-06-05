#include <stdio.h>

#define DT        0.1f    // timestep (ms)
#define STEPS     500     // 500 × 0.1 = 50 ms total

#define V_REST   -70.0f   // resting voltage (mV)
#define V_TH     -55.0f   // spike threshold (mV)
#define TAU       20.0f   // membrane time constant (ms)
#define R         10.0f   // membrane resistance (MΩ)
#define T_REF      2.0f   // refractory period (ms)

int main(void) {
    float V       = V_REST;  // membrane voltage
    float t_ref   = 0.0f;    // refractory countdown

    for (int s = 0; s < STEPS; s++) {
        float t   = s * DT;
        float I   = (t >= 5.0f && t < 35.0f) ? 3.5f : 0.0f;  // input current (nA)
        int spike = 0;

        if (t_ref > 0.0f) {            
            V      = V_REST;
            t_ref -= DT;
        } else {                        
            V += (DT / TAU) * (-(V - V_REST) + R * I);

            if (V >= V_TH) {          
                spike = 1;
                V     = V_REST;
                t_ref = T_REF;
            }
        }

        if (s % 10 == 0)              
            printf("t=%5.1f ms | V=%7.2f mV | %s\n",
                   t, V, spike ? "SPIKE" : ".");
    }
}
