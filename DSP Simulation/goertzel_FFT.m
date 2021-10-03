function pow = goertzel_FFT(data, k, N)
    omega = 2 * pi * k/N;
    cr = cos(omega);
    ci = sin(omega);
    coeff = 2 * cr;
    sprev = 0;
    sprev2 = 0;
    
    for i = 1:N
       s = data(i) + coeff * sprev - sprev2;
       sprev2 = sprev;
       sprev = s;
    end
    
    It = cr * sprev - sprev2;
    Qt = ci * sprev;
    
    omega2 = 2 * pi * k;
    cr2 = cos(omega2);
    ci2 = sin(omega2);
    
    I = It*cr2 + Qt*ci2;
    Q = -It*ci2 + Qt*cr2;
     
    pow = sqrt(I * I + Q * Q) * (2 / N);
    %pow = sprev2 * sprev2 + sprev * sprev - coeff * sprev * sprev2;
end