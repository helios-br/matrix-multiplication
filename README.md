# Trabalho
Implementação de dois algoritmos para a multiplicação de matrizes: Naive Multiplication e Strassen Multiplication.

# Repositório
https://github.com/helios-br/matrix-multiplication.git

# Naive Multiplication
Trata-se da implementação básica (ingênua) da multiplicação de matrizes.

# Strassen Multiplication
Foram implementadas duas versões do algoritmo de Strassen, uma considerando cálculo de índices (StrassenIndexAlgorithm.cpp) e outra não (StrassenAlgorithm.cpp). Em ambas foram empregados pontos de corte para interromper o processamento recursivo e direcioná-lo para o algoritmo básico. De outra forma, ao processar a multiplicação de submatrizes de determinado tamanho (ordem), a execução do código é direcionada para a implementação básica, que mostrou ser melhor para matrizes de dimensão menor, otimizando a performance. Na versão com cálculo de índices o ponto de corte é 128 e na outra assume o valor 32.

Esses valores de ponto de corte não foram explorados com profundidade, merecendo uma melhor análise.

O segundo algoritmo, apesar de não fazer cálculo de índices, tem uma performance bastante razoável em função do uso da técnica "loop merging" (ver linhas 66 a 89 do arquivo StrassenAlgorithm.cpp). Em um único processamento são realizadas todas as operações de adição e subtração de matrizes previstas.

# Execução
1. Para construir a aplicação é necessário executar o comando "make" no diretório raiz do projeto ("matrix-multiplication").
2. Com isso, é gerado o diretório "output" contendo o executável e cópia das instâncias.
3. Para executar, digitar (ainda no diretório raiz): ./run.sh instance_name (a extensão não é necessária).
Exemplo: ./run.sh instance10-2
4. Ao final do processamento, será exibido o gráfico do resultado comparando as três diferentes implementações. Além disso, é gerado o arquivo "log.txt" que contém detalhamentos da última execução.

# Resultados
O algoritmo de Strassen com cálculo de índices apresentou melhor performance em relação aos demais (ver resultado-processamento.png). Maiores informações desse processamento segue abaixo:





