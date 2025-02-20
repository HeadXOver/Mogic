# Mogic
## A complete computer language in logic 逻辑完备的计算机语言
### example1:  
#### *in test.mgc*:  
```mgc
2*(7+6)  
9+7  
(8+6)*7;  
"hello"+"world"  
True or True;
1 or 2
0 and 0
```

####  result:  
*26*  
*16*  
*98*  
*helloworld*  
*Ture*  
*True*  
*False*  
##### Split statements with **carriage returns** or __semicolons__
##### 用**回车**或**分号**分割语句
______
______


### example2:  
#### in *first.mgc*:  
```mgc
obj a name '食物'  
obj b name '苹果'  
nat c name '能吃'  
  
know(b be a);  
know(a be c);  
  
tell(b be c)?
```

#### result:  
*True*  
