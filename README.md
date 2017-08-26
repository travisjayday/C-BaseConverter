# C-BaseConverter
Implicitly converts between Hexadecimal, Binary and Decimal numbers. Can also explicitly convert from ANY imaginable base to any other imaginable base. 

# Modes -- Implicit and Explicit
Implicitly converts from: 
  - decimal to hexadecimal and binary
  - hexadecimal to decimal and binary
  - binary to decimal and hexadecimal <br><br>
  <b>Example: </b>
```
  root@pc:~#conv 0x14
  dec: 20<br>
  bin: 10100
  
  root@pc:~#conv 0b1010
  dec: 10
  hex: 0A
  
  root@pc:~#conv 20
  hex: 14
  bin: 10100
 ```
<hr><br>

<br>
Explicitly converts from: 
  - any base to any other base<br><br>

  <b>Example: </b>
  ```
  root@pc: #conv -e 16 8 14 
  Converting 14 from base 16 to base 8
  24
  ```
  
# Full Usage
```
Usage:
	  conv [0x123]			        Implicitly converts hex # to decimal and binary
	  conv [0b1010]			        Implicitly converts bin # to decimal and hex
	  conv [20]  			          Implicitly converts dec # to hex and binary
	  conv -c    			          Continuously converts implicit input until EOF
	  conv -e [16] [2] [num]	  Explicitly converts [num] from base [16] to base [2]
```

# Additional
Writing this base converter in pure C without <stdio.h> has been a fun little practice. A friend of mine inspired me to write this base converter, and I think it's just a handy tool to have around when working with other low-level programming languages (e.g. assembly). 
