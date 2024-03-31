## Formato: flag{<frame_start>-<frame_end>-<selected_cipher_suite>-<total_encrypted_appdata_exchanged>-<size_of_encrypted_message>}

### frame_start

Analisando o ficheiro no wireshark e procurando o número aleatório utilizado na mensagem de Client Hello: **52362c11ff0ea3a000e1b48dc2d99e04c6d06ea1a061d5b8ddbf87b001745a27** descobrimos que se trata do número **814**.
![image1](Images/ctf13/13_1.png)

### frame_end
![image2](Images/ctf13/13_2.png)

Será **819** já que se trata da ultima Encrypted Handshake Message.

### selected_cipher_suite
 Na resposta do servidor verificamos a Cipher Suite: **TLS_RSA_WITH_AES_128_CBC_SHA256** :
![image3](Images/ctf13/13_3.png)

### total_encrypted_appdata_exchanged

**1264 = 80 + 1184**

![image4](Images/ctf13/13_4.png)


![image5](Images/ctf13/13_5.png)

### size_of_encrypted_message
**80 -  length**

![image6](Images/ctf13/13_6.png)

## conclusão

Juntando os valores ficamos com a flag final correta **flag{814-819-TLS_RSA_WITH_AES_128_CBC_SHA256-1264-80}**
