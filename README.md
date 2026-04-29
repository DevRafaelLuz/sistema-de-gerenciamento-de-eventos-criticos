# Estruturas de Dados Avançadas

## Sistema de Gerenciamento de Eventos Críticos de uma Cidade Inteligente

### 📄 Sobre o Sistema

Uma cidade inteligente monitora, em tempo real, eventos críticos urbanos, como:

- Acidentes de trânsito
- Falhas em semáforos
- Interrupções de energia
- Alagamentos
- Incêndios

Cada evento possui um nível de <u>severidade</u>, <u>timestamp</u>, <u>localização</u> e <u>status</u>.

O sistema conta com as funcionalidades de **registrar**, **consultar**, **priorizar** e **encerrar eventos de forma eficiente**, garantindo tempo de resposta rápido mesmo com grande volume de dados.

Para isso, o núcleo do sistema será composto por uma **Árvore AVL**, garantindo operações eficientes.

---

### 📗 Instruções de Compilação

⚙️ **Compilação no Visual Studio Code (Windows)**

1. **Instalação necessária Instale o VS Code.**
    - Instale o compilador MinGW (Windows).
    - Adicione o compilador ao PATH do sistema.

2. **Configuração no VS Code**
    - Instale a extensão C/C++ (Microsoft).
    - Instale a extensão Code Runner (opcional, para executar rapidamente).
    - Crie um arquivo programa.c.

3. **Compilação e execução**
    - Abra o terminal integrado no VS Code.
    - Compile com:
        > Bash
        > - 
        > gcc programa.c -o programa.exe
    - Execute com:
        > Bash 
        > - 
        > ./programa.exe

---

⚙️ **Compilação no Dev-C++**

1. **Instalação**
    - Baixe e instale o Dev-C++.
    - O compilador TDM-GCC já vem integrado.

2. **Criando o projeto**
    - Abra o Dev-C++.
    - Vá em Arquivo → Novo → Projeto → Console Application (C).
    - Salve o projeto e escreva seu código no editor.

3. **Compilação e execução**
    - Clique em Executar → Compilar e Executar ou pressione F11.
    - O programa será compilado e executado no console interno.

---

⚙️ **Compilação em Linux/Mac**

1. **Verificar compilador**   
    Na maioria dos sistemas Linux e Mac, o compilador gcc já está instalado.
    - Verifique com:
    > bash
    > -
    > gcc --version

    Se não estiver instalado   
    - Linux (Debian/Ubuntu):
    > Bash
    > -
    > sudo apt-get install build-essential

    - Mac (via Xcode Command Line Tools):
    > Bash
    > -
    > xcode-select --install

2. **Compilação e execução**
    - Compile com:

    > Bash
    > -
    > gcc programa.c -o programa

    - Execute com:
    > Bash
    > -
    > ./programa