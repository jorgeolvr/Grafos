'''
Resgate em Queda Livre
Jorge Allan de Castro Oliveira
Python 3.5.2 64-bit
'''
import math
import networkx as nx

qntTeste = int(input())

for i in range(0, qntTeste):
    G = nx.Graph()
    qntVertice = int(input())
    
    if qntVertice <= 500:
        for j in range(0, qntVertice):
            linha = input() 
            p, s = linha.split(" ")
            G.add_node(j, x = int(p), y = int(s))
            
        val1 = 0
        val2 = 1

        for j in range(0, int((qntVertice * (qntVertice - 1)) / 2)): # inserção de todas as arestas possíveis
            x1 = G.node[val1]['x']
            y1 = G.node[val1]['y']
            x2 = G.node[val2]['x']
            y2 = G.node[val2]['y']

            distancia = math.sqrt(math.pow(x1 - x2, 2) + math.pow(y1 - y2, 2))

            G.add_edge(val1, val2, weight = distancia)
            val2 = val2 + 1

            if val2 == qntVertice:
                val1 = val1 + 1
                val2 = val1 + 1

        mst = nx.minimum_spanning_tree(G, weight = 'weight')

        total = 0
        for (u, v, wt) in mst.edges.data('weight'):
            total = total + wt

        total = total / 100
        print("%.2f"%(total))