# CTF11

Ao aceder ao servidor recebemos a seguinte mensagem:
![Figura 1](Images/ctf11/ctf_data.png)


Analisando o ficheiro challenge.py percebemos que existe uma função responsavel pela encriptação da mensagem que contém a flag.




- ```def enc(x, e, n)```
Sendo:
- ```x```: uma mensagem que queremos cifrar.
- ```e```: um expoente publico que é usado no algoritmo e nos é fornecido quando acedemos ao servidor.
- ```n```: o módulo que nos é fornecido.

E uma função responsável de decriptação.
Sendo:
- ```dec(y, d, n)```
- ```y```: a mensagem encriptada como uma string hexadecimal.
- ```d```: o expoente privado que temos de descobrir.
- ```n```: o módulo que nos é fornecido.




O valor de ```d``` satisfaz esta equação ```ed % (p-1)(q-1) = 1```, como já temos o valor de ```e```, o expoente público, falta-nos descobrir ```p``` e ```q``` para conseguirmos chegar ao resultado do expoente privado ```d```.


##### - Como consigo usar a informação que tenho para inferir os valores usados no RSA que cifrou a flag?

Também sabemos que:
- ```p * q == n```
- ```p``` é um primo próximo de 2^512
- ```q``` é um primo próximo de 2^513

Para os descobir utilizámos o algoritmo de Miller Rabin. Pesquisámos um pouco e descobrimos uma implementação funcional.

```py
def miller_rabin(n, k):


    if n == 2:
        return True

    if n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2
    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
            
    return True
```


##### - Como consigo descobrir se a minha inferência está correta?

Conseguindo descobir números primos próximos dos valor do enunciado, temos de verificar se satizfazem a condição de ```p * q == n```, para o efeito, utilizámos um pequeno script em python.

```py
initial_p = nextPrime(2 ** 512)
p = initial_p
q = nextPrime(2 ** 513)

print("começou")



while True:
	while p * q < n:
		p = nextPrime(p)
	
	if p*q	== n:
		break
		
	q = nextPrime(q)
	p = nextPrime(2 ** 512)
```

##### - Finalmente, como posso extrair a minha chave do criptograma que recebi?

Assim, encontrámos o valor de ```p``` e ```q```, que substituindo na equação de cima, ```ed % (p-1)(q-1) = 1```, conseguimos descobrir a chave privada ```d```.
A equação em ordem a ```d``` pode ser representada em python por:

```d = pow(e, -1, (p - 1) * (q - 1))```


Tendo a mensagem encriptada fornecida pelo servidor, o módulo fornecido pelo servidor, e a chave privada que descobrimos usada para decifrar a mensagem com a flag, basta decifrar a mensagem cifrada com a função ```dec``` fornecida em ```challenge.py```.

```


ciphertext= "3032316161666637613463343265636265393264376637643063616633343733633465623132343336653263366433373834643337623838653535643430643439303935303835643034323661333032376138353239303461666261333934633936363933646637336235313134656164653662303264373938613336636434623263353062313862343866333131653533666436356463306239626435336631656230323837613835343265646339666361383038373934373065623834653330393166303132386132613832666333346662666534396638363230343764366135643132366435666230333136333631626431393561386336666437623630313030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030"


msg = dec(unhexlify(ciphertext), d, n).decode()


print(msg)
```

Descobrindo assim a flag na mensagem decifrada.

![Figura 1](Images/ctf11/ctf_flag.png)
