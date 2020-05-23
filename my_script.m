clear all
close all 
clc

G = 10;
w1 = 1;
w2 = 2;
p1 = (-4.052+2.34*j)/0.5
p2 = (-4.052-2.34*j)/0.5
%boucle ouverte
n = [G]
d = [1 w1+w2 w1*w2]
HO = tf(n,d)
h1 = tf([G],[1 w1])
h2 = tf([-G],[1 w2])
figure(1)
step(HO,h1,h2)
title('reponse indicielle du systeme en BO');
figure(2)
bode(HO,h1,h2)

%boucle fermer
figure(3)
s = tf('s');
k1 = 0.2
k2 = 0
k3 = 0.025
k4 = 0.3
Ac = 1
Ar = 1
nb = [G]
db1 = [1 (w1+w2) w1*w2+10*k1]
db2 = [1 (w1+w2) w1*w2+10*k2]
db3 = [1 (w1+w2) w1*w2+10*k3]
db4 = [1 (w1+w2) w1*w2+10*k4]
HB1 = tf(nb,db1) 
HB2 = tf(nb,db2) 
HB3 = tf(nb,db3) 
HB4 = tf(nb,db4) 
step(Ac*HB1,Ac*HB2,Ac*HB3,Ac*HB4)
title('reponse indicielle du systeme en BF');

figure(4)
step(Ar*(HB3/s),Ar/s)
title('reponse du systeme en BF (entre rampe)');
%representation d'etat
%boucle ouverte
a0 = 10
a1 = -10
A = [[-w1 0];[0 -w2]]
B = [1;1]
C = [a0 a1]
[ns , ds] = ss2tf(A,B,C,0)
HS = tf(ns,ds)
figure(5)
step(HS)
title('reponse indicielle du systeme en B0 (representation etat)');
%boucle fermer
A = [[-1 0];[0 -2]]
B = [1;1]
C = [10 -10]
k1 = p1*p2+p1+p2-1
k2 = -p1*p2-2*(p1+p2)-2
Kp = [k1 k2]
chkil = -C*inv(A-B*Kp)*B
L = 1/chkil
Af = A-B*Kp
Bf = B*L
[nf , df] = ss2tf(Af,Bf,C,0)
Hf = tf(nf,df)
figure(6)
step(Hf)
title('reponse indicielle du systeme en BF (representation etat) apres placement des poles');
figure(7)
step(Hf/s,1/s)
title('reponse a une rampe du systeme en BF (representation etat) apres placement des poles');





