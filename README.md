# Argument Parser

![GitHub repo size](https://img.shields.io/github/repo-size/FabricioLR/Argument_Parser_C?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/FabricioLR/Argument_Parser_C?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/FabricioLR/Argument_Parser_C?style=for-the-badge)
![Bitbucket open issues](https://img.shields.io/bitbucket/issues/FabricioLR/Argument_Parser_C?style=for-the-badge)
![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/FabricioLR/Argument_Parser_C?style=for-the-badge)

> Implementação minimalista de um argument parser escrito em C.

## 🚀 Instalando

Apenas copie o arquivo ![argument-pasrser.h](https://github.com/FabricioLR/Argument_Parser_C/blob/master/argument-parser.h) para dentro do seu projeto

## ☕ Usando

Adicione as opções desejadas, inicialize o parser e comece a usar

```
#include "argument-parser.h"

int main(int argc, char **argv){
    add_option("--argument1", "Argumento1 para teste", OPTION_IS_REQUIRED | OPTION_VALUE_IS_REQUIRED);
    if (!parser_init(argc, argv)){
		usage();
		....
	}
	printf("%s\n", get_option_value("--argument1"));
	...
...
```

Saída esperada

```
$./example
Option --argument1 is required
OPTIONS: 
     --argument1 <value>
          description: Argumento1 para teste
          Flags: OPTION_VALUE_IS_REQUIRED | OPTION_IS_REQUIRED
```


## 📫 Contribuindo

Para contribuir, siga estas etapas:

1. Fork este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie um Pull Request.

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).
