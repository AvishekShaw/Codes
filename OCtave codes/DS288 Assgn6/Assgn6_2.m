# This code is to approximate the solution to the equation y'=3y by 
# Adams fourth order predictor corrector methods

#a=start point, b=end point, N= no. of intervals, f is the solution to the\
# equation, h = step size, w0= starting value, w1=2nd value obtained from 
# the analytic equation.
clear
clc
g=@(t) 50*exp(-3*t);
f=@(y) -3*y

a=0;b=10;N=100;h=(b-a)/N;
w0=50;w1=g(h);w(1)=w0;w(2)=w1;
T(1)=0;T(2)=h; 
Exact(1)=g(0);Exact(2)=g(h);
for i=3:1:N
  t=a+i*h;
  T(i)=t;
  Exact(end+1)=g(t); 
  W=w1+0.5*h*(3*f(w1)-f(w0));
  W=w1+h*(5*f(W)+8*f(w1)-f(w0))/12;
  w(end+1)=W;
  w0=w1;
  w1=W;
endfor
w(end)
Exact(end)
#plot of error
#plot(T,abs(1-w./Exact),'-r','linewidth',3)
plot(T,w,'-b','linewidth',3)
xlabel("t","Fontsize",20)
ylabel("y(t)","Fontsize",20)
title("Plot of y(t) vs t for h= 1/2 ","Fontsize",25)
set(gca,'fontsize',20)