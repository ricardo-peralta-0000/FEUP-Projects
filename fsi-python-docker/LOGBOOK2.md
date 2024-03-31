# Trabalho realizado nas Semanas #2 e #3

## Identificação

- Vulnerabilidade **CVE-2017-0199** é uma falha no Microsoft Office, que afeta várias versões, incluindo o Office 2010 e 2013.
- A vulnerabilidade é explorável via documentos RTF ou arquivos maliciosos no Office, permitindo a execução remota de código.
- Afeta principalmente sistemas Windows.
- A vulnerabilidade é de gravidade crítica, pois permite que invasores executem código arbitrário nos sistemas comprometidos.

## Catalogação

- O CVE2017-0199 foi relatado inicialmente em abril de 2017 pela empresa de cibersegurança FireEye e recebeu um CVE ID.
- A Microsoft emitiu um patch para corrigir a vulnerabilidade em abril de 2017.
- Houve relatos de exploração dessa vulnerabilidade em ataques direcionados, mas não se sabe de bug bounties específicos.
- A gravidade da vulnerabilidade é critica (7.8) e sua exploração em ataques justificam a atenção constante da comunidade de segurança.

## Exploit

- Os exploits para CVE-2017-0199 foram desenvolvidos e estão disponíveis publicamente.
- Eles geralmente envolvem a criação de documentos RTF maliciosos ou arquivos do Office com código VBA incorporado.
- Metasploit, um framework de teste de penetração, inclui módulos para explorar essa vulnerabilidade.
- A exploração é relativamente acessível, tornando importante a atualização imediata da aplicação.

## Ataques


- Ataques de spear-phishing: documentos maliciosos permitem execução de código, resultando em controle total, violações de dados e espionagem.
- Pen drives maliciosos: Com documentos infectados, exploram CVE-2017-0199 para executar scripts maliciosos ao serem abertos.
- Downloads drive-by: Hospedados em sites maliciosos, documentos exploram CVE-2017-0199 para executar scripts prejudiciais ao serem acessados.
- E-mails de phishing: Anexos enganosos, explorando CVE-2017-0199, executam scripts maliciosos ao serem abertos, comprometendo sistemas das vítimas.
