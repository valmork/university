d_s segment
	a db 1Eh
	b db 72h
	nod db 00000010b
d_s ends

c_s segment
begin:
assume cs:c_s, ds:d_s
mov ax, d_s
mov ds, ax
mov al,a
mov ah,b
mov bl, nod
m1: 
cmp al,ah; сравниваем их
je exit; если равны - переходим в конец
jb m2; переход при a<b
sub al,ah;если a>b - a-b
m2:
sub ah,al; b-a
jmp m1; опять начало
exit: mov bl,ah
mov cx, 8;счётчик
m:
ror bl, 1;циклический сдвиг
jc m3;если cf = 1, то переходим
jmp m4;иначе в loop               
m3:
inc dl;+=1
m4:
loop m
mov ah,4ch
int 21h
c_s ends
end begin