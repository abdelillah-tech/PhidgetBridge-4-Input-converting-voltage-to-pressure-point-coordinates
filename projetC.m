close all; clear;
volt1_all = []; volt2_all = []; volt3_all = []; volt4_all = [];
force1_all = []; force2_all = []; force3_all = []; force4_all = [];
%coordonnées connues des trois capteurs
x1 = -48; y1 = -48; x2 = 48; y2 = -48; x3 = -48; y3 = 48; x4 = 48; y4 = 48;
X = [-25;25 ;25;-25;0  ;30;0 ;-30;-17;17 ;17;-17;0  ;15;0 ;-15;0];
Y = [-25;-25;25;25 ;-30;0 ;30;0  ;-17;-17;17;17 ;-15;0 ;15;0  ;0];

plot(X,Y,'*')
xlim([-50 50]); ylim([-50 50]);
xlabel('X (en cm)'); ylabel('Y (en cm)');

volt1=[5.1;3.6;2.9;3.5;4.3;3.1;3.1;4.4;4.5;3.6;3.1;3.6;4  ;3.4;3.4;4  ;3.8];
volt2=[3.2;4.7;3.4;2.8;4.3;4.2;3  ;2.9;3.6;4.4;3.5;3  ;3.9;3.9;3.3;3.3;3.5];
volt3=[1.9;1.4;2  ;3.6;1.7;1.7;2.9;2.9;2.1;1.6;2.2;3.1;1.9;1.9;2.6;2.6;2.2];
volt4=[8.5;9  ;10.7 ;9.1;8.6;9.8;9.9;8.6;8.6;9.2;10 ;9.1;9  ;9.6;9.6;9  ;9.4];

volt1_vide = 2.886; volt2_vide = 2.466; volt3_vide = 1.16; volt4_vide = 8.404;

volt1=(volt1-volt1_vide)*1e-02; volt2=(volt2-volt2_vide)*1e-02;
volt3=(volt3-volt3_vide)*1e-02; volt4=(volt4-volt4_vide)*1e-02;

force1 = zeros(max(size(Y),1)); force2 = zeros(max(size(Y),1));
force3 = zeros(max(size(Y),1)); force4 = zeros(max(size(Y),1));
f0 = 10 * 9.8;
for i=1:max(size(Y))
    C1 = [x1 x2 X(i,1) ; y1 y2 y3 ; 1 1 1];
    FI1 = [X(i,1)*f0;Y(i,1)*f0;f0];
    F1 = (C1^(-1))*FI1;
    C2 = [x3 x4;1 1];
    FI2 = [X(i,1)*F1(3);F1(3)];
    F2 = (C2^(-1))*FI2;
    force1(i,1) = F1(1);
    force2(i,1) = F1(2);
    force3(i,1) = F2(1);
    force4(i,1) = F2(2);
end
volt1_all = [volt1_all; volt1]; volt2_all = [volt2_all; volt2];
volt3_all = [volt3_all; volt3]; volt4_all = [volt4_all; volt4];
force1_all = [force1_all; force1]; force2_all = [force2_all; force2];
force3_all = [force3_all; force3]; force4_all = [force4_all; force4];
%% Tracer les courbes
figure;
plot(volt1_all, force1_all,'r*')
coef = polyfit(volt1_all,force1_all, 1)
sprintf('Coef ax + b: a = %6.5f b = %6.5f1',coef(1),coef(2))
a1 = coef(1); b1 = coef(2);
title('Sensor 1'); xlabel('voltage (en mV)'); ylabel('force (en N)');
x = min(volt1_all):0.01:max(volt1_all); y = coef(1)*(x) + coef(2);
hold on
plot(x,y,'b');

figure,
plot(volt2_all, force2_all,'r*')
coef = polyfit(volt2_all,force2_all, 1);
sprintf('Coef ax + b: a = %6.5f b = %6.5f2',coef(1),coef(2))
a2 = coef(1); b2 = coef(2);
title('Sensor 2'); xlabel('voltage (en mV)'); ylabel('force (en N)');
x = min(volt2_all):0.01:max(volt2_all);
y = coef(1)*(x) + coef(2);
hold on
plot(x,y,'b');

figure,
plot(volt3_all, force3_all,'r*')
coef = polyfit(volt3_all,force3_all, 1);
sprintf('Coef ax + b: a = %6.5f b = %6.5f3',coef(1),coef(2))
a3 = coef(1); b3 = coef(2);
title('Sensor 3');
xlabel('voltage (en mV)'); ylabel('force (en N)');
x = min(volt3_all):0.01:max(volt3_all); y = coef(1)*(x) + coef(2);
hold on
plot(x,y,'b');

figure,
plot(volt4_all, force4_all,'r*')
coef = polyfit(volt4_all,force4_all, 1);
sprintf('Coef ax + b: a = %6.5f b = %6.5f4',coef(1),coef(2))
a4 = coef(1);
b4 = coef(2);
title('Sensor 4');
xlabel('voltage (en mV)');
ylabel('force (en N)');
x = min(volt4_all):0.01:max(volt4_all);
y = coef(1)*(x) + coef(2);
hold on
plot(x,y,'b');