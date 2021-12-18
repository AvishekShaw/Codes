#Assgn 6, Q1
clear
output_precision(16)
# System Parameters
a1=0.1;a2=0.1;b1=8*power(10,-7);b2=8*power(10,-7);c1=power(10,-6);c2=power(10,-7);
f=@(n1,n2) [n1*(a1-b1*n1-c1*n2); n2*(a2-b2*n2 -c2*n1)];

#m=no. of equations; N= no. of time intervals; a,b =start and end points resp.
#init=array of initial conditions.
m=2;N=10*2^7;a=0;b=10;init=[power(10,5),power(10,5)];
n1(1)=init(1);n2(1)=init(2); #n1 and n2 are the arrays storing values at different t
#h=time step size,t=current instant of time, T is the iterator which stores the time values
h=(b-a)/N;t=a;T(1)=a;
for j=1:1:m
  w(j)=init(j);
endfor
for i=1:1:N
  for j=1:1:m
    k1(j)=h*f(w(1),w(2))(j);
  endfor
  for j=1:1:m
    k2(j)=h*f((w(1)+0.5*k1(1)),(w(2)+0.5*k1(2)))(j);
  endfor
  for j=1:1:m
    k3(j)=h*f((w(1)+0.5*k2(1)),w(2)+0.5*k2(2))(j);
  endfor
  for j=1:1:m
    k4(j)=h*f((w(1)+k3(1)),w(2)+k3(2))(j);
  endfor
  for j=1:1:m
    w(j)=w(j)+(k1(j)+2*k2(j)+2*k3(j)+k4(j))/6;
  endfor
  t=a+i*h;
  T(end+1)=t;
  n1(end+1)=w(1);
  n2(end+1)=w(2);
endfor

plot(T,n1,'-b',T,n2,'-r')
xlabel("T (in years)","Fontsize",20)
ylabel("N1(t)/N2(t)","Fontsize",20)
title("Plot of N1(t) and N2(t) with time","Fontsize",25)
set(gca,'fontsize',20)
legend('N1(t)','N2(t)')
n1(end)
n2(end)

