'''
Sociedade Brasileira Casamenteira
Jorge Allan de Castro Oliveira
Python 3.5.2 64-bit
NetworkX 2.1
'''
import networkx as nx

num = 0 # variável auxiliar
G = nx.Graph() # cria um grafo G
entrada = input() # leitura da linha de entrada

while entrada != "": # executa até o end of file
    pessoa1, pessoa2 = entrada.split(" ") # quebra da linha por espaço e atribução dos nomes às variáveis

    G.add_node(pessoa1) # criação de um vértice para a primeira pessoa da linha
    G.add_node(pessoa2) # criação de um vértice para a segunda pessoa da linha
    G.add_edge(pessoa1, pessoa2) # adicão de uma aresta entre os dois vértices criados

    entrada = input() # leitura de uma nova linha de entrada

for valor in G.degree():
    if valor != 2: # verifica se o vértice tem grau 2
        casamento = nx.maximal_matching(G) # método do NetworkX para casamento máximo
        num = len(casamento) # retorna o número de casamentos

print(num)