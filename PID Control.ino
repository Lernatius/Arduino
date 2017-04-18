void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
  // A Complete PID Function that can become P-PD-PI just by setting coefficients
  
        double Input, SetPoint, Output, virtualOut; // Input : motor hızı, setpoint: hedeflene hız değeri, Output : çıkış değeri
        double Kp, Ki, Kd; // PID coefficients
        double SampleTime;  // sampling time 1/frequency
        double error, integral, derivative;
        double outMin = 0, outMax = 255, Imax = 255, Imin = 0;   
        double lastOut, lastIn;
        
        void Compute() 
        {
            error = SetPoint - Input;  //Calculate error

            integral += (error * SampleTime);
            if (integral > Imax) { integral = Imax; }
            else if ( integral < Imin) { integral = Imin; } // Anti windup proces

            derivative = (Input - lastIn) / SampleTime;   // prevents derivative kick 

            virtualOut = Kp * error + Ki * integral - Kd * derivative;

            if (virtualOut >= outMax) { virtualOut = outMax; }
            else if (virtualOut <= outMin) { virtualOut = outMin; }

            Output = virtualOut;
            lastIn = Input;

 
        }
