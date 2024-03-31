Analisando o ficheiro cipherspec.py percebemos que existem 3 funções responsaveis pela encriptação de dados.

- ```gen()```

Analisando o ficheiro cipherspec.py conseguimos concluir que a função gen() é responsável por gerar a chave utilizada na encriptação de dados.

A chave é definida com tamanho 16, porém é aplicado um "hotfix" que limita a chave criada. Isto é, os primeiros 13 bytes da chave criada vão ser sempre "\x00" e os ultimos 3 bytes da chave vão ser definidos sempre que a função é chamada.
Tendo em conta este facto, descobrimos assim uma vulnerabilidade pois o código está sujeito a ataques, por exemplo, de brute force que conseguem com facilidade descobrir a chave por não ser muito extensa.

É usado os.urandom() para garantir que esses 3 bytes são gerados aleatóriamente.


- ```enc(k, m, nonce)```

Esta função é responsável por cifrar os dados m, utilizando o algoritmo de encriptação AES com a chave k gerada pela função ```gen()``` e o nonce. 




- ```dec(k, c, nonce)```

Esta função é responsável por decifrar os dados c, utilizando o algoritmo de encriptação AES agora para decifrar com a chave k gerada pela função gen() anteriormente e o nonce. 


Nota: As funções ```enc``` e ```dec``` utilizam o CTR mode com o nonce para garantir que a mesma combinação de nonce e chave não pode ser reutilizada para mensagens diferentes. 


> Como consigo usar esta ciphersuite para cifrar e decifrar dados?

Para cifrar e decifrar dados com esta ciphersuite posso utilizar a função ```gen()``` para gerar um chave, podemos depois utilizar a função ```enc``` com essa chave e o ```nonce``` para cifrar a mensagem. Para decifrar a mensagem utilizamos a função ```dec``` com o mesmo par key-nonce utilizado para cifrar.  

> Como consigo fazer uso da vulnerabilidade que observei para quebrar o código?

Para fazer uso da vulnerabilidade observada e explicada anteriormente podemos criar um script em python que tente decifrar a mensagem que contem a flag tentando todas as combinações possiveis de chaves e utilizar essas chaves na funcão ```dec``` em conjunto com a mensagem cifrada com a flag que nos foi dada e o ```nonce``` que também nos é dado. 


> Como consigo automatizar este processo, para que o meu ataque saiba que encontrou a flag?

Uma maneira de automatizar este processo, é testar para todas as mensagens decifradas se contém a string "flag" dentro da mensagem.
Se tiver, quer dizer que encontrámos a flag.


### Para obter a flag criámos um script em python que automatizou esse processo. 
Usando a mensagem cifrada e o nonce recebidos de ```nc ctf-fsi.fe.up.pt 6003```

![Figura 1](Images/ctf10/script.png)


### Executando esse script obtivemos no terminal a flag na mensagem decifrada.

![Figura 2](Images/ctf10/flag.png)



