xvars := [u(t), v(t), omega(t), phi(t), delta(t), Yr(t), Yf(t), phi_dot(t), 
delta_dot(t)];
uvars := [tau(t), Xr(t), Xf(t)];
fo_eqns := [m*diff(u(t),t)-m*diff(omega(t),t)*sin(phi(t))*h-2*m*omega(t)*cos(
phi(t))*phi_dot(t)*h-Xf(t)-Xr(t)+kD*u(t)^2, -phi_dot(t)^2*sin(phi(t))*h*m+cos(
phi(t))*diff(phi_dot(t),t)*h*m-Yf(t)-Yr(t)-delta(t)*cos(epsilon)/cos(phi(t))*
Xf(t)+m*diff(v(t),t)+m*omega(t)*u(t), -cos(phi(t))*delta_dot(t)*sin(epsilon)/
rf*u(t)*iwf+delta(t)*phi_dot(t)*sin(epsilon)/rf*u(t)*sin(phi(t))*iwf-cos(phi(t
))*delta(t)*sin(epsilon)/rf*diff(u(t),t)*iwf-2*cos(phi(t))*omega(t)*Ifz*
phi_dot(t)*cos(epsilon)^2*sin(phi(t))+diff(omega(t),t)*Iy-cos(phi(t))^2*diff(
omega(t),t)*iwf+diff(omega(t),t)*iwf+Yf(t)*b-Yf(t)*w+cos(phi(t))^2*diff(omega(
t),t)*Iz-cos(phi(t))^2*diff(omega(t),t)*Iy+diff(omega(t),t)*iwr-cos(phi(t))^2*
diff(omega(t),t)*iwr-cos(phi(t))*Cxz*diff(phi_dot(t),t)+Cxz*phi_dot(t)^2*sin(
phi(t))-Xf(t)*sin(phi(t))*h-sin(phi(t))*Xr(t)*h-cos(phi(t))*delta(t)*Xf(t)*an+
cos(phi(t))^2*diff(omega(t),t)*Ifz*cos(epsilon)^2+cos(phi(t))*cos(epsilon)*Ifz
*diff(delta_dot(t),t)+b*Yr(t)-delta_dot(t)*Ifz*phi_dot(t)*cos(epsilon)*sin(phi
(t))-delta_dot(t)*phi_dot(t)*cos(epsilon)*sin(phi(t))*iwf+cos(phi(t))*cos(
epsilon)*Ifz*diff(phi_dot(t),t)*sin(epsilon)-sin(phi(t))*phi_dot(t)^2*cos(
epsilon)*Ifz*sin(epsilon)-cos(phi(t))*phi_dot(t)*iwr/rr*u(t)-cos(phi(t))*iwf*
phi_dot(t)/rf*u(t)-cos(phi(t))*delta(t)*phi_dot(t)^2*cos(epsilon)*iwf+2*cos(
phi(t))*omega(t)*Iy*phi_dot(t)*sin(phi(t))-2*cos(phi(t))*omega(t)*Iz*phi_dot(t
)*sin(phi(t))+2*cos(phi(t))*omega(t)*phi_dot(t)*sin(phi(t))*iwf+2*cos(phi(t))*
omega(t)*phi_dot(t)*sin(phi(t))*iwr-sin(phi(t))*iwr/rr*diff(u(t),t)-iwf*sin(
phi(t))/rf*diff(u(t),t)+1/cos(phi(t))*delta(t)*Xf(t)*cos(epsilon)*b-1/cos(phi(
t))*delta(t)*Xf(t)*cos(epsilon)*w-delta(t)*cos(epsilon)*diff(phi_dot(t),t)*sin
(phi(t))*iwf, -Ifz*cos(epsilon)^2*diff(phi_dot(t),t)+sin(epsilon)*Ifz*diff(
delta_dot(t),t)+Ifz*diff(phi_dot(t),t)+Ix*diff(phi_dot(t),t)-sin(phi(t))*h*g*m
-delta(t)/w*cos(phi(t))*an*b*g*m+delta(t)/rf/w*cos(phi(t))*an*iwf*diff(u(t),t)
+delta(t)/rr/w*cos(phi(t))*an*iwr*diff(u(t),t)+delta(t)/w*cos(phi(t))*an*Xf(t)
*h+delta(t)/w*cos(phi(t))*an*Xr(t)*h-diff(omega(t),t)*Cxz*cos(phi(t))+Yf(t)*
cos(phi(t))*h+delta(t)*Xf(t)*cos(epsilon)*h+cos(epsilon)*delta_dot(t)*iwf/rf*u
(t)+cos(phi(t))*Yr(t)*h+sin(epsilon)*Ifz*cos(phi(t))*cos(epsilon)*diff(omega(t
),t)+omega(t)*cos(phi(t))*iwr/rr*u(t)+omega(t)*iwf/rf*u(t)*cos(phi(t))+delta(t
)*cos(epsilon)/rf*diff(u(t),t)*iwf, cos(phi(t))*delta(t)/rf/w*sin(epsilon)*an*
iwf*diff(u(t),t)+1/cos(phi(t))*delta(t)/w*cos(epsilon)^2*b*g*m*rf+cos(phi(t))*
delta(t)/rr/w*cos(epsilon)^2*iwr*diff(u(t),t)*rf-cos(phi(t))*delta(t)/w*sin(
epsilon)*an*b*g*m-cos(phi(t))*delta(t)/w*cos(epsilon)^2*b*g*m*rf-1/cos(phi(t))
*delta(t)/rr/w*cos(epsilon)^2*iwr*diff(u(t),t)*rf+cos(phi(t))*delta(t)/rr/w*
sin(epsilon)*an*iwr*diff(u(t),t)+cos(phi(t))*an*Yf(t)-1/w*sin(phi(t))*an*b*g*m
+1/rf/w*sin(phi(t))*an*iwf*diff(u(t),t)+1/rr/w*sin(phi(t))*an*iwr*diff(u(t),t)
+cos(phi(t))*delta(t)/w*cos(epsilon)^2*Xf(t)*h*rf+cos(phi(t))*delta(t)/w*cos(
epsilon)^2*Xr(t)*h*rf+cos(phi(t))*delta(t)/w*sin(epsilon)*an*Xf(t)*h+cos(phi(t
))*delta(t)/w*sin(epsilon)*an*Xr(t)*h-1/cos(phi(t))*delta(t)/w*cos(epsilon)^2*
Xf(t)*h*rf-1/cos(phi(t))*delta(t)/w*cos(epsilon)^2*Xr(t)*h*rf+1/w*sin(phi(t))*
an*Xf(t)*h+1/w*sin(phi(t))*an*Xr(t)*h+cos(phi(t))*delta(t)/w*cos(epsilon)^2*
iwf*diff(u(t),t)-1/cos(phi(t))*delta(t)/w*cos(epsilon)^2*iwf*diff(u(t),t)+cos(
phi(t))*omega(t)*sin(epsilon)/rf*u(t)*iwf+Ifz*sin(epsilon)*diff(phi_dot(t),t)-
delta(t)*cos(epsilon)^2*phi_dot(t)^2*iwf+Ifz*diff(delta_dot(t),t)+Cdelta*
delta_dot(t)-tau(t)+cos(phi(t))*cos(epsilon)*Ifz*diff(omega(t),t)-cos(epsilon)
*iwf/rf*u(t)*phi_dot(t)-omega(t)*Ifz*phi_dot(t)*cos(epsilon)*sin(phi(t))+omega
(t)*phi_dot(t)*cos(epsilon)*sin(phi(t))*iwf, sigma*diff(Yr(t),t)-u(t)*Cr2*phi(
t)+u(t)*Yr(t)-Cr1*b*omega(t)+Cr1*v(t), sigma*diff(Yf(t),t)-u(t)*Cf2*phi(t)+u(t
)*Yf(t)-1/u(t)*delta(t)*sigma/cos(phi(t))^2*cos(epsilon)*phi_dot(t)*rf*diff(Yf
(t),t)+delta(t)*Cf1*sin(phi(t))*phi_dot(t)*an-u(t)*delta(t)*Cf1/cos(phi(t))*
cos(epsilon)-u(t)*delta(t)*Cf2*sin(epsilon)-1/u(t)*delta_dot(t)*sigma/cos(phi(
t))*cos(epsilon)*sin(phi(t))*rf*diff(Yf(t),t)-delta_dot(t)*Cf1*cos(phi(t))*an+
Cf1*omega(t)*w-Cf1*omega(t)*b+Cf1*v(t), phi_dot(t)-diff(phi(t),t), delta_dot(t
)-diff(delta(t),t)];
